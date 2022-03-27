#pragma once
#include "GameObject.h"

const Vector2f playerScale = { 64.f, 64.f };

class Texture;

class Player :
	public GameObject
{
private:
	int		mHP;
	float	mSpeed;
	float	mJumpHeight;

public:
	Player();
	~Player();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	void CreateBullet();
	void CreateMissile();

	// get
	int		GetHP() { return this->mHP; }
	float	GetSpeed() { return this->mSpeed; }
	float	GetJumpHeight() { return this->mJumpHeight; }

	// set
	void SetHP(int _hp)
	{
		this->mHP = _hp;
		if (this->mHP <= 0)
		{
			RemoveGameObject(this);
		}
	}
	void SetSpeed(float _speed) { this->mSpeed = _speed; }
	void SetJumpHeight(float _jumpHeight) { this->mJumpHeight = _jumpHeight; }
};

