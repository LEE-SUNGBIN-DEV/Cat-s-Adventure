#include "pch.h"
#include "SceneTool.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"

SceneTool::SceneTool()
{
}

SceneTool::~SceneTool()
{
}

void SceneTool::Enter()
{
}

void SceneTool::Exit()
{
}

void SceneTool::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_ENTER, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_START);
	}
}
