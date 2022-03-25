#pragma once
#include "GameObject.h"
class Projectile :
    public GameObject
{
private:
    float mTheta;
    float mSpeed;

    Vector2f mDirection;

public:
    Projectile();
    ~Projectile();

    virtual void Update() = 0;
    virtual void Render(HDC _bitmapDC) = 0;

    // get
    float GetTheta() { return this->mTheta; }
    float GetSpeed() { return this->mSpeed; }
    Vector2f GetDirection() { return this->mDirection; }

    // set
    void SetTheta(float _theta) { this->mTheta = _theta; }
    void SetSpeed(float _speed) { this->mSpeed = _speed; }
    void SetDirection(Vector2f _direction);
};

