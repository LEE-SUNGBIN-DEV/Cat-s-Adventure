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
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.f);

	// 타일 생성
	for (UINT i = 0; i < 20; ++i)
	{
		for (UINT j = 0; j < 2; ++j)
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
}

void SceneTool::Update()
{
	GameScene::Update();
}
