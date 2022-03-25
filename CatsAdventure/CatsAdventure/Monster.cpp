#include "pch.h"
#include "Monster.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"

Monster::Monster()
	:mSpeed(100.f), mHP(100),
	mOriginalPosition(Vector2f(900.f, 0.f)),
	mPatrolDistance(300.f),
	mMoveDirection(1),
	mReturnOriginalPosition(false)
{
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"MOUSE", L"\\texture\\mouse_left.bmp"));

	// Create Collider
	this->CreateCollider();
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
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);
}
