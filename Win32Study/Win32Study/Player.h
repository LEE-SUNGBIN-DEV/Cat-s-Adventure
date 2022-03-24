#pragma once
#include "GameObject.h"

class Player :
	public GameObject
{
private:

public:
	virtual void Update();
	virtual void Render(HDC _bitmapDC);
};

