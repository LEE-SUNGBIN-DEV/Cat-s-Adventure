#include "pch.h"
#include "GameObject.h"
#include "KeyManager.h"
#include "timeManager.h"
#include "Collider.h"
#include "GameTimer.h"
#include "Animator.h"
#include "Gravity.h"

// 생성자
GameObject::GameObject()
	: mObjectName{},
	mObjectType(OBJECT_TYPE::OBJECT_TYPE_DEFALUT),
	mPosition(),
	mScale(),
	mDirection(Vector2f((float)MOVE_DIRECTION_RIGHT, 0.f)),
	mIsAlive(true),
	mTexture(nullptr),
	mCollider(nullptr),
	mTimer(nullptr),
	mAnimator(nullptr),
	mGravity(nullptr)
{
}
GameObject::GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition)
	: GameObject::GameObject()
{
	this->mScale.x = (_RightBottomPosition.x - _LeftTopPosition.x) / 2.0f;
	this->mScale.y = (_RightBottomPosition.y - _LeftTopPosition.y) / 2.0f;

	this->mPosition.x = _LeftTopPosition.x + this->mScale.x;
	this->mPosition.y = _LeftTopPosition.y + this->mScale.y;
}

// 복사 생성자
GameObject::GameObject(const GameObject& _origin)
	:mObjectType(_origin.mObjectType),
	mObjectName(_origin.mObjectName),
	mPosition(_origin.mPosition),
	mScale(_origin.mScale),
	mDirection(_origin.mDirection),
	mIsAlive(true),
	mTexture(_origin.mTexture),
	mCollider(nullptr),
	mTimer(nullptr),
	mAnimator(nullptr),
	mGravity(nullptr)
{
	if (_origin.mCollider)
	{
		this->mCollider = new Collider(*_origin.mCollider);
		this->mCollider->SetOwner(this);
	}

	if (_origin.mTimer)
	{
		this->mTimer = new GameTimer(*_origin.mTimer);
		this->mTimer->SetOwner(this);
	}

	if (_origin.mAnimator)
	{
		this->mAnimator = new Animator(*_origin.mAnimator);
		this->mAnimator->SetOwner(this);
	}

	if (_origin.mGravity)
	{
		this->mGravity = new Gravity(*_origin.mGravity);
		this->mGravity->SetOwner(this);
	}
}

GameObject::~GameObject()
{
	if (this->mCollider != nullptr)
	{
		delete this->mCollider;
	}

	if (this->mTimer != nullptr)
	{
		delete this->mTimer;
	}

	if (this->mAnimator != nullptr)
	{
		delete this->mAnimator;
	}
}

void GameObject::LateUpdate()
{
	if (this->mCollider != nullptr)
	{
		this->mCollider->LateUpdate();
	}

	if (this->mGravity != nullptr)
	{
		this->mGravity->LateUpdate();
	}
}

void GameObject::Render(HDC _bitmapDC)
{
	Vector2f renderPosition = GetPosition();
	// 렌더링 좌표(카메라 기준)
	renderPosition = GameCamera::GetInstance()->GetRenderPosition(renderPosition);

	Rectangle(_bitmapDC,
		(int)(renderPosition.x - this->GetScale().x),
		(int)(renderPosition.y - this->GetScale().y),
		(int)(renderPosition.x + this->GetScale().x),
		(int)(renderPosition.y + this->GetScale().y));

	this->ComponentRender(_bitmapDC);
}

void GameObject::OnCollision(Collider* _opponent)
{
}

void GameObject::OnCollisionEnter(Collider* _opponent)
{
}

void GameObject::OnCollisionExit(Collider* _opponent)
{
}

void GameObject::ComponentRender(HDC _bitmapDC)
{
	// Collider Component
	if (this->mCollider != nullptr)
	{
		this->mCollider->Render(_bitmapDC);
	}

	// Animation
	if (this->mAnimator != nullptr)
	{
		this->mAnimator->Render(_bitmapDC);
	}
}

void GameObject::AddCollider()
{
	this->mCollider = new Collider;
	this->mCollider->SetOwner(this);
}

void GameObject::AddTimer()
{
	this->mTimer = new GameTimer;
	this->mTimer->SetOwner(this);
}

void GameObject::AddAnimator()
{
	this->mAnimator = new Animator;
	this->mAnimator->SetOwner(this);
}

void GameObject::AddGravity()
{
	this->mGravity = new Gravity;
	this->mGravity->SetOwner(this);
}
