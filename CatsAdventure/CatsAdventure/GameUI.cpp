#include "pch.h"
#include "GameUI.h"

#include "KeyManager.h"

GameUI::GameUI()
	:mUIName{}
{
}

GameUI::~GameUI()
{
}

void GameUI::Update()
{
	if (KEY_CHECK(KEY::KEY_MOUSE_LEFT_BUTTON, KEY_STATE::KEY_STATE_DOWN))
	{
		Vector2f mousePosition = GET_MOUSE_POSITION;
		Vector2f uiPosition = this->GetPosition();
		Vector2f uiHalfScale = this->GetScale() / 2.0f;

		if (uiPosition.x - uiHalfScale.x < mousePosition.x
			&& uiPosition.x + uiHalfScale.x > mousePosition.x
			&& uiPosition.y - uiHalfScale.y < mousePosition.y
			&& uiPosition.y + uiHalfScale.y > mousePosition.y)
		{
			this->OnMouseClick();
		}
	}
}

void GameUI::Render(HDC _bitmapDC)
{

}

void GameUI::OnMouseClick()
{
}

