#pragma once

class GameObject;

const float GRAVITY_ACCELERATION = 1.2f;

class Gravity
{
private:
	GameObject* mOwner;	// 이 컴포넌트의 소유자

	bool mIsGround;
	float mFallSpeed;

public:
	Gravity();
	Gravity(const Gravity& _origin);
	~Gravity();

	void LateUpdate();

	// get
	bool IsGround() { return this->mIsGround; }
	GameObject* GetOwner() { return this->mOwner; }

	// set
	void SetIsGround(bool _isGround) { this->mIsGround = _isGround; }
	void SetOwner(GameObject* _owner) { this->mOwner = _owner; }
};

