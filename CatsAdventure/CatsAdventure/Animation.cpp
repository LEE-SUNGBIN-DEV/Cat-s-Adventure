#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "GameObject.h"
#include "Player.h"
#include "TimeManager.h"

Animation::Animation()
	:mAnimator(nullptr),
	mTexture(nullptr),
	mName{},
	mCurrentFrame(0),
	mDurationTime(0.f),
	mFinish(false)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (this->mFinish)
	{
		return;
	}

	this->mDurationTime += (float)DELTA_TIME;
	if (this->mDurationTime >= this->mFrameList[this->mCurrentFrame].mDuration)
	{
		++this->mCurrentFrame;
		if (this->mCurrentFrame >= this->mFrameList.size())
		{
			this->mFinish = true;
		}
		this->mDurationTime = 0;
	}
}

void Animation::Render(HDC _bitmapDC)
{
	if (this->mFinish)
	{
		return;
	}

	GameObject* object = this->GetAnimator()->GetOwner();
	Vector2f position = object->GetPosition();
	
	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		(int)position.x - object->GetScale().x,
		(int)position.y - object->GetScale().y,
		(int)object->GetScale().x * 2,
		(int)object->GetScale().y * 2,
		this->mTexture->GetDC(),
		(int)this->mFrameList[this->mCurrentFrame].mLeftTop.x,
		(int)this->mFrameList[this->mCurrentFrame].mLeftTop.y,
		(int)this->mFrameList[this->mCurrentFrame].mSliceSize.x,
		(int)this->mFrameList[this->mCurrentFrame].mSliceSize.y,
		RGB(255, 0, 255)
		);
}

void Animation::Create(Texture* _texture, Vector2f _leftTop, Vector2f _sliceSize, Vector2f _interval, float _duration, UINT _frameCount)
{
	this->mTexture = _texture; 

	AnimationFrame animationFrame = {};
	for (UINT i = 0; i < _frameCount; ++i)
	{
		animationFrame.mDuration = _duration;
		animationFrame.mLeftTop = _leftTop + _interval * i;
		animationFrame.mSliceSize = _sliceSize;

		this->mFrameList.push_back(animationFrame);
	}
}
