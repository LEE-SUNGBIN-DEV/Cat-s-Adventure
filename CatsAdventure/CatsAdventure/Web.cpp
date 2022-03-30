#include "pch.h"
#include "Web.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Texture.h"
#include "Collider.h"
#include "Player.h"

Web::Web()
	: mDamage(webDamage)
{
	this->SetObjectName(L"Web");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	this->SetScale(webBitmapScale);
	this->SetSpeed(webSpeed);
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SPIDER_WEB", L"\\texture\\spider_web.bmp"));

	// Create Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(webColliderScale);
}

Web::~Web()
{
}

void Web::Update()
{
	Vector2f projectilePosition = GetPosition();

	projectilePosition.x -= this->GetDirection().x * this->GetSpeed() * (float)DELTA_TIME;
	projectilePosition.y -= this->GetDirection().y * this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Web::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();
	position = GameCamera::GetInstance()->GetRenderPosition(position);

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		(int)position.x - (int)webBitmapScale.x / 2,
		(int)position.y - (int)webBitmapScale.y / 2,
		(int)webBitmapScale.x, (int)webBitmapScale.y,
		this->GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	this->ComponentRender(_bitmapDC);
}

void Web::OnCollision(Collider* _opponent)
{
}

void Web::OnCollisionEnter(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_PLAYER:
	{
		Player* player = (Player*)_opponent->GetOwner();
		player->SetHP(player->GetHP() - this->mDamage);
		RemoveGameObject(this);
	}
	break;
	}
}

void Web::OnCollisionExit(Collider* _opponent)
{
}
