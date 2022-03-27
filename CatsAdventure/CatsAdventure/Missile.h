#pragma once
#include "Projectile.h"
class Missile :
    public Projectile
{
private:
    int mDamage;

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

