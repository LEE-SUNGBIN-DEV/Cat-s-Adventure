#include "pch.h"
#include "KeyManager.h"
#include "GameCore.h"

int mappingVK[(int)KEY::KEY_SIZE] =
{
	VK_LEFT,	// 0. KEY_LEFT
	VK_RIGHT,	// 1. KEY_RIGHT
	VK_UP,		// 2. KEY_UP
	VK_DOWN,	// 3. KEY_DOWN
	'Q',		// 4. KEY_Q
	'W',		// 5. KEY_W
	'E',		// 6. KEY_E
	'R',		// 7. KEY_R
	'A',		// 8. KEY_A
	'S',		// 9. KEY_S
	'D',		// 10. KEY_D
	'F',		// 11. KEY_F
	'Z',		// 12. KEY_Z
	'X',		// 13. KEY_X
	'C',		// 14. KEY_C
	'V',		// 15. KEY_V
	VK_MENU,	// 16. KEY_ALT
	VK_CONTROL,	// 17. KEY_CTRL
	VK_SHIFT,	// 18. KEY_SHIFT
	VK_RETURN,	// 19. KEY_ENTER
	VK_SPACE,	// 20. KEY_SPACE
	VK_ESCAPE,	// 21. KEY_ESC
	VK_LBUTTON, // 22. MOUSE_LEFT_BUTTON
	VK_RBUTTON	// 23. MOUSE_RIGHT_BUTTON,
};

KeyManager::KeyManager()
{

}

KeyManager::~KeyManager()
{

}

void KeyManager::Init()
{
	// Init Key State
	for (int i = 0; i < (int)KEY::KEY_SIZE; ++i)
	{
		this->mKeyInfo.push_back(KeyInfo(KEY_STATE::KEY_STATE_NONE, false));
	}
}

void KeyManager::Update()
{
	HWND hwnd = GetFocus();

	// Focusing check
	if (hwnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::KEY_SIZE; ++i)
		{
			if (GetAsyncKeyState(mappingVK[i]) & 0x8000)
			{
				if (this->mKeyInfo[i].prevPress)
				{
					this->mKeyInfo[i].state = KEY_STATE::KEY_STATE_HOLD;
				}

				else
				{
					this->mKeyInfo[i].state = KEY_STATE::KEY_STATE_DOWN;
				}

				this->mKeyInfo[i].prevPress = true;
			}

			else
			{
				if (this->mKeyInfo[i].prevPress)
				{
					this->mKeyInfo[i].state = KEY_STATE::KEY_STATE_UP;
				}

				else
				{
					this->mKeyInfo[i].state = KEY_STATE::KEY_STATE_NONE;
				}

				this->mKeyInfo[i].prevPress = false;
			}
		}
		// 클라이언트 마우스 좌표
		POINT clientMousePosition = {};
		GetCursorPos(&clientMousePosition);
		ScreenToClient(GameCore::GetInstance()->GetMainHWND(), &clientMousePosition);
		this->mMousePosition = Vector2f((float)clientMousePosition.x, (float)clientMousePosition.y);
	}

	else
	{
		for (int i = 0; i < (int)KEY::KEY_SIZE; ++i)
		{
			this->mKeyInfo[i].prevPress = false;
			this->mKeyInfo[i].state = KEY_STATE::KEY_STATE_UP;
		}
	}
}