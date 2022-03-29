#pragma once
#include "Projectile.h"

const Vector2f missileBitmapScale = { 60.f, 60.f };
const Vector2f missileColliderScale = { 30.f, 30.f };
const float missileSpeed = 300.f;
const float missileDamage = 10.f;

const float missileUpHeight = 150.f;
const float missileUpSpeed = 400.f;
const float missileGuidedSpeed = 600.f;

enum
{
    MISSILE_STATE_NONE,
    MISSILE_STATE_UP,
    MISSILE_STATE_GUIDED
};

class Missile :
    public Projectile
{
private:
    int mDamage;
    int mMissileState;

    float mUpHeight;

public:
    Missile();
    ~Missile();

    virtual void Update();
    virtual void Render(HDC _bitmapDC);

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    virtual Missile* Clone() { return new Missile(*this); }

    // get
    int GetDamage() { return this->mDamage; }

    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
};

