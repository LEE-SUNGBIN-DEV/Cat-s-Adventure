#pragma once
#include "GameUI.h"
class ExitButton :
    public GameUI
{
private:

public:
	ExitButton();
	virtual ~ExitButton();

	virtual ExitButton* Clone() { return new ExitButton(*this); }
	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();
};

