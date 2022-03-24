#include "pch.h"
#include "GameObject.h"
#include "KeyManager.h"
#include "timeManager.h"

// »ý¼ºÀÚ
GameObject::GameObject()
	: mPosition(), mScale()
{

}
GameObject::GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition)
{
	this->mScale.x = (_RightBottomPosition.x - _LeftTopPosition.x) / 2.0f;
	this->mScale.y = (_RightBottomPosition.y - _LeftTopPosition.y) / 2.0f;

	this->mPosition.x = _LeftTopPosition.x + this->mScale.x;
	this->mPosition.y = _LeftTopPosition.y + this->mScale.y;
}

GameObject::~GameObject()
{

}
