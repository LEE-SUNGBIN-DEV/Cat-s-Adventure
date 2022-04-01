#include "pch.h"
#include "SceneTool.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "GameCamera.h"
#include "GameCore.h"
#include "Tile.h"

SceneTool::SceneTool()
{
}

SceneTool::~SceneTool()
{
}

void SceneTool::Enter()
{	
	// Set Camera
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.f, false);

	// Ÿ�� ����
	for (UINT i = 0; i < 20; ++i)
	{
		for (UINT j = 0; j < 1; ++j)
		{
			Vector2f tilePosition;
			tilePosition.x = TILE_SIZE * i;
			tilePosition.y = mainResolution.y - (TILE_SIZE * j) - TILE_SIZE;

			Tile* tile = new Tile;
			tile->SetPosition(tilePosition);
			AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
		}
	}

}

void SceneTool::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneTool::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_ENTER, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_START);
	}
}
