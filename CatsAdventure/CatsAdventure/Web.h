#pragma once
#include "Projectile.h"
class Web :
	public Projectile
{
private:
    int mDamage;

    Vector2f mTargetPosition;

public:
    Web();
    ~Web();

    virtual void Update();
    virtual void Render(HDC _bitmapDC);

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    virtual Web* Clone() { return new Web(*this); }

    // get
    int GetDamage() { return this->mDamage; }
    Vector2f GetTargetDirection() { return this->mTargetPosition; }

    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
    void SetTargetPosition(Vector2f _targetPosition) { this->mTargetPosition = _targetPosition; }
};

