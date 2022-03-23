#pragma once

class GameObject
{
private:
	POINT pos;
	POINT scale;

public:
	// »ý¼ºÀÚ
	GameObject();
	GameObject(POINT _ltPos, POINT _rbPos) :GameObject;

	// get
	POINT GetPos();
	POINT GetScale();

	// set
	void SetPos(POINT _pos);
	void SetScale(POINT _scale);
};

