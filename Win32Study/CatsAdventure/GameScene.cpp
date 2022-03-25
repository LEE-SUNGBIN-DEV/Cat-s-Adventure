#include "pch.h"
#include "GameScene.h"
#include "GameObject.h"

GameScene::GameScene()
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
			this->mGameObjectList[i][j]->Update();
		}
	}
}

void GameScene::Render(HDC _bitmapDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->mGameObjectList[i].size(); ++j)
		{
			this->mGameObjectList[i][j]->Render(_bitmapDC);
		}
	}
}
