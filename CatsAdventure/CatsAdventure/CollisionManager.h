#pragma once

class Collider;

class CollisionManager
{
private:
	UINT	mCollisionMatrix[(UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE];

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
	void GenerateCollision(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB);
	bool IsCollision(Collider* _objectA, Collider* _objectB);
};

