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
				CheckCollisionCondition((OBJECT_TYPE)row, (OBJECT_TYPE)col);
			}
		}
	}
}

void CollisionManager::CheckCollisionCondition(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB)
{
	GameScene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
	
	const vector<GameObject*>& objectTypeA = currentScene->GetGameObjectList(_objectTypeA);
	const vector<GameObject*>& objectTypeB = currentScene->GetGameObjectList(_objectTypeB);
	
	COLLIDER_ID CombinationID;
	map<ULONGLONG, bool>::iterator iter;
	Collider* colliderA = nullptr;
	Collider* colliderB = nullptr;

	for (size_t i = 0; i < objectTypeA.size(); ++i)
	{
		colliderA = objectTypeA[i]->GetCollider();
		// Collider�� �������� ���� ���
		if (colliderA == nullptr)
		{
			continue;
		}

		for (size_t j = 0; j < objectTypeB.size(); ++j)
		{
			colliderB = objectTypeB[j]->GetCollider();

			// Collider�� �������� ���� ���, Ȥ�� �ڱ� �ڽ��� ���
			if (colliderB == nullptr
				|| objectTypeA[i] == objectTypeB[j])
			{
				continue;
			}

			// Collider ���� ID�� ����
			CombinationID.mLeftID = colliderA->GetID();
			CombinationID.mRightID = colliderB->GetID();
			
			iter = mCollisionInfo.find(CombinationID.ID);
			
			// First Collision, Add Info to Map
			if (iter == mCollisionInfo.end())
			{
				mCollisionInfo.insert(make_pair(CombinationID.ID, false));
				iter = mCollisionInfo.find(CombinationID.ID);
			}

			// Collision �߻�
			if (this->IsCollision(colliderA, colliderB))
			{
				// ���� �����ӿ� Collision �߻�
				if (iter->second)
				{
					// ������Ʈ�� Remove ������ ���
					if (objectTypeA[i]->IsAlive() == false
						|| objectTypeB[j]->IsAlive() == false)
					{
						colliderA->OnCollisionExit(colliderB);
						colliderB->OnCollisionExit(colliderA);
						iter->second = false;
					}

					else
					{
						colliderA->OnCollision(colliderB);
						colliderB->OnCollision(colliderA);
						iter->second = true;
					}
				}

				// ���� �����ӿ� Collision �߻����� ����
				else
				{
					if (objectTypeA[i]->IsAlive()
						&& objectTypeB[j]->IsAlive())
					{

						colliderA->OnCollisionEnter(colliderB);
						colliderB->OnCollisionEnter(colliderA);
						iter->second = true;
					}
				}
			}

			// Collision �߻����� ����
			else
			{
				// ���� �����ӿ� Collision �߻�
				if (iter->second)
				{
					colliderA->OnCollisionExit(colliderB);
					colliderB->OnCollisionExit(colliderA);
					iter->second = false;
				}
			}
		}
	}

}

bool CollisionManager::IsCollision(Collider* _objectA, Collider* _objectB)
{
	Vector2f positionA = _objectA->GetPosition();
	Vector2f positionB = _objectB->GetPosition();
	Vector2f scaleA = _objectA->GetScale();
	Vector2f scaleB = _objectB->GetScale();

	if (abs(positionA.x - positionB.x) < abs(scaleA.x + scaleB.x)
		&& abs(positionA.y - positionB.y) < abs(scaleA.y + scaleB.y))
	{
		return true;
	}

	else
	{
		return false;
	}
}

void CollisionManager::ConnectCollisionMatrix(OBJECT_TYPE _objectTypeA, OBJECT_TYPE _objectTypeB)
{
	// enum�� �� ���� ���� row(��), ū ���� col(��) 
	UINT row = (UINT)_objectTypeA;
	UINT col = (UINT)_objectTypeB;

	if (row > col)
	{
		row = (UINT)_objectTypeB;
		col = (UINT)_objectTypeA;
	}

	if (mCollisionMatrix[row] & (1 << col))
	{
		// ��Ʈ ���� �� AND ���� 
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