#include "pch.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Gravity.h"

Tile::Tile()
	:mTargetTextureIndex(15)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_TILE);
	this->SetObjectName(L"Tile");
	this->SetScale(Vector2f(TILE_SIZE, TILE_SIZE));
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"Tile Stone", L"\\texture\\tile\\tile_stone.bmp"));

	this->AddCollider();
	this->GetCollider()->SetScale(this->GetScale());
	this->GetCollider()->SetOffset(Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));
}

Tile::~Tile()
{
}

void Tile::Render(HDC _bitmapDC)
{
	if (this->GetTexture() == nullptr)
	{
		return;
	}

	else
	{
		Vector2f renderPosition = this->GetPosition();
		Vector2f tileScale = this->GetScale();
		renderPosition = GameCamera::GetInstance()->GetRenderPosition(renderPosition);

		UINT originalTextureWidth = this->GetTexture()->GetBitmapInfoWidth();
		UINT originalTextureHeight = this->GetTexture()->GetBitmapInfoHeight();
		
		UINT originalTextureMaxRow = originalTextureWidth / TILE_SIZE;
		UINT originalTextureMaxCol = originalTextureHeight / TILE_SIZE;

		UINT targetTextureRow = this->mTargetTextureIndex / originalTextureMaxCol;
		UINT targetTextureCol = this->mTargetTextureIndex % originalTextureMaxCol;

		assert(targetTextureRow < originalTextureMaxRow);

		BitBlt(_bitmapDC,
			(int)renderPosition.x, (int)renderPosition.y,
			TILE_SIZE, TILE_SIZE,
			this->GetTexture()->GetDC(),
			TILE_SIZE * targetTextureRow,
			TILE_SIZE * targetTextureCol,
			SRCCOPY);
	}
}

void Tile::Update()
{
}

void Tile::OnCollision(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_PLAYER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(true);

	}

	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(true);
	}
	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
	}
	break;

	}
}

void Tile::OnCollisionEnter(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_PLAYER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(true);
	}

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(true);
	}
	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
		RemoveGameObject(_opponent->GetOwner());
	}

	break;
	}
}

void Tile::OnCollisionExit(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_PLAYER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(false);
	}

	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		_opponent->GetOwner()->GetGravity()->SetIsGround(false);
	}
	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
	}
	break;
	
	}
}


