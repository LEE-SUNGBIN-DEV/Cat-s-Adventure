#include "pch.h"
#include "GameTimer.h"
#include "TimeManager.h"


GameTimer::GameTimer()
	: mOwner(nullptr),
	mCountTime(0.f),
	mTargetTime(0.f)
{
}

GameTimer::~GameTimer()
{
}

bool GameTimer::Timer()
{
	this->mCountTime += (float)DELTA_TIME;
	if (this->mCountTime >= this->mTargetTime)
	{
		this->mCountTime = 0.f;

		return true;
	}

	else
	{
		return false;
	}
}
