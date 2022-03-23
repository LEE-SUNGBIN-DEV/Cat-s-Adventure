#pragma once
#include "define.h"
// �̱��� ����
// ��ü�� ������ 1���� ����
// ���� ��𼭵� ���� ���� �����ؾ���

class GameObject;

class GameCore
{
private:
	HWND mainHWND;
	HDC mainHDC;
	POINT mainResolution;

	HDC bitMapHDC;
	HBITMAP bitMap;

	GameObject* gameObject;

	void Update();
	void Render();

	GameCore();
	~GameCore();

public:
	// �̱���
	static GameCore* GetInstance()
	{
		static GameCore manager;
		return &manager;
	}
	int Init(HWND _hwnd, POINT _resolution);
	void Progress();

	// get
	HWND GetMainHWND() { return this->mainHWND; }
};

