#pragma once
#include "GameObject.h"

const int TILE_SIZE = 64;

class Tile :
    public GameObject
{
private:


public:
    Tile();
    ~Tile();

    virtual void Render(HDC _bitmapDC);
    virtual void Update();

    virtual Tile* Clone() { return new Tile(*this); }
};

