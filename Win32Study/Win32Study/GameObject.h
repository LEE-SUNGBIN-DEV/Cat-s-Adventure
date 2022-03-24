#pragma once
#include "GameObject.h"

class GameObject
{
private:
	Vector2f mPosition;
	Vector2f mScale;

public:
	// »ý¼ºÀÚ
	GameObject();
	GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render(HDC _bitmapDC) = 0;

	// get
	Vector2f GetPos() { return this->mPosition; }
	Vector2f GetScale() { return this->mScale; }

	// set
	void SetPos(Vector2f _position) { this->mPosition = _position; return; }
	void SetScale(Vector2f _scale) { this->mScale = _scale;	return; }
};

