#pragma once
class GameTimer
{
private:
	static UINT generateID;

	UINT		mID;
	GameObject* mOwner;	// �� ������Ʈ�� ������

	float		mCountTime;
	float		mTargetTime;

public:
	GameTimer();
	~GameTimer();

	bool Timer();

	// get
	UINT		GetID() { return this->mID; }
	GameObject* GetOwner() { return this->mOwner; }

	// set
	void SetOwner(GameObject* _owner) { this->mOwner = _owner; }
	void SetTargetTime(float _targetTime) { this->mTargetTime = _targetTime; }
};

