#include "pch.h"
#include "MonsterFrog.h"

#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "Texture.h"
#include "Collider.h"
#include "GameTimer.h"

#include "Acid.h"

MonsterFrog::MonsterFrog()
{
	this->SetObjectName(L"Frog");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	this->SetScale(monsterFrogScale);

	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"FROG", L"\\texture\\gold_frog.bmp"));

	// Create Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());

	// Create TImer
	this->AddTimer();
	this->GetTimer()->SetTargetTime(frogAttackDelay);
}

MonsterFrog::~MonsterFrog()
{
}

void MonsterFrog::Update()
{
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	if (!gameObjectList.empty())
	{
		if (this->GetTimer()->Timer())
		{
			CreateAcid();
		}
	}
}

void MonsterFrog::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();
	position = GameCamera::GetInstance()->GetRenderPosition(position);
	Vector2f halfScale = this->GetScale() / 2.0f;

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		(int)position.x - (int)halfScale.x,
		(int)position.y - (int)halfScale.y,
		(int)monsterFrogScale.x, (int)monsterFrogScale.y,
		GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	this->ComponentRender(_bitmapDC);
}

void MonsterFrog::OnCollision(Collider* _opponent)
{
}

void MonsterFrog::OnCollisionEnter(Collider* _opponent)
{
}

void MonsterFrog::OnCollisionExit(Collider* _opponent)
{
}

void MonsterFrog::CreateAcid()
{
	Acid* acid = new Acid;
	Vector2f acidPosition = this->GetPosition();
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	acidPosition.y += this->GetScale().y;

	acid->SetPosition(acidPosition);
	acid->SetTheta(0);
	acid->SetDirection(this->GetPosition() - gameObjectList[0]->GetPosition());

	CreateGameObject(acid, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
}
