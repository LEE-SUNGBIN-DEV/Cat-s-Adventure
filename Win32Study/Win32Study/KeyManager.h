#pragma once
#include "define.h"

class KeyManager
{
private:
	KeyManager();
	~KeyManager();

public:
	// ΩÃ±€≈Ê
	static KeyManager* GetInstance()
	{
		static KeyManager manager;
		return &manager;
	}
	void Init();
	void Update();
};

