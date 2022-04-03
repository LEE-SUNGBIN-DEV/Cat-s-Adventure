#pragma once
#include "GameScene.h"

const int tileWidthNumber = 150;

class SceneStage01 :
	public GameScene
{
private:
	float mMapWidth;

public:
	SceneStage01();
	~SceneStage01();

	virtual void Render(HDC _bitmapDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

