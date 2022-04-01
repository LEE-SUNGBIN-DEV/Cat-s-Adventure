#include "pch.h"
#include "SceneStage01.h"

#include "GameCore.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"

#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterMouse.h"
#include "MonsterSpider.h"

#include "Texture.h"

SceneStage01::SceneStage01()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"Back Ground", L"\\texture\\background_stage_01.bmp"));
}
SceneStage01::~SceneStage01()
{

}

void SceneStage01::Enter()
{
	// Set Camera
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.f, false);

	// 타일 생성
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			Vector2f tilePosition = {};
			tilePosition.x = TILE_SIZE * i;
			tilePosition.y = mainResolution.y - (TILE_SIZE * j) - TILE_SIZE;

			Tile* tile = new Tile;
			tile->SetPosition(tilePosition);
			AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
		}
	}

	for (int i = 0; i < 12; i++)
	{
		Vector2f tilePosition = {};
		tilePosition.x = 0.f;
		tilePosition.y = mainResolution.y - (TILE_SIZE * (i+2));

		Tile* tile = new Tile;
		tile->SetPosition(tilePosition);
		AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
	}

	// Set Player
	GameObject* player = new Player;
	player->SetPosition(Vector2f(100.f, mainResolution.y - (TILE_SIZE + playerScale.y)));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	GameCamera::GetInstance()->SetTargetOffset(Vector2f(0.f, player->GetPosition().y - mainResolution.y / 2.f));

	// Set Monster
	MonsterMouse* monsterMouse00 = new MonsterMouse;
	monsterMouse00->SetPosition(Vector2f(900.f, 621.f));
	monsterMouse00->SetOriginalPosition(monsterMouse00->GetPosition());
	AddGameObject(monsterMouse00, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	MonsterSpider* monsterSpider00 = new MonsterSpider;
	monsterSpider00->SetPosition(Vector2f(900.f, 25.f));
	monsterSpider00->SetOriginalPosition(monsterSpider00->GetPosition());
	AddGameObject(monsterSpider00, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	MonsterSpider* monsterSpider01 = new MonsterSpider;
	monsterSpider01->SetPosition(Vector2f(800.f, 25.f));
	monsterSpider01->SetOriginalPosition(monsterSpider01->GetPosition());
	AddGameObject(monsterSpider01, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	MonsterSpider* monsterSpider02 = new MonsterSpider;
	monsterSpider02->SetPosition(Vector2f(700.f, 25.f));
	monsterSpider02->SetOriginalPosition(monsterSpider01->GetPosition());
	AddGameObject(monsterSpider02, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	// Collision Check
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	//CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_TILE, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);

}

void SceneStage01::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
	ChangeGameScene(SCENE_TYPE::SCENE_TYPE_END);
}

void SceneStage01::Update()
{
	GameScene::Update();
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