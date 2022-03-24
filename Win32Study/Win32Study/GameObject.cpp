#include "pch.h"
#include "GameObject.h"
#include "KeyManager.h"
#include "timeManager.h"

// »ý¼ºÀÚ
GameObject::GameObject()
	: pos(), scale()
{

}
GameObject::GameObject(Vector2f _ltPos, Vector2f _rbPos)
{
	this->scale.x = (_rbPos.x - _ltPos.x) / 2.0f;
	this->scale.y = (_rbPos.y - _ltPos.y) / 2.0f;

	this->pos.x = _ltPos.x + this->scale.x;
	this->pos.y = _ltPos.y + this->scale.y;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	// ====================== Key Input Control
	// Object Position
	Vector2f movePos = this->GetPos();

	if (KeyManager::GetInstance()->GetKeyState(KEY::KEY_LEFT)
		== KEY_STATE::KEY_STATE_HOLD)
	{
		movePos.x -= 100.0f * (float)DELTA_TIME;
	}

	if (KeyManager::GetInstance()->GetKeyState(KEY::KEY_RIGHT)
		== KEY_STATE::KEY_STATE_HOLD)
	{
		movePos.x += 100.0f * (float)DELTA_TIME;
	}

	if (KeyManager::GetInstance()->GetKeyState(KEY::KEY_UP)
		== KEY_STATE::KEY_STATE_DOWN)
	{
		movePos.y -= 20.0f;
	}

	if (KeyManager::GetInstance()->GetKeyState(KEY::KEY_DOWN)
		== KEY_STATE::KEY_STATE_HOLD)
	{
		movePos.y += 100.0f * (float)DELTA_TIME;
	}
	this->SetPos(movePos);

	// Object Act
}

void GameObject::Render(HDC _bitmapDC)
{
	Rectangle(_bitmapDC,
		this->pos.x - this->scale.x,
		this->pos.y - this->scale.y,
		this->pos.x + this->scale.x,
		this->pos.y + this->scale.y);
}

