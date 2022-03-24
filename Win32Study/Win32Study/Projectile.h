#pragma once
#include "GameObject.h"
class Projectile :
    public GameObject
{
private:
    int mDirection;

    float mSpeed;

public:
    Projectile();
    ~Projectile();

    virtual void Update() = 0;
    virtual void Render(HDC _bitmapDC) = 0;

    // get
    int GetDirection() { return this->mDirection; }
    int GetSpeed() { return this->mSpeed; }

    // set
    void SetDirection(int _direction) { this->mDirection = _direction; }
    void SetSpeed(int _speed) { this->mSpeed = _speed; }
};

