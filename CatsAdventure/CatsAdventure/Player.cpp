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
#include "Animator.h"
#include "Animation.h"

Player::Player()
	: mHP(100),
	mSpeed(300.f),
	mJumpHeight(0.f),
	mIsJump(PLAYER_JUMP_NONE)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	this->SetScale(playerBitmapScale);

	//======================================== Init Component
	// ==================== Animator
	this->AddAnimator();
	// idel
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_IDLE", L"\\texture\\cat\\cat_idle.bmp"));
	this->GetAnimator()->CreateAnimation(L"IDLE", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);
	// walk
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_WALK", L"\\texture\\cat\\cat_walk.bmp"));
	this->GetAnimator()->CreateAnimation(L"WALK", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);
	// jump
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_JUMP", L"\\texture\\cat\\cat_jump.bmp"));
	this->GetAnimator()->CreateAnimation(L"JUMP", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 8);
	// hurt
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_HURT", L"\\texture\\cat\\cat_hurt.bmp"));
	this->GetAnimator()->CreateAnimation(L"HURT", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);
	
	this->GetAnimator()->Play(L"IDLE", true);

	// ==================== Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(playerColliderScale);

	// Camera
	GameCamera::GetInstance()->SetTargetObject(this);
}

Player::~Player()
{
	//if(this->GetTexture() != nullptr)
	//	delete this->GetTexture();
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
		GameCamera::GetInstance()->SetCameraMode(true);
		this->GetAnimator()->Play(L"WALK", true);
		updatePosition.x -= mSpeed * (float)DELTA_TIME;
	}

	// Right
	if (KEY_CHECK(KEY::KEY_RIGHT, KEY_STATE::KEY_STATE_HOLD))
	{
		GameCamera::GetInstance()->SetCameraMode(true);
		this->GetAnimator()->Play(L"WALK", true);
		updatePosition.x += mSpeed * (float)DELTA_TIME;
	}

	// Jump
	if (KEY_CHECK(KEY::KEY_C, KEY_STATE::KEY_STATE_DOWN))
	{
		GameCamera::GetInstance()->SetCameraMode(true);
		if (mIsJump == PLAYER_JUMP_NONE)
		{
			this->GetAnimator()->Play(L"JUMP", true);
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

	this->GetAnimator()->Update();
}

void Player::Render(HDC _bitmapDC)
{
	this->ComponentRender(_bitmapDC);
}

void Player::OnCollision(Collider* _opponent)
{
}

void Player::OnCollisionEnter(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		this->GetAnimator()->Play(L"HURT", true);
	}
	break;

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
		this->GetAnimator()->Play(L"HURT", true);
	}
	break;
	}
}

void Player::OnCollisionExit(Collider* _opponent)
{
}

void Player::JumpChecking(Vector2f* _updatePosition)
{
	if (this->mIsJump == PLAYER_JUMP_PROGRESS)
	{
		this->mJumpHeight += playerJumpSpeed * (float)DELTA_TIME;
		_updatePosition->y -= playerJumpSpeed * (float)DELTA_TIME;

		if (this->mJumpHeight >= playerJumpPower)
		{
			this->mIsJump = PLAYER_JUMP_FALL;
		}
	}

	else if (this->mIsJump == PLAYER_JUMP_FALL)
	{
		this->mJumpHeight -= playerJumpSpeed * (float)DELTA_TIME;
		_updatePosition->y += playerJumpSpeed * (float)DELTA_TIME;

		if (this->mJumpHeight <= 0)
		{
			this->mJumpHeight = 0;
			this->mIsJump = PLAYER_JUMP_NONE;
			this->GetAnimator()->Play(L"IDLE", true);
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
