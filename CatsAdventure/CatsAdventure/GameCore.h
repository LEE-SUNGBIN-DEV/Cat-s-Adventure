#pragma once
#include "define.h"
// �̱��� ����
// ��ü�� ������ 1���� ����
// ���� ��𼭵� ���� ���� �����ؾ���

class Texture;
class GameObject;

class GameCore
{
private:
	// Main Window Infomation
	HWND	mainHWND;
	HDC		mainDC;
	POINT	mainResolution;

	// Bitmap Infromation
	HDC		bitmapDC;
	HBITMAP	bitmap;

	// Brush & Pen
	HBRUSH	mBrushType[(UINT)BRUSH_TYPE::BRUSH_TYPE_SIZE];
	HPEN	mPenType[(UINT)PEN_TYPE::PEN_TYPE_SIZE];

	GameCore();
	~GameCore();
public:
	// Singleton
	static GameCore* GetInstance()
	{
		static GameCore manager;
		return &manager;
	}

	int		Init(HWND _hwnd, POINT _resolution);
	void	Progress();
	void	CreateBrushAndPen();

	// get
	HWND	GetMainHWND() { return this->mainHWND; }
	HDC		GetMainDC() { return this->mainDC; }
	POINT	GetMainResolution() { return this->mainResolution; }
	HBRUSH	GetBrush(BRUSH_TYPE _brushType) { return this->mBrushType[(UINT)_brushType]; }
	HPEN	GetPen(PEN_TYPE _penType) { return this->mPenType[(UINT)_penType]; }
};

