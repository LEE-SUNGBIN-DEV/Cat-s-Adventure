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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&prevCount);
	// �ʴ� ī��Ʈ ��
	QueryPerformanceFrequency(&frequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&curCount);
	// ī��Ʈ ���� ����
	deltaTime = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;

	// ī��Ʈ �� ����
	prevCount = curCount;

	// update �Լ� ȣ�� Ƚ��
	++callCount;

	// ���� �ð� ����
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