#include "pch.h"
#include "SceneManager.h"
#include "SceneStart.h"
#include "SceneStage01.h"
#include "SceneEnd.h"
#include "SceneLose.h"
#include "SceneTool.h"

SceneManager::SceneManager()
	:mGameSceneList(), mCurrentScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::SCENE_TYPE_SIZE; ++i)
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
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_TOOL] = new SceneTool;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_TOOL]->SetName(L"Scene Tool");

	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START] = new SceneStart;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START]->SetName(L"Game Start");
	
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_STAGE_01] = new SceneStage01;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_STAGE_01]->SetName(L"Stage 01");

	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_END] = new SceneEnd;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_END]->SetName(L"Game End");

	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_LOSE] = new SceneLose;
	this->mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_LOSE]->SetName(L"Game Over");

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
