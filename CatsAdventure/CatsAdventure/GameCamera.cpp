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
	mCameraSpeed(0.f)
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	if (this->mTargetObject != nullptr)
	{
		if (this->mTargetObject->GetIsAlive() == false)
		{
			this->mTargetObject = nullptr;
		}

		else
		{
			this->mLookAtPosition = this->mTargetObject->GetPosition();
		}

		this->mLookAtPosition = this->mTargetObject->GetPosition();
	}

	// Left
	if (KEY_CHECK(KEY::KEY_D, KEY_STATE::KEY_STATE_HOLD))
	{
		this->mLookAtPosition.x -= this->mCameraSpeed * (float)DELTA_TIME;
	}

	// Right
	if (KEY_CHECK(KEY::KEY_A, KEY_STATE::KEY_STATE_HOLD))
	{
		this->mLookAtPosition.x += this->mCameraSpeed * (float)DELTA_TIME;
	}

	// ȭ�� �߾� ��ǥ�� ī�޶� LookAt ��ǥ���� ���̰��� ���
	CalculateDifference();
}

void GameCamera::CalculateDifference()
{
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	Vector2f centerPosition = mainResolution / 2.0f;

	this->mDiffrence = this->mLookAtPosition - centerPosition;
}
