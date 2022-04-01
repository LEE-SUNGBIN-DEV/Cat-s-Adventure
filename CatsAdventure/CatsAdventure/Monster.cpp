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
	mMoveDirection(1),
	mReturnOriginalPosition(false)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
}
Monster::~Monster()
{

}

void Monster::Update()
{
	Vector2f currentPosition = GetPosition();

	currentPosition.x += this->mSpeed * this->mMoveDirection * (float)DELTA_TIME;
	SetPosition(currentPosition);
	
	// 방향 전환
	if (mPatrolDistance < abs(currentPosition.x - mOriginalPosition.x)
		&& mReturnOriginalPosition == false)
	{
		mReturnOriginalPosition = true;
		this->mMoveDirection *= -1;
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
