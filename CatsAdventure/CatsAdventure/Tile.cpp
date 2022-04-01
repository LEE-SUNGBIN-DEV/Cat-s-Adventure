#include "pch.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Texture.h"

Tile::Tile()
{
	this->SetScale(Vector2f(TILE_SIZE, TILE_SIZE));
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"Tile Stone", L"\\texture\\tile\\tile_stone.bmp"));
}

Tile::~Tile()
{
}

void Tile::Render(HDC _bitmapDC)
{
	if (this->GetTexture() == nullptr)
	{
		return;
	}

	else
	{
		Vector2f renderPosition = this->GetPosition();
		Vector2f tileScale = this->GetScale();
		renderPosition = GameCamera::GetInstance()->GetRenderPosition(renderPosition);

		BitBlt(_bitmapDC,
			(int)renderPosition.x, (int)renderPosition.y,
			TILE_SIZE, TILE_SIZE,
			this->GetTexture()->GetDC(),
			0, 0,
			SRCCOPY);
	}
}

void Tile::Update()
{
}



