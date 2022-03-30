#include "pch.h"
#include "SceneStart.h"

#include "GameCore.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterMouse.h"
#include "MonsterSpider.h"

#include "PathManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameCamera.h"

SceneStart::SceneStart()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND", L"\\texture\\backgroundStart.bmp"));

}
SceneStart::~SceneStart()
{

}

void SceneStart::Enter()
{
	// Set Player
	GameObject* player = new Player;
	player->SetPosition(Vector2f(100.f, 621.f));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	GameCamera::GetInstance()->SetTargetObject(player);

	// Set Monster
	MonsterMouse* monsterMouse = new MonsterMouse;
	monsterMouse->SetPosition(Vector2f(900.f, 621.f));
	monsterMouse->SetOriginalPosition(monsterMouse->GetPosition());
	AddGameObject(monsterMouse, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

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
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	// Set Camera
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.f);
}

void SceneStart::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneStart::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_ENTER, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_STAGE_01);
	}
		
}

void SceneStart::Render(HDC _bitmapDC)
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