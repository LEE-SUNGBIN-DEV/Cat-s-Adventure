#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
private:
	float mSpeed;
	float mPatrolDistance;
	
	int mMoveDirection;

	bool mReturnOriginalPosition;

	Vector2f mOriginalPosition;
public:
	Monster();
	~Monster();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	// get
	float GetSpeed() { return this->mSpeed; }
	float GetPatrolDistance() { return this->mPatrolDistance; }
	int GetMoveDirection() { return this->mMoveDirection; }

	// set
	void SetSpeed(float _speed) { this->mSpeed = _speed; }
	void SetMoveDirection(int _moveDirection) { this->mMoveDirection = _moveDirection; }
	void SetOriginalPosition(Vector2f _originalPosition) { this->mOriginalPosition = _originalPosition; }
	void SetPatrolDistance(float _patrolDistance) { this->mPatrolDistance = _patrolDistance; }
};

