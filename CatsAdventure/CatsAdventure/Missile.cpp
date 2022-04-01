#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Monster.h"
#include "SceneManager.h"
#include "GameScene.h"

Missile::Missile()
	: mDamage(missileDamage),
	mMissileState(MISSILE_STATE_UP),
	mUpHeight(0.f)
{
	this->SetObjectName(L"Missile");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	this->SetScale(missileScale);
	this->SetSpeed(missileSpeed);
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SHARK_MISSILE", L"\\texture\\sharkMissile_right.bmp"));
	
	// Create Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vector2f updatePosition = this->GetPosition();
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	if (this->mMissileState == MISSILE_STATE_UP)
	{
		this->mUpHeight += missileUpSpeed * (float)DELTA_TIME;
		updatePosition.y -= missileUpSpeed * (float)DELTA_TIME;

		if (this->mUpHeight >= missileUpHeight)
		{
			this->mUpHeight = 0.f;
			this->mMissileState = MISSILE_STATE_GUIDED;
		}
	}

	else if (this->mMissileState == MISSILE_STATE_GUIDED)
	{
		if (!gameObjectList.empty())
		{
			Vector2f targetPosition = gameObjectList[0]->GetPosition();
			targetPosition = (targetPosition - updatePosition);
			targetPosition.x = targetPosition.x * 0.8f;
			this->SetDirection(targetPosition.Normalize());
		}
		
		else
		{
			this->SetDirection(this->GetDirection());
		}

		updatePosition.x += this->GetDirection().x * missileGuidedSpeed * (float)DELTA_TIME;
		updatePosition.y += this->GetDirection().y * missileGuidedSpeed * (float)DELTA_TIME;
	}

	SetPosition(updatePosition);
}

void Missile::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();
	position = GameCamera::GetInstance()->GetRenderPosition(position);
	
	Vector2f halfScale = this->GetScale() / 2.0f;

	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		(int)position.x - (int)halfScale.x,
		(int)position.y - (int)halfScale.y,
		(int)missileScale.x, (int)missileScale.y,
		this->GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	this->ComponentRender(_bitmapDC);
}

void Missile::OnCollision(Collider* _opponent)
{
}

void Missile::OnCollisionEnter(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		Monster* monster = (Monster*)_opponent->GetOwner();
		monster->SetHP(monster->GetHP() - this->mDamage);

		RemoveGameObject(this);
	}
	break;
	}
}

void Missile::OnCollisionExit(Collider* _opponent)
{
}
