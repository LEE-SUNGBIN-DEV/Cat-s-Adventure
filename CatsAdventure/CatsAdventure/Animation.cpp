#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"

Animation::Animation()
	:mAnimator(nullptr),
	mName{}
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
}

void Animation::Render()
{
}

void Animation::Create(Texture* _texture, UINT _frameCount)
{

}
