#pragma once
#include "GameObject.h"

// Åõ»çÃ¼
class Projectile :
    public GameObject
{
private:
    float mTheta;
    float mSpeed;

public:
    Projectile();
    virtual ~Projectile();

    virtual void Update() = 0;
    virtual void Render(HDC _bitmapDC) = 0;

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    // get
    float       GetTheta() { return this->mTheta; }
    float       GetSpeed() { return this->mSpeed; }

    // set
    void SetTheta(float _theta) { this->mTheta = _theta; }
    void SetSpeed(float _speed) { this->mSpeed = _speed; }
};

