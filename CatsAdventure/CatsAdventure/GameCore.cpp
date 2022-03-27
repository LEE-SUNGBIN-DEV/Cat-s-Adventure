#include "pch.h"
#include "GameCore.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "CollisionManager.h"

GameCore::GameCore()
	:mainHWND(nullptr), mainDC(nullptr), mainResolution(),
	bitmapDC(nullptr), bitmap(),
	mBrushType{}, mPenType{}
{
	this->CreateBrushAndPen();
}

GameCore::~GameCore()
{
	ReleaseDC(this->mainHWND, this->mainDC);
	DeleteDC(this->bitmapDC);
	DeleteObject(this->bitmap);

	for (UINT i = 0; i < (UINT)PEN_TYPE::PEN_TYPE_SIZE; i++)
	{
		delete mPenType[i];
	}
}

int GameCore::Init(HWND _hwnd, POINT _resolution)
{
	this->mainHWND = _hwnd;
	this->mainResolution = _resolution;
	
	// ---------------------- Set Window
	RECT winRect = { 0, 0, this->mainResolution.x, this->mainResolution.y };
	// 메뉴, 테두리 굵기를 포함한 값을 계산해서 winRect에 return
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(this->mainHWND, nullptr,
		100, 100, winRect.right - winRect.left, winRect.bottom - winRect.top,
		0);

	// ---------------------- for Paint, Bring Main Device Context
	this->mainDC = GetDC(this->mainHWND);

	// ---------------------- for Double Buffering
	this->bitmap = CreateCompatibleBitmap(this->mainDC, this->mainResolution.x, this->mainResolution.y);
	this->bitmapDC = CreateCompatibleDC(this->mainDC);

	HBITMAP prevBitMap = (HBITMAP)SelectObject(this->bitmapDC, this->bitmap);
	DeleteObject(prevBitMap);


	// ---------------------- Init Manager
	PathManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	CollisionManager::GetInstance()->Init();

	return S_OK;
}

void GameCore::Progress()
{
	// ====================== Manager Update
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();

	// ====================== Render
	// ---------------------- Refresh
	Rectangle(this->bitmapDC, -1, -1, this->mainResolution.x + 1, this->mainResolution.y + 1);

	// ---------------------- Draw
	SceneManager::GetInstance()->Render(this->bitmapDC);

	// ---------------------- Copy to MainWindow
	BitBlt(this->mainDC, 0, 0, this->mainResolution.x, this->mainResolution.y
		, this->bitmapDC, 0, 0, SRCCOPY);

}

void GameCore::CreateBrushAndPen()
{
	mBrushType[(UINT)BRUSH_TYPE::BRUSH_TYPE_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	
	mPenType[(UINT)PEN_TYPE::PEN_TYPE_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	mPenType[(UINT)PEN_TYPE::PEN_TYPE_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	mPenType[(UINT)PEN_TYPE::PEN_TYPE_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
