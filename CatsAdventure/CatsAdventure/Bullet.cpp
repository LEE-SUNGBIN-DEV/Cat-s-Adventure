#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Monster.h"

Bullet::Bullet()
	: mDamage(bulletDamage)
{
	this->SetObjectName(L"Bullet");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	this->SetScale(bulletBitmapScale);
	this->SetSpeed(bulletSpeed);
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"FISH_BULLET", L"\\texture\\fishBullet_right.bmp"));
	
	// Create Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(bulletColliderScale);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{

	Vector2f projectilePosition = GetPosition();

	projectilePosition.x += this->GetDirection().x * this->GetSpeed() * (float)DELTA_TIME;
	projectilePosition.y -= this->GetDirection().y * this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Bullet::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// 특정 색상 제외하고 복사
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

void Bullet::OnCollision(Collider* _opponent)
{
}

void Bullet::OnCollisionEnter(Collider* _opponent)
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

void Bullet::OnCollisionExit(Collider* _opponent)
{
}
