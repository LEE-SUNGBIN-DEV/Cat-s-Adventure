#include "pch.h"
#include "GameSceneStart.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"

GameSceneStart::GameSceneStart()
{

}
GameSceneStart::~GameSceneStart()
{

}

void GameSceneStart::EnterScene()
{
	// Player
	GameObject* player = new Player;

	player->SetPos(Vector2f(50.f, 621.f));
	player->SetScale(Vector2f(50.f, 50.f));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	// Map
	Monster* monster = new Monster;

	monster->SetPos(Vector2f(900.f, 621.f));
	monster->SetScale(Vector2f(50.f, 50.f));
	AddGameObject(monster, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
}

void GameSceneStart::ExitScene()
{
}
