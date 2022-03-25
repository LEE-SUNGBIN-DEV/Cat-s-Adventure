#include "pch.h"
#include "SceneManager.h"
#include "GameSceneStart.h"

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
	
	// 현재 씬 저장
	this->mCurrentScene = mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_START];
	this->mCurrentScene->EnterScene();
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