#include "pch.h"
#include "TimeManager.h"
#include "GameCore.h"

TimeManager::TimeManager()
	: mCurrentCount(),
	mPrevCount(),
	mFrequency(),
	mDeltaTime(0),
	mAccumulate(0),
	mCallCount(0),
	mFPS(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	// 현재 카운트
	QueryPerformanceCounter(&mPrevCount);
	// 초당 카운트 수
	QueryPerformanceFrequency(&mFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&mCurrentCount);
	// 카운트 값의 차이
	mDeltaTime = (double)(mCurrentCount.QuadPart - mPrevCount.QuadPart) / (double)mFrequency.QuadPart;

	// 카운트 값 갱신
	mPrevCount = mCurrentCount;

	// update 함수 호출 횟수
	++mCallCount;

	// 단위 시간 누적
	mAccumulate += mDeltaTime;

	if (mAccumulate >= 1.)
	{
		mFPS = mCallCount;
		mAccumulate = 0.;
		mCallCount = 0;

		wchar_t buffer[255] = {};
		swprintf_s(buffer, L"FPS: %d, DT: %f", mFPS, mDeltaTime);
		SetWindowText(GameCore::GetInstance()->GetMainHWND(), buffer);
	}
}
