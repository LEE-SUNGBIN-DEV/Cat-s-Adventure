#pragma once
#include "Monster.h"

#define SPIDER_ATTACK_DELAY 2.0f

class MonsterSpider :
	public Monster
{
private:
	float mAttackDelay;

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

	// get
	float GetAttackDelay() { return this->mAttackDelay; }

	// set
	void SetAttackDelay(float _attackDelay) { this->mAttackDelay = _attackDelay; }
};

