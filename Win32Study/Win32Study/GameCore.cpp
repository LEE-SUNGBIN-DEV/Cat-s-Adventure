#include "pch.h"
#include "GameCore.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "KeyManager.h"

GameCore::GameCore()
	:mainHWND(nullptr), mainHDC(nullptr), mainResolution(),
	bitMapHDC(nullptr), bitMap()
{
	Vector2f tmpLT(100,100), tmpRB(200, 200);
	this->gameObject = new GameObject(tmpLT, tmpRB);
}
GameCore::~GameCore()
{
	ReleaseDC(this->mainHWND, this->mainHDC);
	DeleteDC(this->bitMapHDC);
	DeleteObject(this->bitMap);
	delete this->gameObject;
}

int GameCore::Init(HWND _hwnd, POINT _resolution)
{
	this->mainHWND = _hwnd;
	this->mainResolution = _resolution;
	
	// ---------------------- Set Window
	RECT winRect = { 0, 0, this->mainResolution.x, this->mainResolution.y };
	// 메뉴, 테두리 굵기를 포함한 값을 계산해서 winRect에 다시 돌려줌
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(this->mainHWND, nullptr,
		100, 100, winRect.right - winRect.left, winRect.bottom - winRect.top,
		0);

	// ---------------------- for Paint, Bring Main Device Context
	this->mainHDC = GetDC(this->mainHWND);

	// ---------------------- for Double Buffering
	this->bitMap = CreateCompatibleBitmap(this->mainHDC, this->mainResolution.x, this->mainResolution.y);
	this->bitMapHDC = CreateCompatibleDC(this->mainHDC);

	HBITMAP prevBitMap = (HBITMAP)SelectObject(this->bitMapHDC, this->bitMap);
	DeleteObject(prevBitMap);

	// ---------------------- Init Manager
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	return S_OK;
}
void GameCore::Update()
{
	// 키보드
	// 0x8000: 눌렸는지 확인
	Vector2f movePos = this->gameObject->GetPos();

	if (KeyManager::GetInstance()->GetKeyState(KEY::KEY_LEFT)
		== KEY_STATE::KEY_STATE_DOWN)
	{
		movePos.x -= 100.0f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		movePos.x += 100.0f * DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		movePos.y -= 100.0f * DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		movePos.y += 100.0f * DELTA_TIME;
	}
	gameObject->SetPos(movePos);
}
void GameCore::Render()
{
	// ----------------------Refresh
	Rectangle(this->bitMapHDC, -1, -1, this->mainResolution.x + 1, this->mainResolution.y + 1);
	
	// ----------------------Draw
	Rectangle(this->bitMapHDC,
		(int)(this->gameObject->GetPos().x - this->gameObject->GetScale().x),
		(int)(this->gameObject->GetPos().y - this->gameObject->GetScale().y),
		(int)(this->gameObject->GetPos().x + this->gameObject->GetScale().x),
		(int)(this->gameObject->GetPos().y + this->gameObject->GetScale().y));

	// ----------------------Copy to MainWindow
	BitBlt(this->mainHDC, 0, 0, this->mainResolution.x, this->mainResolution.y
	, this->bitMapHDC, 0, 0, SRCCOPY);
}

void GameCore::Progress()
{
	// Manager Update
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();

	// update
	Update();

	// render
	Render();

}
