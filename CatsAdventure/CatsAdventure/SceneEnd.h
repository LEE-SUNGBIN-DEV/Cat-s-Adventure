#pragma once
#include "GameScene.h"
class SceneEnd :
    public GameScene
{
private:

public:
	SceneEnd();
	~SceneEnd();

	virtual void Render(HDC _bitmapDC);
	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};

