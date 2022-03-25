#pragma once
#include "Projectile.h"

class Texture;

class Bullet :
    public Projectile
{
private:
    int mDamage;
    Texture* mTexture;

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

