#include "pch.h"
#include "GameCamera.h"
#include "GameObject.h"
#include "GameCore.h"
#include "KeyManager.h"
#include "TimeManager.h"

GameCamera::GameCamera()
	:mTargetObject(nullptr),
	mDiffrence(0.f, 0.f),
	mLookAtPosition(Vector2f(0.f, 0.f)),
	mCurrentLookAtPosition(Vector2f(0.f, 0.f)),
	mPrevLookAtPosition(Vector2f(0.f, 0.f)),
	mCameraSpeedByKeyboard(1000.f),
	mCameraSpeedByMouse(0.f),
	mCameraMoveTimeByMouse(1.0f),
	mAccumulatedTime(0.f)
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	if (this->mTargetObject != nullptr)
	{
		if (this->mTargetObject->IsAlive() == false)
		{
			this->mTargetObject = nullptr;
		}

		else
		{
			//this->mLookAtPosition = this->mTargetObject->GetPosition();
		}
	}

	// Left
	if (KEY_CHECK(KEY::KEY_D, KEY_STATE::KEY_STATE_HOLD))
	{
		this->mLookAtPosition.x -= this->mCameraSpeedByKeyboard * (float)DELTA_TIME;
	}

	// Right
	if (KEY_CHECK(KEY::KEY_A, KEY_STATE::KEY_STATE_HOLD))
	{
		this->mLookAtPosition.x += this->mCameraSpeedByKeyboard * (float)DELTA_TIME;
	}

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값을 계산
	CalculateDifference();
}

void GameCamera::CalculateDifference()
{
	this->mAccumulatedTime += (float)DELTA_TIME;
	if (this->mAccumulatedTime >= this->mCameraMoveTimeByMouse)
	{
		this->mCurrentLookAtPosition = this->mLookAtPosition;
	}

	else
	{
		Vector2f LookAtDirection = this->mLookAtPosition - this->mPrevLookAtPosition;
		this->mCurrentLookAtPosition = this->mPrevLookAtPosition + LookAtDirection.Normalize() * this->mCameraSpeedByMouse * (float)DELTA_TIME;
	}
	
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	Vector2f centerPosition = mainResolution / 2.0f;

	this->mDiffrence = this->mCurrentLookAtPosition - centerPosition;
	this->mPrevLookAtPosition = this->mCurrentLookAtPosition;
}
