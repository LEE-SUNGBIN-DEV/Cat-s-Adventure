#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameCore.h"

Collider::Collider()
	:mOwner(nullptr), mOffset(0.f, 0.f),
	mPosition(0.f, 0.f), mScale(0.f, 0.f)
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
	HPEN redPen = GameCore::GetInstance()->GetPen(PEN_TYPE::PEN_TYPE_RED);
	HPEN prevPen = (HPEN)SelectObject(_bitmapDC, redPen);

	HBRUSH hollowBrush = GameCore::GetInstance()->GetBrush(BRUSH_TYPE::BRUSH_TYPE_HOLLOW);
	HBRUSH prevBrush = (HBRUSH)SelectObject(_bitmapDC, hollowBrush);

	Vector2f position = GetPosition();

	Rectangle(_bitmapDC,
		int(position.x - mScale.x),
		int(position.y - mScale.y),
		int(position.x + mScale.x),
		int(position.y + mScale.y));

	SelectObject(_bitmapDC, prevPen);
	SelectObject(_bitmapDC, prevBrush);
}
