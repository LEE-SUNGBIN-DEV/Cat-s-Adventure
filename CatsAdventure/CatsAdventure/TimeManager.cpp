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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&mPrevCount);
	// �ʴ� ī��Ʈ ��
	QueryPerformanceFrequency(&mFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&mCurrentCount);
	// ī��Ʈ ���� ����
	mDeltaTime = (double)(mCurrentCount.QuadPart - mPrevCount.QuadPart) / (double)mFrequency.QuadPart;

	// ī��Ʈ �� ����
	mPrevCount = mCurrentCount;

	// update �Լ� ȣ�� Ƚ��
	++mCallCount;

	// ���� �ð� ����
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
