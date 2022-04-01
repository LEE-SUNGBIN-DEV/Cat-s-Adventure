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
#include "Gravity.h"

Player::Player()
	: mHP(150),
	mSpeed(300.f),
	mJumpHeight(0.f),
	mIsJump(PLAYER_JUMP_NONE)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	this->SetScale(playerScale);

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
	// fall
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_FALL", L"\\texture\\cat\\cat_fall.bmp"));
	this->GetAnimator()->CreateAnimation(L"FALL", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);
	// hurt
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_HURT", L"\\texture\\cat\\cat_hurt.bmp"));
	this->GetAnimator()->CreateAnimation(L"HURT", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);
	// dead
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"CAT_DEAD", L"\\texture\\cat\\cat_dead.bmp"));
	this->GetAnimator()->CreateAnimation(L"DEAD", this->GetTexture(), Vector2f(0.f, 0.f), Vector2f(562.f, 494.f), Vector2f(562.f, 0.f), 0.1f, 10);

	this->GetAnimator()->Play(L"IDLE", true);

	// ==================== Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());
	this->GetCollider()->SetOffset(Vector2f(0.f, 0.f));
	this->GetCollider()->SetOffset(Vector2f(0.f, this->GetScale().y / 2.f));

	// =================== Gravity
	this->AddGravity();

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

	if(this->mIsJump == PLAYER_JUMP_NONE)
		this->GetAnimator()->Play(L"IDLE", true);

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
	JumpChecking(&updatePosition);

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

	case OBJECT_TYPE::OBJECT_TYPE_TILE:
	{

	}

	break;
	}
}

void Player::OnCollisionExit(Collider* _opponent)
{
}

void Player::JumpChecking(Vector2f* _updatePosition)
{
	// 점프 상태면
	if (this->mIsJump == PLAYER_JUMP_PROGRESS)
	{
		if (this->GetGravity() != nullptr)
		{
			// Ground 상태 해제
			this->GetGravity()->SetIsGround(false);
		}

		// 점프 진행
		this->mJumpHeight += playerJumpSpeed * (float)DELTA_TIME;
		_updatePosition->y -= playerJumpSpeed * (float)DELTA_TIME;

		// 최대 점프 거리에 도달하면
		if (this->mJumpHeight >= playerJumpPower)
		{
			// 낙하 상태로 변경, 점프 높이 초기화
			this->mIsJump = PLAYER_JUMP_FALL;
			this->mJumpHeight = 0;
		}
	}

	// 낙하 상태
	else if (this->mIsJump == PLAYER_JUMP_FALL)
	{
		this->GetAnimator()->Play(L"FALL", true);
		if (this->GetGravity() != nullptr)
		{
			// 땅에 닿으면
			if (this->GetGravity()->IsGround() == true)
			{
				// 낙하 상태 해제
				this->mIsJump = PLAYER_JUMP_NONE;
			}
		}
	}
}

void Player::CreateBullet()
{
	Bullet* bullet = new Bullet;
	Vector2f bulletPosition = this->GetPosition();

	bulletPosition.x += this->GetScale().x;

	bullet->SetPosition(bulletPosition);
	bullet->SetTheta(0);
	bullet->SetDirection(Vector2f(1.f, 0.f));

	CreateGameObject(bullet, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
}

void Player::CreateMissile()
{
	Missile* missile = new Missile;
	Vector2f missilePosition = this->GetPosition();

	missilePosition.y -= this->GetScale().y;

	missile->SetPosition(missilePosition);
	missile->SetTheta(0);
	missile->SetDirection(Vector2f(1.f, 0.f));

	CreateGameObject(missile, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
}
