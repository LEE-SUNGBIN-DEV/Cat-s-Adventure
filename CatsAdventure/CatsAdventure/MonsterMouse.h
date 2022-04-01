#pragma once
#include "Monster.h"

const Vector2f monsterMouseScale = { 50.f, 50.f };

class MonsterMouse :
	public Monster
{
private:
	int mDamage;

public:
	MonsterMouse();
	~MonsterMouse();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	virtual MonsterMouse* Clone() { return new MonsterMouse(*this); }
};

