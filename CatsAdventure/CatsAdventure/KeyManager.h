#pragma once
#include "define.h"

enum class KEY_STATE
{
	KEY_STATE_NONE, // 
	KEY_STATE_DOWN, // Key Down
	KEY_STATE_HOLD, // Key Hold
	KEY_STATE_UP, // Key Up
};

enum class KEY
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_Q, KEY_W, KEY_E, KEY_R,
	KEY_A, KEY_S, KEY_D, KEY_F,
	KEY_Z, KEY_X, KEY_C, KEY_V,
	KEY_ALT, KEY_CTRL, KEY_SHIFT,
	KEY_ENTER, KEY_SPACE, KEY_ESC,


	KEY_SIZE
};

struct KeyInfo
{
	KEY_STATE state;
	bool prevPress;

	KeyInfo(KEY_STATE _state, bool _prevPress)
	{
		this->state = _state;
		this->prevPress = _prevPress;
	}
};

class KeyManager
{
	// 1. ������ ����ȭ
	// ���� ������ �������� ������ �̺�Ʈ�� �����ؾ��Ѵ�.

	// 2. �پ��� ��Ȳ���� Ű �̺�Ʈ ó��
private:
	vector<KeyInfo>	keyInfo;

	KeyManager();
	~KeyManager();

public:
	// Singleton
	static KeyManager* GetInstance()
	{
		static KeyManager manager;
		return &manager;
	}
	
	void Init();
	void Update();

	// get
	KEY_STATE GetKeyState(KEY _index)
	{
		return this->keyInfo[(int)_index].state;
	}
};

