#pragma once
#include "GameScene.h"

class SceneStage01 :
	public GameScene
{
private:

public:
	SceneStage01();
	~SceneStage01();

	virtual void Render(HDC _bitmapDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

