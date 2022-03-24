#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Bullet.h"

Player::Player()
	: mSpeed(100.f), mJumpHeight(20.f)
{
}

Player::~Player()
{
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
}

void Player::Render(HDC _bitmapDC)
{
	Rectangle(_bitmapDC,
		this->GetPosition().x - this->GetScale().x,
		this->GetPosition().y - this->GetScale().y,
		this->GetPosition().x + this->GetScale().x,
		this->GetPosition().y + this->GetScale().y);
}

void Player::CreateBullet()
{
	Bullet* bullet = new Bullet;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	bullet->SetPosition(bulletPosition);
	bullet->SetScale(Vector2f(20.0f, 20.0f));
	bullet->SetSpeed(400.f);
	bullet->SetTheta(0);

	GameScene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
	currentScene->AddGameObject(bullet, OBJECT_TYPE::OBJECT_TYPE_PROJECTILE);
}
