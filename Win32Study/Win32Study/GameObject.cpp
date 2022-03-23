#include "pch.h"
#include "GameObject.h"

// »ý¼ºÀÚ
GameObject::GameObject()
{

}
GameObject::GameObject(Vector2f _ltPos, Vector2f _rbPos)
{
	this->scale.x = (_rbPos.x - _ltPos.x) / 2.0f;
	this->scale.y = (_rbPos.y - _ltPos.y) / 2.0f;

	this->pos.x = _ltPos.x + this->scale.x;
	this->pos.y = _ltPos.y + this->scale.y;
}

