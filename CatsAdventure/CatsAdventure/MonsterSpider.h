#pragma once
#include "Monster.h"

const Vector2f monsterSpiderScale = { 50.f, 50.f };
const float spiderAttackDelay = 3.0f;

class MonsterSpider :
	public Monster
{
private:

public:
	MonsterSpider();
	~MonsterSpider();

	virtual void Update();
	virtual void Render(HDC _bitmapDC);

	virtual void OnCollision(Collider* _opponent);
	virtual void OnCollisionEnter(Collider* _opponent);
	virtual void OnCollisionExit(Collider* _opponent);

	virtual MonsterSpider* Clone() { return new MonsterSpider(*this); }

	void CreateWeb();
};

