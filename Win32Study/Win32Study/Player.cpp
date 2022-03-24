#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "TimeManager.h"

void Player::Update()
{
	// ====================== Key Input Control
	// Player Position
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

	// Player Act
}

void Player::Render(HDC _bitmapDC)
{
	Rectangle(_bitmapDC,
		this->GetPos().x - this->GetScale().x,
		this->GetPos().y - this->GetScale().y,
		this->GetPos().x + this->GetScale().x,
		this->GetPos().y + this->GetScale().y);
}
