#include "pch.h"
#include "MonsterMouse.h"
#include "Player.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"

MonsterMouse::MonsterMouse()
	:mDamage(10)
{
	this->SetObjectName(L"Mouse");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	this->SetScale(monsterMouseBitmapScale);

	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"MOUSE", L"\\texture\\mouse_left.bmp"));

	// Create Collider
	this->CreateCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(monsterMouseColliderScale);
}
MonsterMouse::~MonsterMouse()
{

}

void MonsterMouse::Update()
{
	Vector2f currentPosition = GetPosition();

	currentPosition.x -= this->GetSpeed() * this->GetMoveDirection() * (float)DELTA_TIME;
	SetPosition(currentPosition);
}

void MonsterMouse::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// Ư�� ���� �����ϰ� ����
	TransparentBlt(_bitmapDC,
		int(position.x - width / 2),
		int(position.y - width / 2),
		width, height,
		GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	this->ComponentRender(_bitmapDC);
}

void MonsterMouse::OnCollision(Collider* _opponent)
{
}

void MonsterMouse::OnCollisionEnter(Collider* _opponent)
{
	if (_opponent->GetOwner()->GetObjectType == OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	{
		Player* player = (Player*)_opponent->GetOwner();
		player->SetHP(player->GetHP() - this->mDamage);
	}
}

void MonsterMouse::OnCollisionExit(Collider* _opponent)
{
}
