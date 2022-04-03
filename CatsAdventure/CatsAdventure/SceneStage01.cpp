#include "pch.h"
#include "SceneStage01.h"

#include "GameCore.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "RandomManager.h"

#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterMouse.h"
#include "MonsterSpider.h"

#include "Texture.h"

SceneStage01::SceneStage01()
	:mMapWidth(TILE_SIZE * (float)tileWidthNumber)
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"Stage01", L"\\texture\\background\\background_stage_01.bmp"));
}
SceneStage01::~SceneStage01()
{

}

void SceneStage01::Enter()
{
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();

	// 타일 생성
	for (int i = 0; i < tileWidthNumber; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			Vector2f tilePosition = {};
			tilePosition.x = TILE_SIZE * i;
			tilePosition.y = mainResolution.y - (TILE_SIZE * (j+1));

			Tile* tile = new Tile;
			tile->SetPosition(tilePosition);
			AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
		}
	}

	for (int i = 0; i < 12; i++)
	{
		Vector2f tilePosition = {};
		tilePosition.x = 0.f;
		tilePosition.y = mainResolution.y - (TILE_SIZE * (i + 2));

		Tile* tile = new Tile;
		tile->SetPosition(tilePosition);
		AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
	}

	for (int i = 0; i < 12; i++)
	{
		Vector2f tilePosition = {};
		tilePosition.x = TILE_SIZE * (tileWidthNumber-1);
		tilePosition.y = mainResolution.y - (TILE_SIZE * (i + 2));

		Tile* tile = new Tile;
		tile->SetPosition(tilePosition);
		AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
	}

	// Set Player
	GameObject* player = new Player;
	player->SetPosition(Vector2f(100.f, 400.f));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	// Set Camera
	GameCamera::GetInstance()->SetLookAtPosition(Vector2f(player->GetPosition().x, mainResolution.y/2.0f), false);
	//GameCamera::GetInstance()->SetTargetOffset(Vector2f(0.f, player->GetPosition().y - mainResolution.y / 2.f));

	// Collision Check
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);

	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);

	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	// Init Random Manager
	RandomManager::GetInstance()->Init(this, player, 2.0f);
}

void SceneStage01::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneStage01::Update()
{
	vector<GameObject*> playerList = this->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	
	GameScene::Update();
	RandomManager::GetInstance()->Update();

	if (playerList.empty())
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_LOSE);
	}

	if (!playerList.empty())
	{
		if (playerList[0]->GetPosition().x >= (this->mMapWidth - 2*TILE_SIZE))
		{
			ChangeGameScene(SCENE_TYPE::SCENE_TYPE_END);
		}
	}
}

void SceneStage01::Render(HDC _bitmapDC)
{
	Texture* texture = GetTexture();

	int width = texture->GetBitmapInfoWidth();
	int height = texture->GetBitmapInfoHeight();

	// 복사
	BitBlt(_bitmapDC,
		0, 0,
		width, height,
		texture->GetDC(),
		0, 0,
		SRCCOPY);

	// 오브젝트
	GameScene::Render(_bitmapDC);
}