#include "pch.h"
#include "GameCore.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

GameCore::GameCore()
	:mainHWND(nullptr), mainDC(nullptr), mainResolution(),
	bitmapDC(nullptr), bitmap()
{
}
GameCore::~GameCore()
{
	ReleaseDC(this->mainHWND, this->mainDC);
	DeleteDC(this->bitmapDC);
	DeleteObject(this->bitmap);
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
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	return S_OK;
}

void GameCore::Progress()
{
	// ====================== Manager Update
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();

	// ====================== Render
	// ---------------------- Refresh
	Rectangle(this->bitmapDC, -1, -1, this->mainResolution.x + 1, this->mainResolution.y + 1);

	// ---------------------- Draw
	SceneManager::GetInstance()->Render(this->bitmapDC);

	// ---------------------- Copy to MainWindow
	BitBlt(this->mainDC, 0, 0, this->mainResolution.x, this->mainResolution.y
		, this->bitmapDC, 0, 0, SRCCOPY);

}
