#pragma once
#include "GameScene.h"
class GameSceneStart :
	public GameScene
{
private:

public:
	GameSceneStart();
	~GameSceneStart();

	virtual void EnterScene();
	virtual void ExitScene();
};

