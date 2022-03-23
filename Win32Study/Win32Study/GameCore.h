#pragma once
#include "define.h"
// 싱글톤 패턴
// 객체의 개수를 1개로 제한
// 언제 어디서든 쉽게 접근 가능해야함

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
	// 싱글톤
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

