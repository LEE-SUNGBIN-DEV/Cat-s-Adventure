#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"

Bullet::Bullet()
	: mDamage(1)
{
	// Load Texture
	this->mTexture
		= ResourceManager::GetInstance()->LoadTexture(L"FISH_BULLET", L"\\texture\\fishBullet.bmp");
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{

	Vector2f projectilePosition = GetPosition();

	projectilePosition.x += this->GetDirection().x * this->GetSpeed() * (float)DELTA_TIME;
	projectilePosition.y -= this->GetDirection().y * this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Bullet::Render(HDC _bitmapDC)
{
	int width = (int)this->mTexture->GetBitmapInfoWidth();
	int height = (int)this->mTexture->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		mTexture->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);
}
