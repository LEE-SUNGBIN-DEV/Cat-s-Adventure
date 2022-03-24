#pragma once
#include "GameObject.h"
class Projectile :
    public GameObject
{
private:
    float mTheta;

    float mSpeed;

public:
    Projectile();
    ~Projectile();

    virtual void Update() = 0;
    virtual void Render(HDC _bitmapDC) = 0;

    // get
    float GetTheta() { return this->mTheta; }
    int GetSpeed() { return this->mSpeed; }

    // set
    void SetTheta(int _theta) { this->mTheta = _theta; }
    void SetSpeed(int _speed) { this->mSpeed = _speed; }
};

