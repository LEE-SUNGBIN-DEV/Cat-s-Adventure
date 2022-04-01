#pragma once
#include "GameUI.h"
class TitleUI :
    public GameUI
{
private:

public:
	TitleUI();
	virtual ~TitleUI();

	virtual TitleUI* Clone() { return new TitleUI(*this); }
	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();
};

