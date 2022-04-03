#include "pch.h"
#include "Monster.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"

Monster::Monster()
	:mSpeed(100.f), mHP(20),
	mOriginalPosition(Vector2f(900.f, 0.f)),
	mPatrolDistance(300.f),
	mReturnOriginalPosition(false)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	this->SetDirection(Vector2f((float)MOVE_DIRECTION_LEFT, 0.f));
}
Monster::~Monster()
{

}

void Monster::Update()
{
	Vector2f currentPosition = this->GetPosition();
	Vector2f moveDirection = this->GetDirection();
	currentPosition.x += this->mSpeed * this->GetDirection().x * (float)DELTA_TIME;
	SetPosition(currentPosition);
	
	// 방향 전환
	if (mPatrolDistance < abs(currentPosition.x - mOriginalPosition.x)
		&& mReturnOriginalPosition == false)
	{
		mReturnOriginalPosition = true;
		moveDirection.x -= -1;
		this->SetDirection(moveDirection);
	}

	if (mPatrolDistance > abs(currentPosition.x - mOriginalPosition.x))
	{
		mReturnOriginalPosition = false;
	}
}

void Monster::Render(HDC _bitmapDC)
{
	this->ComponentRender(_bitmapDC);
}

void Monster::OnCollision(Collider* _opponent)
{
}

void Monster::OnCollisionEnter(Collider* _opponent)
{
}

void Monster::OnCollisionExit(Collider* _opponent)
{
}
