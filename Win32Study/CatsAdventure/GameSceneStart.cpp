#include "pch.h"
#include "GameSceneStart.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Texture.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "Texture.h"

GameSceneStart::GameSceneStart()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND", L"\\texture\\background.bmp"));

}
GameSceneStart::~GameSceneStart()
{

}

void GameSceneStart::EnterScene()
{
	// 메인 해상도
	Vector2f resolution = GameCore::GetInstance()->GetMainResolution();

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

	
}

void GameSceneStart::ExitScene()
{
}

void GameSceneStart::Render(HDC _bitmapDC)
{
	Texture* texture = GetTexture();

	int width = texture->GetBitmapInfoWidth();
	int height = texture->GetBitmapInfoHeight();

	// 특정 색상 제외하고 복사
	BitBlt(_bitmapDC,
		0, 0,
		width, height,
		texture->GetDC(),
		0, 0,
		SRCCOPY);

	// 오브젝트
	GameScene::Render(_bitmapDC);
}