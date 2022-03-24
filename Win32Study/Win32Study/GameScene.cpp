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
		for (size_t j = 0; j < this->gameObjectList[i].size(); ++j)
		{
			delete this->gameObjectList[i][j];
		}
	}
}

void GameScene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->gameObjectList[i].size(); ++j)
		{
			this->gameObjectList[i][j]->Update();
		}
	}
}

void GameScene::Render(HDC _bitmapDC)
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE; ++i)
	{
		for (size_t j = 0; j < this->gameObjectList[i].size(); ++j)
		{
			this->gameObjectList[i][j]->Render(_bitmapDC);
		}
	}
}
