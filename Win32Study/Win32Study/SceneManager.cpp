#include "pch.h"
#include "SceneManager.h"
#include "GameSceneStart.h"

SceneManager::SceneManager()
	:gameSceneList(), curScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::SCENE_TYPE_SIZE; i++)
	{
		if (gameSceneList != nullptr)
		{
			delete gameSceneList[i];
		}
	}
}

void SceneManager::Init()
{
	// Scene 생성
	this->gameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START] = new GameSceneStart();
	this->gameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START]->SetName(L"Start Scene");
	
	// 현재 씬 저장
	this->curScene = gameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START];
	this->curScene->EnterScene();
}

void SceneManager::Update()
{
	this->curScene->Update();
}

void SceneManager::Render(HDC _bitmapDC)
{
	this->curScene->Render(_bitmapDC);
}