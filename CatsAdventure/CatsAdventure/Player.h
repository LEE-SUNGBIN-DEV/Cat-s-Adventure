#pragma once
#include "GameObject.h"

const float		playerJumpPower = 150.f;
const float		playerJumpSpeed = 400.f;
const Vector2f	playerScale = { 64.f, 64.f };

enum
{
	PLAYER_JUMP_NONE,
	PLAYER_JUMP_PROGRESS,
	PLAYER_JUMP_FALL
};

class Texture;

class Player :
	public GameObject
{
private:
	int		mHP;

	int		mIsJump; // 0: 동작 없음, 1: 점프 중, 2: 하강 중
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

	virtual Player* Clone() { return new Player(*this); }

	void JumpChecking(Vector2f* _updatePosition);
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

