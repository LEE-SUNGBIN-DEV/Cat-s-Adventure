#pragma once
#include "GameObject.h"

const int TILE_SIZE = 64;
const int TILE_TEXTURE_MAX_INDEX = 15;

class Tile :
    public GameObject
{
private:
    int mTargetTextureIndex;

public:
    Tile();
    ~Tile();

    virtual void Render(HDC _bitmapDC);
    virtual void Update();

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    virtual Tile* Clone() { return new Tile(*this); }

    // get

    // set
    void SetTargetTextureIndex(int _index) { this->mTargetTextureIndex = _index; }
};

