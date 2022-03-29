#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "GameObject.h"
#include "Texture.h"

Animator::Animator()
	: mOwner(nullptr),
	mCurrentAnimation(nullptr),
	mRepeat(false)
{
}

// 복사 생성자
Animator::Animator(const Animator& _origin)
	: mOwner(nullptr),
	mCurrentAnimation(_origin.mCurrentAnimation),
	mRepeat(_origin.mRepeat)
{
}

Animator::~Animator()
{
	RemoveMap(this->mAnimationMap);
}

void Animator::CreateAnimation(const wstring& _name, Texture* _texture, Vector2f _leftTop, Vector2f _sliceSize, Vector2f _interval, float _duration, UINT _frameCount)
{
	Animation* animation = FindAnimation(_name);

	assert(animation == nullptr);

	animation = new Animation;
	animation->SetName(_name);
	animation->SetAnimator(this);
	animation->Create(_texture, _leftTop, _sliceSize, _interval, _duration, _frameCount);

	this->mAnimationMap.insert(make_pair(_name, animation));
}

Animation* Animator::FindAnimation(const wstring& _name)
{
	map<wstring, Animation*>::iterator iter = mAnimationMap.find(_name);
	if (iter == this->mAnimationMap.end())
	{
		return nullptr;
	}
	else
	{
		return iter->second;
	}
}

void Animator::Play(const wstring& _animationName, bool _repeat)
{
	this->mCurrentAnimation = this->FindAnimation(_animationName);
	this->mRepeat = _repeat;
}

void Animator::Update()
{
	if (this->mCurrentAnimation != nullptr)
	{
		this->mCurrentAnimation->Update();

		if (this->mRepeat && this->mCurrentAnimation->IsFinish())
		{
			this->mCurrentAnimation->SetFrame(0);
		}
	}
}

void Animator::Render(HDC _bitmapDC)
{
	if (this->mCurrentAnimation != nullptr)
	{
		this->mCurrentAnimation->Render(_bitmapDC);
	}
}
