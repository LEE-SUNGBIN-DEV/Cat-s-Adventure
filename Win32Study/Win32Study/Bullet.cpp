#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet()
	: mDamage(1)
{
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
	Ellipse(_bitmapDC,
		this->GetPosition().x - this->GetScale().x,
		this->GetPosition().y - this->GetScale().y,
		this->GetPosition().x + this->GetScale().x,
		this->GetPosition().y + this->GetScale().y);
}
