#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "GameObject.h"
#include "Texture.h"

Animator::Animator()
	: mOwner(nullptr),
	mCurrentAnimation(nullptr)
{
}

// 복사 생성자
Animator::Animator(const Animator& _origin)
	: mOwner(nullptr),
	mCurrentAnimation(_origin.mCurrentAnimation)
{
}

Animator::~Animator()
{
	RemoveMap(this->mAnimationMap);
}

void Animator::CreateAnimation(const wstring& _name, Texture* _texture, UINT _frameCount)
{
	Animation* animation = FindAnimation(_name);

	assert(animation == nullptr);

	animation = new Animation;
	animation->SetName(_name);
	animation->SetAnimator(this);
	this->mAnimationMap.insert(make_pair(_name, animation));

	animation->Create(_texture, _frameCount);
}

Animation* Animator::FindAnimation(const wstring& _name)
{
	map<wstring, Animation*>::iterator iter = mAnimationMap.find(_name);
	if (iter == this->mAnimationMap.end())
		return nullptr;
	else
		iter->second;
}

void Animator::Play()
{
}

void Animator::Update()
{
	if (this->mCurrentAnimation != nullptr)
	{
		this->mCurrentAnimation->Update();
	}
}

void Animator::Render()
{
	if (this->mCurrentAnimation != nullptr)
	{
		this->mCurrentAnimation->Render();
	}
}
