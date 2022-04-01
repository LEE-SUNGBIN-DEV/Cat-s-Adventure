#pragma once
#include "GameObject.h"

class GameUI :
    public GameObject
{
private:
	wstring mUIName;

public:
	GameUI();
	virtual ~GameUI();

	void Update();

	virtual void Render(HDC _bitmapDC);
	virtual void OnMouseClick();

	// get
	const wstring& GetUIName() { return this->mUIName; }

	// set
	void SetUIName(const wstring& _uiName) { this->mUIName = _uiName; }
};

