#pragma once

class Collider;

union COLLIDER_ID
{
	struct
	{
		UINT mLeftID;
		UINT mRightID;
	};
	ULONGLONG ID;
};

class CollisionManager
{
private:
	map<ULONGLONG, bool>	mCollisionInfo;
	UINT					mCollisionMatrix[(UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE];

	CollisionManager();
	~CollisionManager();

public:
	static CollisionManager* GetInstance()
	{
		static CollisionManager manager;
		return &manager;
	}

	void Init();
	void Update();
	void ConnectCollisionMatrix(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB);
	void ClearCollisionMatrix();
	void CheckCollisionCondition(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB);
	bool IsCollision(Collider* _objectA, Collider* _objectB);
};

