#include "pch.h"
#include "GameObject.h"
#include "KeyManager.h"
#include "timeManager.h"
#include "Collider.h"

// »ý¼ºÀÚ
GameObject::GameObject()
	: mObjectName{}, mObjectType(OBJECT_TYPE::OBJECT_TYPE_DEFALUT),
	mOffset(), mScale(), mIsAlive(true),
	mTexture(nullptr), mCollider(nullptr)
{
}
GameObject::GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition)
	: GameObject::GameObject()
{
	this->mScale.x = (_RightBottomPosition.x - _LeftTopPosition.x) / 2.0f;
	this->mScale.y = (_RightBottomPosition.y - _LeftTopPosition.y) / 2.0f;

	this->mOffset.x = _LeftTopPosition.x + this->mScale.x;
	this->mOffset.y = _LeftTopPosition.y + this->mScale.y;
}

GameObject::~GameObject()
{
	if (this->mCollider != nullptr)
	{
		delete this->mCollider;
	}
}

void GameObject::LateUpdate()
{
	if (this->mCollider != nullptr)
	{
		this->mCollider->LateUpdate();
	}
}

void GameObject::Render(HDC _bitmapDC)
{
	Vector2f position = GetPosition();

	Rectangle(_bitmapDC,
		int(position.x - this->GetScale().x),
		int(position.y - this->GetScale().y),
		int(position.x + this->GetScale().x),
		int(position.y + this->GetScale().y));

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
}

void GameObject::CreateCollider()
{
	this->mCollider = new Collider;
	this->mCollider->SetOwner(this);
}
