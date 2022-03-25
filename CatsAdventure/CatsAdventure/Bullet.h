#pragma once
#include "Projectile.h"

class Bullet :
    public Projectile
{
private:
    int mDamage;

public:
    Bullet();
    ~Bullet();

    virtual void Update();
    virtual void Render(HDC _bitmapDC);

    // get
    int GetDamage() { return this->mDamage; }
    
    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
};

