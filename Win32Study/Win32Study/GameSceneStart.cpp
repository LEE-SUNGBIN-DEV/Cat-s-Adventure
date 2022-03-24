#include "pch.h"
#include "GameSceneStart.h"
#include "GameObject.h"

GameSceneStart::GameSceneStart()
{

}
GameSceneStart::~GameSceneStart()
{

}

void GameSceneStart::EnterScene()
{
	GameObject* gameObject = new GameObject();

	gameObject->SetPos(Vector2f(50.f, 621.f));
	gameObject->SetScale(Vector2f(50.f, 50.f));
	AddGameObject(gameObject, OBJECT_TYPE::OBJECT_TYPE_DEFALUT);
}

void GameSceneStart::ExitScene()
{
}
