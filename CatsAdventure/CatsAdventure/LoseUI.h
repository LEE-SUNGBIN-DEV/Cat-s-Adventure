#pragma once
#include "GameUI.h"
class LoseUI :
    public GameUI
{
private:

public:
	LoseUI();
	virtual ~LoseUI();

	virtual LoseUI* Clone() { return new LoseUI(*this); }
	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();
};

