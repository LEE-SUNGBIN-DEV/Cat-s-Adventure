#include "pch.h"
#include "GameObject.h"

// »ý¼ºÀÚ
GameObject::GameObject(POINT _ltPos, POINT _rbPos)
{
}
GameObject::GameObject(POINT _ltPos, POINT _rbPos)
{
	this->scale.x = (_rbPos.x - _ltPos.x) / 2;
	this->scale.y = (_rbPos.y - _ltPos.y) / 2;

	this->pos.x = _ltPos.x + this->scale.x;
	this->pos.y = _ltPos.y + this->scale.y;
}

// get
POINT GameObject::GetPos()
{
	return this->pos;
}
POINT GameObject::GetScale()
{
	return this->scale;
}

// set
void GameObject::SetPos(POINT _pos)
{
	this->pos = _pos;
	return;
}
void GameObject::SetScale(POINT _scale)
{
	this->scale = _scale;
	return;
}