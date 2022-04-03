#include "pch.h"
#include "GameCamera.h"

#include "GameCore.h"
#include "GameObject.h"
#include "GameCore.h"
#include "KeyManager.h"
#include "TimeManager.h"

GameCamera::GameCamera()
	:mTargetObject(nullptr),
	mTargetOffset(Vector2f(0.f, 0.f)),
	mTargetMode(true),
	mDiffrence(0.f, 0.f),
	mLookAtPosition(Vector2f(GameCore::GetInstance()->GetMainResolution())/2.f),
	mCurrentLookAtPosition(Vector2f(GameCore::GetInstance()->GetMainResolution()) / 2.f),
	mPrevLookAtPosition(Vector2f(GameCore::GetInstance()->GetMainResolution()) / 2.f),
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
	// Target Tracing Mode
	if (this->mTargetMode == true && this->mTargetObject != nullptr)
	{
		if (this->mTargetObject->IsAlive() == false)
		{
			this->mTargetObject = nullptr;
		}

		else
		{
			Vector2f lookAt = this->mTargetObject->GetPosition() - this->mTargetOffset;
			this->SetLookAtPosition(lookAt, true);
		}
	}

	// Mouse Mode
	/*if (KEY_CHECK(KEY::KEY_MOUSE_LEFT_BUTTON, KEY_STATE::KEY_STATE_DOWN))
	{
		Vector2f lookAt = GameCamera::GetInstance()->GetRealPosition(GET_MOUSE_POSITION);
		this->SetLookAtPosition(lookAt, false);
	}*/

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값을 계산
	CalculateDifference();
}

void GameCamera::CalculateDifference()
{
	switch (this->mTargetMode)
	{
	case false:
	{
		this->mAccumulatedTime += (float)DELTA_TIME;
		if (this->mAccumulatedTime >= this->mCameraMoveTimeByMouse)
		{
			this->mCurrentLookAtPosition = this->mLookAtPosition;
		}

		else
		{
			if (this->mLookAtPosition != this->mPrevLookAtPosition)
			{
				Vector2f LookAtDirection = this->mLookAtPosition - this->mPrevLookAtPosition;
				this->mCurrentLookAtPosition = this->mPrevLookAtPosition + LookAtDirection.Normalize() * this->mCameraSpeedByMouse * (float)DELTA_TIME;
			}
		}

		Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
		Vector2f centerPosition = mainResolution / 2.0f;

		this->mDiffrence = this->mCurrentLookAtPosition - centerPosition;
		this->mPrevLookAtPosition = this->mCurrentLookAtPosition;

		break;
	}

	case true:
	{
		Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
		Vector2f centerPosition = mainResolution / 2.0f;

		this->mCurrentLookAtPosition = this->mLookAtPosition;
		this->mDiffrence = this->mCurrentLookAtPosition - centerPosition;
		this->mPrevLookAtPosition = this->mCurrentLookAtPosition;

		break;
	}

	}
}

void GameCamera::SetLookAtPosition(Vector2f _lookAtPosition, bool _targetMode)
{
	this->mTargetMode = _targetMode;

	switch (this->mTargetMode)
	{
	// 마우스 모드
	case false:
	{
		this->mLookAtPosition = _lookAtPosition;
		float length = (this->mLookAtPosition - this->mPrevLookAtPosition).Length();
		this->mCameraSpeedByMouse = length / this->mCameraMoveTimeByMouse;
		this->mAccumulatedTime = 0.f;
	}
	break;

	// 키보드 모드
	case true:
	{
		// this->mLookAtPosition = _lookAtPosition;

		// Y축 고정
		this->mLookAtPosition.x = _lookAtPosition.x;
		this->mAccumulatedTime = 0.f;
	}
	break;
	}
}
