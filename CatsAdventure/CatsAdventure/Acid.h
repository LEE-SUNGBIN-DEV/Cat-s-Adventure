#pragma once
#include "Projectile.h"

const Vector2f acidScale = { 35.f, 35.f };
const float acidSpeed = 500.f;
const int acidDamage = 25;

class Acid :
    public Projectile
{
private:
    int mDamage;

    Vector2f mTargetPosition;

public:
    Acid();
    ~Acid();

    virtual void Update();
    virtual void Render(HDC _bitmapDC);

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    virtual Acid* Clone() { return new Acid(*this); }

    // get
    int GetDamage() { return this->mDamage; }
    Vector2f GetTargetDirection() { return this->mTargetPosition; }

    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
    void SetTargetPosition(Vector2f _targetPosition) { this->mTargetPosition = _targetPosition; }

};

