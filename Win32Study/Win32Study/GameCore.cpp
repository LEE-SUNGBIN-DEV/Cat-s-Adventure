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
	
	// �ػ󵵿� �°� ������ ũ�� ����
	RECT winRect = { 0, 0, this->mainResolution.x, this->mainResolution.y };
	// �޴�, �׵θ� ���⸦ ������ ���� ����ؼ� winRect�� �ٽ� ������
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(this->mainHWND, nullptr,
		100, 100, winRect.right - winRect.left, winRect.bottom - winRect.top,
		0);

	// �׸��⸦ ���� ���� �������� Device Context ������
	this->mainHDC = GetDC(this->mainHWND);

	return S_OK;
}

void GameCore::Progress()
{
	// Paint
	InvalidateRect(this->mainHWND);
}