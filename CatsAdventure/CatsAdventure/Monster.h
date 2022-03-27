#pragma once
#include "GameObject.h"
class Texture;

class Monster :
	public GameObject
{
private:
	int	mHP;
	int	mMoveDirection;

	float mSpeed;
	float mPatrolDistance;
	
	bool mReturnOriginalPosition;

	Vector2f mOriginalPosition;

public:
	Monster();
	~Monster();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	// get
	int GetHP() { return this->mHP; }
	float GetSpeed() { return this->mSpeed; }
	float GetPatrolDistance() { return this->mPatrolDistance; }
	int GetMoveDirection() { return this->mMoveDirection; }

	// set
	void SetHP(int _hp) { this->mHP = _hp; };
	void SetSpeed(float _speed) { this->mSpeed = _speed; }
	void SetMoveDirection(int _moveDirection) { this->mMoveDirection = _moveDirection; }
	void SetOriginalPosition(Vector2f _originalPosition) { this->mOriginalPosition = _originalPosition; }
	void SetPatrolDistance(float _patrolDistance) { this->mPatrolDistance = _patrolDistance; }
};

