#pragma once
#include "GameObject.h"
class Texture;

class Monster :
	public GameObject
{
private:
	int	mHP;

	float mSpeed;
	float mPatrolDistance;
	
	bool mReturnOriginalPosition;

	Vector2f mOriginalPosition;

public:
	Monster();
	~Monster();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	virtual Monster* Clone() { return new Monster(*this); }

	// get
	int		GetHP() { return this->mHP; }
	float	GetSpeed() { return this->mSpeed; }
	float	GetPatrolDistance() { return this->mPatrolDistance; }

	// set
	void inline SetHP(int _hp)
	{
		this->mHP = _hp;
		if (this->mHP <= 0)
		{
			RemoveGameObject(this);
		}
	};
	void SetSpeed(float _speed) { this->mSpeed = _speed; }
	void SetOriginalPosition(Vector2f _originalPosition) { this->mOriginalPosition = _originalPosition; }
	void SetPatrolDistance(float _patrolDistance) { this->mPatrolDistance = _patrolDistance; }
};

