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
	: mHP(100), mSpeed(200.f),
	mJumpHeight(0.f), mIsJump(PLAYER_JUMP_NONE)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER);
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

	// 점프 테스트 버전
	JumpChecking(&updatePosition);

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
	if (KEY_CHECK(KEY::KEY_C, KEY_STATE::KEY_STATE_DOWN))
	{
		if (mIsJump == PLAYER_JUMP_NONE)
		{
			mIsJump = PLAYER_JUMP_PROGRESS;
		}
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

void Player::OnCollision(Collider* _opponent)
{
}

void Player::OnCollisionEnter(Collider* _opponent)
{
}

void Player::OnCollisionExit(Collider* _opponent)
{
}

void Player::JumpChecking(Vector2f* _updatePosition)
{
	if (this->mIsJump == PLAYER_JUMP_PROGRESS)
	{
		this->mJumpHeight += PLAYER_JUMP_SPEED * (float)DELTA_TIME;
		_updatePosition->y -= PLAYER_JUMP_SPEED * (float)DELTA_TIME;

		if (this->mJumpHeight >= PLAYER_JUMP_POWER)
		{
			this->mIsJump = 2;
		}
	}

	else if (this->mIsJump == PLAYER_JUMP_FALL)
	{
		this->mJumpHeight -= PLAYER_JUMP_SPEED * (float)DELTA_TIME;
		_updatePosition->y += PLAYER_JUMP_SPEED * (float)DELTA_TIME;

		if (this->mJumpHeight <= 0)
		{
			this->mJumpHeight = 0;
			this->mIsJump = PLAYER_JUMP_NONE;
		}
	}
}

void Player::CreateBullet()
{
	Bullet* bullet = new Bullet;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	bullet->SetPosition(bulletPosition);
	bullet->SetScale(Vector2f(20.0f, 20.0f));
	bullet->SetTheta(0);
	bullet->SetDirection(Vector2f(1.f, 0.f));

	CreateGameObject(bullet, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
}

void Player::CreateMissile()
{
	Missile* missile = new Missile;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	missile->SetPosition(bulletPosition);
	missile->SetScale(Vector2f(20.0f, 20.0f));
	missile->SetTheta(0);
	missile->SetDirection(Vector2f(1.f, 0.f));

	CreateGameObject(missile, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
}
