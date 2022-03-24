#include "pch.h"
#include "Monster.h"
#include "TimeManager.h"

Monster::Monster()
	:mSpeed(100.f),
	mOriginalPosition(Vector2f(900.f, 0.f)),
	mPatrolDistance(300.f),
	mMoveDirection(1),
	mReturnOriginalPosition(false)
{

}
Monster::~Monster()
{

}

void Monster::Update()
{
	Vector2f currentPosition = GetPos();

	currentPosition.x += this->mSpeed * this->mMoveDirection * (float)DELTA_TIME;
	SetPos(currentPosition);
	
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
	Rectangle(_bitmapDC,
		this->GetPos().x - this->GetScale().x,
		this->GetPos().y - this->GetScale().y,
		this->GetPos().x + this->GetScale().x,
		this->GetPos().y + this->GetScale().y);
}
