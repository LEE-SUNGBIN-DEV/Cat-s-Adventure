#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"

Missile::Missile()
	: mDamage(1)
{
}

Missile::~Missile()
{
}

void Missile::Update()
{

	Vector2f projectilePosition = GetPosition();

	projectilePosition.x += this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Missile::Render(HDC _bitmapDC)
{
	Ellipse(_bitmapDC,
		this->GetPosition().x - this->GetScale().x,
		this->GetPosition().y - this->GetScale().y,
		this->GetPosition().x + this->GetScale().x,
		this->GetPosition().y + this->GetScale().y);
}
