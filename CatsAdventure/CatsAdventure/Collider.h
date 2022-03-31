#pragma once

class GameObject;

class Collider
{
private:
	static UINT generateID;

	UINT		mID;
	GameObject*	mOwner;	// 이 컴포넌트의 소유자

	Vector2f	mPosition;
	Vector2f	mOffset;
	Vector2f	mScale;

	int			mIsCollision;

public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	Collider& operator = (Collider& _origin) = delete;

	void LateUpdate();
	void Render(HDC _bitmapDC);

	void OnCollision(Collider* _opponent);
	void OnCollisionEnter(Collider* _opponent);
	void OnCollisionExit(Collider* _opponent);

	// get
	UINT		GetID() { return this->mID; }
	GameObject*	GetOwner() { return this->mOwner; }
	Vector2f	GetPosition() { return this->mPosition; }
	Vector2f	GetOffset() { return this->mOffset; }
	Vector2f	GetScale() { return this->mScale; }

	// set
	void SetOwner(GameObject* _owner) { this->mOwner = _owner; }
	void SetPosition(Vector2f _position) { this->mPosition = _position; }
	void SetOffset(Vector2f _offset) { this->mOffset = _offset; }
	void SetScale(Vector2f _scale) { this->mScale = _scale; }
};

