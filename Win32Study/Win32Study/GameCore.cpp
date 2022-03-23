#include "pch.h"
#include "GameCore.h"
#include "GameObject.h"

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
void GameCore::Update()
{
	// Ű����
	// 0x8000: ���ȴ��� Ȯ��
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{

	}

	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{

	}

	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{

	}

	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{

	}

}
void GameCore::Render()
{
	// �׸���
	Rectangle(this->mainHDC,
		gameObject.GetPos().x - gameObject.GetScale().x,
		gameObject.GetPos().y - gameObject.GetScale().y,
		gameObject.GetPos().x + gameObject.GetScale().x,
		gameObject.GetPos().y + gameObject.GetScale().y);

	InvalidateRect(this->mainHWND, nullptr, true);
}
void GameCore::Progress()
{
	// update()
	Update();

	// render
	Render();

}