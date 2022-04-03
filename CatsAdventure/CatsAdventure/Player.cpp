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
	mSpeed(1000.f),
	mJumpHeight(0.f),
	mState(PLAYER_STATE_IDLE),
	mIsJump(false), mIsFall(false), mIsHurt(false)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PLAYER);
	this->SetScale(playerScale);
	this->SetDirectionNotNormalize(Vector2f((float)MOVE_DIRECTION_RIGHT, (float)JUMP_DIRECTION_DOWN));

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
	Vector2f moveDirection = this->GetDirection();

	// WALK - Left
	if (KEY_CHECK(KEY::KEY_LEFT, KEY_STATE::KEY_STATE_HOLD))
	{
		GameCamera::GetInstance()->SetCameraMode(true);

		this->mState = PLAYER_STATE_WALK;
		moveDirection.x = (float)MOVE_DIRECTION_LEFT;
		this->SetDirectionNotNormalize(moveDirection);
		updatePosition.x += this->GetDirection().x * mSpeed * (float)DELTA_TIME;
	}
	else if (KEY_CHECK(KEY::KEY_LEFT, KEY_STATE::KEY_STATE_UP))
	{
		this->mState = PLAYER_STATE_IDLE;
	}
	
	// WALK - Right
	if (KEY_CHECK(KEY::KEY_RIGHT, KEY_STATE::KEY_STATE_HOLD))
	{
		GameCamera::GetInstance()->SetCameraMode(true);

		this->mState = PLAYER_STATE_WALK;
		moveDirection.x = (float)MOVE_DIRECTION_RIGHT;
		this->SetDirectionNotNormalize(moveDirection);
		updatePosition.x += this->GetDirection().x * mSpeed * (float)DELTA_TIME;
	}
	else if (KEY_CHECK(KEY::KEY_RIGHT, KEY_STATE::KEY_STATE_UP))
	{
		this->mState = PLAYER_STATE_IDLE;
	}

	// JUMP
	if (KEY_CHECK(KEY::KEY_C, KEY_STATE::KEY_STATE_DOWN))
	{
		if (this->mIsJump == false && this->mIsFall == false)
		{
			GameCamera::GetInstance()->SetCameraMode(true);

			// 점프 상태로 변경
			this->mIsJump = true;
		}
	}
	UpdateJumpState(&updatePosition);

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

	// Animating
	this->UpdateAnimation();
}

void Player::UpdateAnimation()
{
	// Animating
	// Animating Priority
	// FALL > JUMP > HURT > WALK > IDLE
	if (mIsFall == true)
	{
		this->GetAnimator()->Play(L"FALL", true);
	}

	else if (mIsJump == true)
	{
		this->GetAnimator()->Play(L"JUMP", true);
	}

	else if (mIsHurt == true)
	{
		this->GetAnimator()->Play(L"HURT", true);
	}

	else if (mState == PLAYER_STATE_WALK)
	{
		this->GetAnimator()->Play(L"WALK", true);
	}

	else if (mState == PLAYER_STATE_IDLE)
	{
		this->GetAnimator()->Play(L"IDLE", true);
	}

	this->GetAnimator()->Update();
}

void Player::UpdateJumpState(Vector2f* _updatePosition)
{
	Vector2f moveDirection = this->GetDirection();

	// 점프 상태면
	if (this->mIsJump == true)
	{
		moveDirection.y = (float)JUMP_DIRECTION_UP;
		this->SetDirectionNotNormalize(moveDirection);
		// 점프 진행
		this->mJumpHeight += playerJumpSpeed * (float)DELTA_TIME;
		_updatePosition->y += this->GetDirection().y * playerJumpSpeed * (float)DELTA_TIME;

		if (this->GetGravity() != nullptr)
		{
			// Ground 상태 해제
			this->GetGravity()->SetIsGround(false);
		}

		// 최대 점프 거리에 도달하면
		if (this->mJumpHeight >= playerJumpPower)
		{
			// 낙하 상태로 변경, 점프 높이 초기화
			this->mIsJump = false;
			this->mIsFall = true;
			this->mJumpHeight = 0;

			moveDirection.y = (float)JUMP_DIRECTION_DOWN;
			this->SetDirectionNotNormalize(moveDirection);
		}
	}

	// 낙하 상태
	if (this->mIsFall == true)
	{
		if (this->GetGravity() != nullptr)
		{
			// 땅에 닿으면
			if (this->GetGravity()->IsGround() == true)
			{
				// 낙하 상태 해제
				this->mIsFall = false;
				this->mState = PLAYER_STATE_IDLE;

				moveDirection.y = (float)JUMP_DIRECTION_NONE;
				this->SetDirectionNotNormalize(moveDirection);
			}
		}
	}
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
		this->mIsHurt = true;

		break;
	}

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
		this->mIsHurt = true;

		break;
	}

	case OBJECT_TYPE::OBJECT_TYPE_TILE:
	{
		this->mIsFall = false;
		break;
	}
	}
}

void Player::OnCollisionExit(Collider* _opponent)
{
	switch (_opponent->GetOwner()->GetObjectType())
	{
	case OBJECT_TYPE::OBJECT_TYPE_MONSTER:
	{
		this->mIsHurt = false;

		break;
	}

	case OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE:
	{
		this->mIsHurt = false;

		break;
	}

	case OBJECT_TYPE::OBJECT_TYPE_TILE:
	{

		break;
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
