#pragma once
#include "GameScene.h"
class SceneStart :
	public GameScene
{
private:

public:
	SceneStart();
	~SceneStart();

	virtual void Render(HDC _bitmapDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

