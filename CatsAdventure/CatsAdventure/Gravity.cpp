#include "pch.h"
#include "Gravity.h"
#include "GameObject.h"
#include "TimeManager.h"

Gravity::Gravity()
	: mIsGround(false), mOwner(nullptr), mFallSpeed(1.0f)
{
}

Gravity::Gravity(const Gravity& _origin)
	: mIsGround(_origin.mIsGround), mOwner(nullptr), mFallSpeed(1.0f)
{
}

Gravity::~Gravity()
{
}

void Gravity::LateUpdate()
{
	if (this->mIsGround == true)
	{
		this->mFallSpeed = 1.0f;
		return;
	}

	else
	{
		Vector2f gravityPosition = this->mOwner->GetPosition();

		// ³«ÇÏ ¼Óµµ ÁßÃ¸
		this->mFallSpeed += GRAVITY_ACCELERATION;
		gravityPosition.y = gravityPosition.y + (this->mFallSpeed * (float)DELTA_TIME);
		this->mOwner->SetPosition(gravityPosition);
	}
}
