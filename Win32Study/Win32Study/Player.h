#pragma once
#include "GameObject.h"

class Player :
	public GameObject
{
private:
	float mSpeed;
	float mJumpHeight;


public:
	Player();
	~Player();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	void CreateBullet();

	// get
	float GetSpeed() { return this->mSpeed; }
	float GetJumpHeight() { return this->mJumpHeight; }

	// set
	void SetSpeed(float _speed) { this->mSpeed = _speed; }
	void SetJumpHeight(float _jumpHeight) { this->mJumpHeight = _jumpHeight; }
};

