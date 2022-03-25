#include "pch.h"
#include "Player.h"

#include "KeyManager.h"

#include "TimeManager.h"

#include "SceneManager.h"
#include "GameScene.h"

#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"

#include "Bullet.h"
#include "Missile.h"

#include "Collider.h"

Player::Player()
	: mSpeed(100.f), mJumpHeight(20.f), mHP(100)
{
	this->SetScale(playerScale);
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"PLAYER", L"\\texture\\player_right.bmp"));

	// Create Collider
	this->CreateCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());
}

Player::~Player()
{
	if(this->GetTexture() != nullptr)
		delete this->GetTexture();
}

void Player::Update()
{
	// ====================== Key Input Control
	// Player Move Position
	Vector2f updatePosition = this->GetPosition();

	// Left
	if (KEY_CHECK(KEY::KEY_LEFT, KEY_STATE::KEY_STATE_HOLD))
	{
		updatePosition.x -= mSpeed * (float)DELTA_TIME;
	}

	// Right
	if (KEY_CHECK(KEY::KEY_RIGHT, KEY_STATE::KEY_STATE_HOLD))
	{
		updatePosition.x += mSpeed * (float)DELTA_TIME;
	}

	// Jump
	if (KEY_CHECK(KEY::KEY_UP, KEY_STATE::KEY_STATE_DOWN))
	{
		updatePosition.y -= mJumpHeight;
	}
	this->SetPosition(updatePosition);

	// Player Attack
	if (KEY_CHECK(KEY::KEY_Z, KEY_STATE::KEY_STATE_DOWN))
	{
		CreateBullet();
	}
	if (KEY_CHECK(KEY::KEY_X, KEY_STATE::KEY_STATE_DOWN))
	{
		CreateMissile();
	}
}

void Player::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		this->GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
		);

	this->ComponentRender(_bitmapDC);
}

void Player::CreateBullet()
{
	Bullet* bullet = new Bullet;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	bullet->SetPosition(bulletPosition);
	bullet->SetScale(Vector2f(20.0f, 20.0f));
	bullet->SetSpeed(500.f);
	bullet->SetTheta(0);
	bullet->SetDirection(Vector2f(1.f, 0.f));

	GameScene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
	currentScene->AddGameObject(bullet, OBJECT_TYPE::OBJECT_TYPE_PROJECTILE);
}

void Player::CreateMissile()
{
	Missile* missile = new Missile;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	missile->SetPosition(bulletPosition);
	missile->SetScale(Vector2f(20.0f, 20.0f));
	missile->SetSpeed(300.f);
	missile->SetTheta(0);
	missile->SetDirection(Vector2f(1.f, 0.f));

	GameScene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
	currentScene->AddGameObject(missile, OBJECT_TYPE::OBJECT_TYPE_PROJECTILE);
}
