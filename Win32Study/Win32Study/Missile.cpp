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

	projectilePosition.x += this->GetDirection().x * this->GetSpeed() * (float)DELTA_TIME;
	projectilePosition.y -= this->GetDirection().y * this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Missile::Render(HDC _bitmapDC)
{
}
