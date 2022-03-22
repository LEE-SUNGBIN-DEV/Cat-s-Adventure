#include "pch.h"
#include "GameCore.h"

GameCore::GameCore()
{

}
GameCore::~GameCore()
{
	ReleaseDC(this->mainHWND, this->mainHDC);
}

int GameCore::Init(HWND _hwnd, POINT _resolution)
{
	this->mainHWND = _hwnd;
	this->mainResolution = _resolution;
	
	// 해상도에 맞게 윈도우 크기 조절
	RECT winRect = { 0, 0, this->mainResolution.x, this->mainResolution.y };
	// 메뉴, 테두리 굵기를 포함한 값을 계산해서 winRect에 다시 돌려줌
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(this->mainHWND, nullptr,
		100, 100, winRect.right - winRect.left, winRect.bottom - winRect.top,
		0);

	// 그리기를 위해 메인 윈도우의 Device Context 가져옴
	this->mainHDC = GetDC(this->mainHWND);

	return S_OK;
}

void GameCore::Progress()
{
	// Paint
	InvalidateRect(this->mainHWND);
}