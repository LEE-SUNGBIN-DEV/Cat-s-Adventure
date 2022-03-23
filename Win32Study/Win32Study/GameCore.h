#pragma once
#include "define.h"
// 싱글톤 패턴
// 객체의 개수를 1개로 제한
// 언제 어디서든 쉽게 접근 가능해야함

class GameCore
{
private:
	HWND mainHWND;
	POINT mainResolution;
	HDC mainHDC;
	GameObject gameObject;

	GameCore();
	~GameCore();
	void Update();
	void Render();

public:
	// static 함수나 변수는 객체가 없어도 접근 가능
	SINGLETON(GameCore);

	int Init(HWND _hwnd, POINT _resolution);
	void Progress();
};

