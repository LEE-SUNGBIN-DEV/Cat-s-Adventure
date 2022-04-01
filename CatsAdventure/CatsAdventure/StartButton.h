#pragma once
#include "GameUI.h"
class StartButton :
    public GameUI
{
private:

public:
	StartButton();
	virtual ~StartButton();

	virtual StartButton* Clone() { return new StartButton(*this); }
	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();
};

