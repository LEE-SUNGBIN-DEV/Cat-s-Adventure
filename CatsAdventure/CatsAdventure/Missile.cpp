#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"

Missile::Missile()
	: mDamage(10)
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SHARK_MISSILE", L"\\texture\\sharkMissile_right.bmp"));
	
	// Create Collider
	this->CreateCollider();
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vector2f projectilePosition = GetPosition();

	projectilePosition.x += this->GetDirection().x * this->GetSpeed() * (float)DELTA_TIME;
	projectilePosition.y -= this->GetDirection().y * this->GetSpeed() * (float)DELTA_TIME;

	SetPosition(projectilePosition);
}

void Missile::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		this->GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);
}
