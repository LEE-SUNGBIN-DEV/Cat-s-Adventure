#pragma once

class GameObject
{
private:
	POINT pos;
	POINT scale;

public:
	// ������
	GameObject();
	GameObject(POINT _ltPos, POINT _rbPos) :GameObject;

	// get
	POINT GetPos();
	POINT GetScale();

	// set
	void SetPos(POINT _pos);
	void SetScale(POINT _scale);
};

