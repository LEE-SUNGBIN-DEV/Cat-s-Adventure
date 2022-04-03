#pragma once
#include "GameUI.h"
class WinUI :
    public GameUI
{
private:

public:
	WinUI();
	virtual ~WinUI();

	virtual WinUI* Clone() { return new WinUI(*this); }
	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();
};

