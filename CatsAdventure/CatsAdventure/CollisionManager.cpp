#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
	:mCollisionMatrix{}
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++row)
	{
		for (UINT col = row; col < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++col)
		{
			if (mCollisionMatrix[row] & (1 << col))
			{
				GenerateCollision((OBJECT_TYPE)row, (OBJECT_TYPE)col);
			}
		}
	}
}

void CollisionManager::GenerateCollision(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB)
{
	GameScene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
	
	const vector<GameObject*>& objectTypeA = currentScene->GetGameObjectList(_objectTypeA);
	const vector<GameObject*>& objectTypeB = currentScene->GetGameObjectList(_objectTypeB);

	for (size_t i = 0; i < objectTypeA.size(); ++i)
	{
		// Collider를 보유하지 않은 경우
		if (objectTypeA[i]->GetCollider() == nullptr)
		{
			continue;
		}

		for (size_t j = 0; j < objectTypeB.size(); ++j)
		{
			// Collider를 보유하지 않은 경우, 자기 자신일 경우
			if (objectTypeB[j]->GetCollider() == nullptr
				|| objectTypeA[i] == objectTypeB[j])
			{
				continue;
			}

			if (this->IsCollision(objectTypeA[i]->GetCollider(), objectTypeB[j]->GetCollider()))
			{

			}
		}
	}

}

bool CollisionManager::IsCollision(Collider* _objectA, Collider* _objectB)
{

	return false;
}

void CollisionManager::ConnectCollisionMatrix(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB)
{
	// enum값 중 작은 값을 row(행), 큰 값을 col(열) 
	UINT row = (UINT)_objectTypeA;
	UINT col = (UINT)_objectTypeB;

	if (row > col)
	{
		row = (UINT)_objectTypeB;
		col = (UINT)_objectTypeA;
	}

	if (mCollisionMatrix[row] & (1 << col))
	{
		// 비트 반전 후 AND 연산 
		mCollisionMatrix[row] &= ~(1 << col);
	}
	else
	{
		mCollisionMatrix[row] |= (1 << col);
	}

}

void CollisionManager::ClearCollisionMatrix()
{
	memset(mCollisionMatrix, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE);
}