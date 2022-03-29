#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameCore.h"

UINT Collider::generateID = 0;

Collider::Collider()
	: mID(generateID++),
	mOwner(nullptr),
	mPosition(0.f, 0.f),
	mOffset(0.f, 0.f),
	mScale(0.f, 0.f)
{
}

// 복사 생성자
Collider::Collider(const Collider& _origin)
	: mID(generateID++),
	mOwner(nullptr),
	mPosition(_origin.mPosition),
	mOffset(_origin.mOffset),
	mScale(_origin.mScale)
{
}

Collider::~Collider()
{
}

void Collider::LateUpdate()
{
	// Trace Owner's Position + offset
	Vector2f position = this->GetOwner()->GetPosition() + this->GetOffset();

	this->SetPosition(position);
}

void Collider::Render(HDC _bitmapDC)
{
	HPEN greenPen = GameCore::GetInstance()->GetPen(PEN_TYPE::PEN_TYPE_GREEN);
	HPEN prevPen = (HPEN)SelectObject(_bitmapDC, greenPen);

	HBRUSH hollowBrush = GameCore::GetInstance()->GetBrush(BRUSH_TYPE::BRUSH_TYPE_HOLLOW);
	HBRUSH prevBrush = (HBRUSH)SelectObject(_bitmapDC, hollowBrush);

	Vector2f position = this->GetPosition();

	Rectangle(_bitmapDC,
		int(position.x - mScale.x),
		int(position.y - mScale.y),
		int(position.x + mScale.x),
		int(position.y + mScale.y));

	SelectObject(_bitmapDC, prevPen);
	SelectObject(_bitmapDC, prevBrush);
}

void Collider::OnCollision(Collider* _opponent)
{
	this->mOwner->OnCollision(_opponent);
}

void Collider::OnCollisionEnter(Collider* _opponent)
{
	this->mOwner->OnCollisionEnter(_opponent);
}

void Collider::OnCollisionExit(Collider* _opponent)
{
	this->mOwner->OnCollisionExit(_opponent);
}
