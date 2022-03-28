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
	this->SetScale(Vector2f(30.f,30.f));
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"MOUSE", L"\\texture\\mouse_left.bmp"));

	// Create Collider
	this->CreateCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());
}
Monster::~Monster()
{

}

void Monster::Update()
{
	Vector2f currentPosition = GetPosition();

	currentPosition.x += this->mSpeed * this->mMoveDirection * (float)DELTA_TIME;
	SetPosition(currentPosition);
	
	// ���� ��ȯ
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

	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

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