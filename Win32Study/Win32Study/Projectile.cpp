#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"

Projectile::Projectile()
	: mTheta(0.f), mSpeed(200.f), mDirection(Vector2f(1.f, 1.f))
{
	this->mDirection.Normalize();
}

Projectile::~Projectile()
{
}

void Projectile::SetDirection(Vector2f _direction)
{
	this->mDirection = _direction;
	this->mDirection.Normalize();
}
