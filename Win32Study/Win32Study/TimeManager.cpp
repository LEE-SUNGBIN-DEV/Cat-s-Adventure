#include "pch.h"
#include "TimeManager.h"
#include "GameCore.h"

TimeManager::TimeManager()
	: curCount(), prevCount(), frequency(),
	deltaTime(0.), accumulate(0.), callCount(0), FPS(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	// 현재 카운트
	QueryPerformanceCounter(&prevCount);
	// 초당 카운트 수
	QueryPerformanceFrequency(&frequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&curCount);
	// 카운트 값의 차이
	deltaTime = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;

	// 카운트 값 갱신
	prevCount = curCount;

	// update 함수 호출 횟수
	++callCount;

	// 단위 시간 누적
	accumulate += deltaTime;

	if (accumulate >= 1.)
	{
		FPS = callCount;
		accumulate = 0.;
		callCount = 0;

		wchar_t buffer[255] = {};
		swprintf_s(buffer, L"FPS: %d, DT: %f", FPS, deltaTime);
		SetWindowText(GameCore::GetInstance()->GetMainHWND(), buffer);
	}
}