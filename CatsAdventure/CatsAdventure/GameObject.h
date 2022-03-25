#pragma once
#include "GameObject.h"

class Texture;
class Collider;

class GameObject
{
private:
	Vector2f mOffset;
	Vector2f mScale;

	Texture* mTexture;
	Collider* mCollider;

public:
	// »ý¼ºÀÚ
	GameObject();
	GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition);
	virtual ~GameObject();

	virtual void LateUpdate() final;
	virtual void Update() = 0;
	virtual void Render(HDC _bitmapDC);

	void ComponentRender(HDC _bitmapDC);
	void CreateCollider();

	// get
	Vector2f GetPosition() { return this->mOffset; }
	Vector2f GetScale() { return this->mScale; }
	Texture* GetTexture() { return this->mTexture; }
	Collider* GetCollider() { return this->mCollider; }

	// set
	void SetPosition(Vector2f _position) { this->mOffset = _position; return; }
	void SetScale(Vector2f _scale) { this->mScale = _scale;	return; }
	void SetTexture(Texture* _texture) { this->mTexture = _texture; }
	void SetCollider(Collider* _collider) { this->mCollider = _collider; }
};

