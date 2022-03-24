#include "pch.h"
#include "KeyManager.h"
#include "GameCore.h"


int mappingVK[(int)KEY::KEY_SIZE] =
{
	VK_LEFT,	// KEY_LEFT
	VK_RIGHT,	// KEY_RIGHT
	VK_UP,		// KEY_UP
	VK_DOWN,	// KEY_DOWN
	'Q',		// KEY_Q
	'W',		// KEY_W
	'E',		// KEY_E
	'R',		// KEY_R
	'A',		// KEY_A
	'S',		// KEY_S
	'D',		// KEY_D
	'F',		// KEY_F
	'Z',		// KEY_Z
	'X',		// KEY_X
	'C',		// KEY_C
	'V',		// KEY_V
	VK_MENU,	// KEY_ALT
	VK_CONTROL,	// KEY_CTRL
	VK_SHIFT,	// KEY_SHIFT
	VK_RETURN,	// KEY_ENTER
	VK_SPACE,	// KEY_SPACE
	VK_ESCAPE	// KEY_ESC
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
		this->keyInfo.push_back(KeyInfo(KEY_STATE::KEY_STATE_NONE, false));
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
				if (this->keyInfo[i].prevPress)
				{
					this->keyInfo[i].state = KEY_STATE::KEY_STATE_HOLD;
				}

				else
				{
					this->keyInfo[i].state = KEY_STATE::KEY_STATE_DOWN;
				}

				this->keyInfo[i].prevPress = true;
			}

			else
			{
				if (this->keyInfo[i].prevPress)
				{
					this->keyInfo[i].state = KEY_STATE::KEY_STATE_UP;
				}

				else
				{
					this->keyInfo[i].state = KEY_STATE::KEY_STATE_NONE;
				}

				this->keyInfo[i].prevPress = false;
			}
		}
	}

	else
	{
		for (int i = 0; i < (int)KEY::KEY_SIZE; ++i)
		{
			this->keyInfo[i].prevPress = false;
			this->keyInfo[i].state = KEY_STATE::KEY_STATE_UP;
		}
	}
}