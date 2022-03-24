#pragma once
#include "define.h"
// �̱��� ����
// ��ü�� ������ 1���� ����
// ���� ��𼭵� ���� ���� �����ؾ���

class GameObject;

class GameCore
{
private:
	// main
	HWND mainHWND;
	HDC mainDC;
	POINT mainResolution;

	// bitmap
	HDC bitmapDC;
	HBITMAP bitmap;

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
	POINT GetMainResolution() { return this->mainResolution; }
};

