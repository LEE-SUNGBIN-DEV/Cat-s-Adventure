#pragma once
#include "GameObject.h"
#include "GameCamera.h"

class Texture;
class Collider;
class GameTimer;
class Animator;

class GameObject
{
private:
	OBJECT_TYPE	mObjectType;
	wstring		mObjectName;

	Vector2f	mOffset;
	Vector2f	mScale;
	bool		mIsAlive;

	// Texture
	Texture*	mTexture;

	// Component
	Collider*	mCollider;
	GameTimer*	mTimer;
	Animator*	mAnimator;

	// EventManager 클래스를 통해서만 조작 가능
	void SetIsAlive(bool _isAlive) { this->mIsAlive = _isAlive; }

public:
	GameObject();
	GameObject(Vector2f _LeftTopPosition, Vector2f _RightBottomPosition);
	GameObject(const GameObject& _origin);
	virtual ~GameObject();

	virtual void LateUpdate() final;
	virtual void Update() = 0;
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	void ComponentRender(HDC _bitmapDC);

	void AddCollider();
	void AddTimer();
	void AddAnimator();

	virtual GameObject* Clone() = 0;

	// get
	const wstring&	GetObjectName() { return this->mObjectName; }
	OBJECT_TYPE		GetObjectType() { return this->mObjectType; }
	Vector2f		GetPosition() { return this->mOffset; }
	Vector2f		GetScale() { return this->mScale; }
	bool			GetIsAlive() { return this->mIsAlive; }
	Texture*		GetTexture() { return this->mTexture; }
	Collider*		GetCollider() { return this->mCollider; }
	GameTimer*		GetTimer() { return this->mTimer; }
	Animator*		GetAnimator() { return this->mAnimator; }

	// set
	void SetPosition(Vector2f _position) { this->mOffset = _position; return; }
	void SetScale(Vector2f _scale) { this->mScale = _scale;	return; }
	void SetTexture(Texture* _texture) { this->mTexture = _texture; }
	void SetCollider(Collider* _collider) { this->mCollider = _collider; }
	void SetObjectType(OBJECT_TYPE _objectType) { this->mObjectType = _objectType; }
	void SetObjectName(const wstring& _objectName) { this->mObjectName = _objectName; }

	friend class EventManager;
};

