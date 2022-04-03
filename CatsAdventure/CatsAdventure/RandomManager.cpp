#include "pch.h"
#include <random>

#include "GameCore.h"
#include "RandomManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

#include "Player.h"
#include "GameTimer.h"
#include "Tile.h"
#include "MonsterFrog.h"
#include "MonsterMouse.h"
#include "MonsterSpider.h"
#include "GameScene.h"

RandomManager::RandomManager()
	:mAccumulatedTime(0.f), mUpdateDuration(3.f),
	mTarget(nullptr), mCurrentScene(nullptr)
{
}

RandomManager::~RandomManager()
{
}

void RandomManager::Init(GameScene* _currentScene, GameObject* _target, float _updateDuration)
{
	this->mCurrentScene = _currentScene;
	this->mTarget = _target;
	this->mUpdateDuration = _updateDuration;
}

void RandomManager::Update()
{
	if (this->mCurrentScene == nullptr
		|| this->mTarget == nullptr)
	{
		return;
	}

	this->mAccumulatedTime += (float)DELTA_TIME;

	if (this->mAccumulatedTime >= mUpdateDuration)
	{
		int createCount = CreateRandomNumber(1, 3);
		this->mAccumulatedTime = 0.f;

		for (int i = 0; i < createCount; ++i)
		{
			this->CreateRandomMonster();
			this->CreateRandomTile();
		}
	}
}

int RandomManager::CreateRandomNumber(int _minRange, int _maxRange)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(_minRange, _maxRange);

	return dis(gen);
}

Vector2f RandomManager::CreateRandomPosition()
{
	if (this->mTarget == nullptr)
	{
		return Vector2f(0.f, 0.f);
	}

	// TargetObject의 진행 방향에서 생성 되도록 설정
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	Vector2f randomPosition = this->mTarget->GetPosition();
	int randomPositionX = CreateRandomNumber((int)mainResolution.x / 2, (int)mainResolution.x);
	int randomPositionY = CreateRandomNumber(0, (int)mainResolution.y / 2);

	randomPosition.x += (float)randomPositionX;
	randomPosition.y -= (float)randomPositionY;

	return randomPosition;
}

void RandomManager::CreateRandomTile()
{
	int tileTypeNumber = TILE_TEXTURE_MAX_INDEX;
	int tileType = CreateRandomNumber(0, tileTypeNumber);
	Vector2f randomPosition = this->CreateRandomPosition();

	Tile* tile = new Tile;
	tile->SetTargetTextureIndex(tileType);
	tile->SetPosition(randomPosition);
	this->mCurrentScene->AddGameObject(tile, OBJECT_TYPE::OBJECT_TYPE_TILE);
}

void RandomManager::CreateRandomMonster()
{
	int monsterTypeNumber = (int)MONSTER_TYPE::MONSTER_TYPE_SIZE - 1;
	int monsterType = CreateRandomNumber(0, monsterTypeNumber);
	Vector2f randomPosition = this->CreateRandomPosition();

	switch (monsterType)
	{
	case (int)MONSTER_TYPE::MONSTER_TYPE_MOUSE:
	{
		MonsterMouse* monsterMouse = new MonsterMouse;
		monsterMouse->SetPosition(randomPosition);
		monsterMouse->SetOriginalPosition(monsterMouse->GetPosition());
		this->mCurrentScene->AddGameObject(monsterMouse, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
		break;
	}

	case (int)MONSTER_TYPE::MONSTER_TYPE_SPIDER:
	{
		MonsterSpider* monsterSpider = new MonsterSpider;
		monsterSpider->SetPosition(randomPosition);
		monsterSpider->SetOriginalPosition(monsterSpider->GetPosition());
		this->mCurrentScene->AddGameObject(monsterSpider, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
		break;
	}

	case (int)MONSTER_TYPE::MONSTER_TYPE_FROG:
	{
		MonsterFrog* monsterFrog = new MonsterFrog;
		monsterFrog->SetPosition(randomPosition);
		monsterFrog->SetOriginalPosition(monsterFrog->GetPosition());
		this->mCurrentScene->AddGameObject(monsterFrog, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
		break;
	}
	}
	

	
}
