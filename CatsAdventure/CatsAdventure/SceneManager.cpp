#include "pch.h"
#include "SceneManager.h"
#include "GameSceneStart.h"
#include "SceneTool.h"

SceneManager::SceneManager()
	:mGameSceneList(), mCurrentScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::SCENE_TYPE_SIZE; i++)
	{
		if (mGameSceneList != nullptr)
		{
			delete mGameSceneList[i];
		}
	}
}

void SceneManager::Init()
{
	// Scene 생성
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START] = new GameSceneStart();
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START]->SetName(L"Start Scene");
	
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_TOOL] = new SceneTool;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START]->SetName(L"Scene Tool");
	
	//this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_STAGE_01] = new SceneStage01;
	//this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_STAGE_02] = new SceneStage02;

	// 현재 씬 저장
	this->mCurrentScene = mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START];
	this->mCurrentScene->Enter();
}

void SceneManager::Update()
{
	this->mCurrentScene->Update();
	this->mCurrentScene->LateUpdate();
}

void SceneManager::Render(HDC _bitmapDC)
{
	this->mCurrentScene->Render(_bitmapDC);
}

void SceneManager::ChangeScene(SCENE_TYPE _sceneType)
{
	this->mCurrentScene->Exit();
	this->mCurrentScene = this->mGameSceneList[(UINT)_sceneType];
	this->mCurrentScene->Enter();
}
