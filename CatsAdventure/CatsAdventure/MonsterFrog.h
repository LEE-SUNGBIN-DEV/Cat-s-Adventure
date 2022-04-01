#pragma once
#include "Monster.h"

const Vector2f monsterFrogScale = { 50.f, 50.f };
const float frogAttackDelay = 2.0f;

class MonsterFrog :
    public Monster
{
private:

public:
	MonsterFrog();
	~MonsterFrog();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	virtual MonsterFrog* Clone() { return new MonsterFrog(*this); }

	void CreateAcid();

};

