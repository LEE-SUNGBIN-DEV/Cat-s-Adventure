#pragma once
#include "GameScene.h"

class SceneTool :
	public GameScene
{
private:

public:
	SceneTool();
	~SceneTool();

	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

