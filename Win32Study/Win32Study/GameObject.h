#pragma once
#include "GameObject.h"

class GameObject
{
private:
	Vector2f pos;
	Vector2f scale;

public:
	// »ý¼ºÀÚ
	GameObject();
	GameObject(Vector2f _ltPos, Vector2f _rbPos);
	virtual ~GameObject();

	void Update();
	void Render(HDC _bitmapDC);

	// get
	Vector2f GetPos() { return this->pos; }
	Vector2f GetScale() { return this->scale; }

	// set
	void SetPos(Vector2f _pos) { this->pos = _pos; return; }
	void SetScale(Vector2f _scale) { this->scale = _scale;	return; }
};

