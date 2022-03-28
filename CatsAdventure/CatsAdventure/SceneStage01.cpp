#include "pch.h"
#include "SceneStage01.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Monster.h"
#include "Texture.h"

SceneStage01::SceneStage01()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND", L"\\texture\\backgroundStage01.bmp"));

}
SceneStage01::~SceneStage01()
{

}

void SceneStage01::Enter()
{
	// Player
	GameObject* player = new Player;

	player->SetPosition(Vector2f(50.f, 621.f));
	player->SetScale(Vector2f(50.f, 50.f));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	// Monster
	Monster* monster = new Monster;

	monster->SetPosition(Vector2f(900.f, 621.f));
	monster->SetScale(Vector2f(50.f, 50.f));
	monster->SetOriginalPosition(monster->GetPosition());
	AddGameObject(monster, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	// Collision Check
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);

}

void SceneStage01::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneStage01::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_ENTER, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_START);
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