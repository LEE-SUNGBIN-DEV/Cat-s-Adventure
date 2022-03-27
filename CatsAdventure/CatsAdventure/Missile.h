#pragma once
#include "Projectile.h"

#define MISSILE_UP_HEIGHT 150.f
#define MISSILE_UP_SPEED 400.f
#define MISSILE_GUIDED_SPEED 600.f

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

    // get
    int GetDamage() { return this->mDamage; }

    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
};

