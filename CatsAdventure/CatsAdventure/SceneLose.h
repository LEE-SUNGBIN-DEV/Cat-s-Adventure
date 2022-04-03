#pragma once
#include "GameScene.h"
class SceneLose :
    public GameScene
{
private:

public:
	SceneLose();
	~SceneLose();

	virtual void Render(HDC _bitmapDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

