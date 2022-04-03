#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"

Projectile::Projectile()
	: mTheta(0.f), mSpeed(100.f)
{
	this->SetObjectName(L"Projectile");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	this->GetDirection().Normalize();
	this->SetDirection(Vector2f(1.f, 1.f));
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
