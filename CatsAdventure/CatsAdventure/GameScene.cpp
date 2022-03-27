#include "pch.h"
#include "GameScene.h"
#include "GameObject.h"

GameScene::GameScene()
	:mTexture(nullptr)
{

}
GameScene::~GameScene()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->mGameObjectList[i].size(); ++j)
		{
			delete this->mGameObjectList[i][j];
		}
	}
}

void GameScene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->mGameObjectList[i].size(); ++j)
		{
			if (this->mGameObjectList[i][j]->GetIsAlive() == true)
			{
				this->mGameObjectList[i][j]->Update();
			}
		}
	}
}

void GameScene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->mGameObjectList[i].size(); ++j)
		{
			this->mGameObjectList[i][j]->LateUpdate();
		}
	}
}

void GameScene::Render(HDC _bitmapDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		vector<GameObject*>::iterator iter = this->mGameObjectList[i].begin();

		for (; iter != this->mGameObjectList[i].end();)
		{
			if ((*iter)->GetIsAlive())
			{
				(*iter)->Render(_bitmapDC);
				++iter;
			}

			else
			{
				iter = this->mGameObjectList[i].erase(iter);
			}
		}
	}
}
