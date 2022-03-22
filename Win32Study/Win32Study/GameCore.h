#pragma once
#include "define.h"
// �̱��� ����
// ��ü�� ������ 1���� ����
// ���� ��𼭵� ���� ���� �����ؾ���

class GameCore
{
private:
	HWND mainHWND;
	POINT mainResolution;
	HDC mainHDC;

	GameCore();
	~GameCore();

public:
	// static �Լ��� ������ ��ü�� ��� ���� ����
	SINGLETON(GameCore);

	int Init(HWND _hwnd, POINT _resolution);
	void Progress();
};

