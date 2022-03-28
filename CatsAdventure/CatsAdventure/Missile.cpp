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
	: mDamage(10), mMissileState(MISSILE_STATE_UP),
	mUpHeight(0.f)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	this->SetScale(Vector2f(30.f, 30.f));
	this->SetSpeed(300.f);
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SHARK_MISSILE", L"\\texture\\sharkMissile_right.bmp"));
	
	// Create Collider
	this->CreateCollider();
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
		this->mUpHeight += MISSILE_UP_SPEED * (float)DELTA_TIME;
		updatePosition.y -= MISSILE_UP_SPEED * (float)DELTA_TIME;

		if (this->mUpHeight >= MISSILE_UP_HEIGHT)
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
			targetPosition = targetPosition - updatePosition;
			this->SetDirection(targetPosition);
		}
		
		else
		{
			this->SetDirection(Vector2f(1.f, 0.f));
		}

		updatePosition.x += this->GetDirection().x * MISSILE_GUIDED_SPEED * (float)DELTA_TIME;
		updatePosition.y += this->GetDirection().y * MISSILE_GUIDED_SPEED * (float)DELTA_TIME;
	}

	SetPosition(updatePosition);
}

void Missile::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
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