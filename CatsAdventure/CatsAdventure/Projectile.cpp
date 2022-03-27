#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"

Projectile::Projectile()
	: mTheta(0.f), mSpeed(200.f), mDirection(Vector2f(1.f, 1.f))
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	this->mDirection.Normalize();
}

Projectile::~Projectile()
{
}

void Projectile::OnCollision(Collider* _opponent)
{
}

void Projectile::OnCollisionEnter(Collider* _opponent)
{
}

void Projectile::OnCollisionExit(Collider* _opponent)
{
}

void Projectile::SetDirection(Vector2f _direction)
{
	this->mDirection = _direction;
	this->mDirection.Normalize();
}
