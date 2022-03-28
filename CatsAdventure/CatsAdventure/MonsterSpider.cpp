#include "pch.h"
#include "MonsterSpider.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Web.h"
#include "SceneManager.h"
#include "GameScene.h"

MonsterSpider::MonsterSpider()
	: mAttackDelay(0.f)
{
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	this->SetScale(Vector2f(30.f, 30.f));
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SPIDER", L"\\texture\\spider.bmp"));

	// Create Collider
	this->CreateCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());
}
MonsterSpider::~MonsterSpider()
{

}

void MonsterSpider::Update()
{
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	if (!gameObjectList.empty())
	{
		if (this->mAttackDelay == 0)
		{
			CreateWeb();
		}

		this->mAttackDelay += (float)DELTA_TIME;

		if (this->mAttackDelay >= SPIDER_ATTACK_DELAY)
		{
			this->mAttackDelay = 0;
		}
	}
}

void MonsterSpider::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();
	Vector2f position = GetPosition();

	// 특정 색상 제외하고 복사
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

void MonsterSpider::OnCollision(Collider* _opponent)
{
}

void MonsterSpider::OnCollisionEnter(Collider* _opponent)
{
}

void MonsterSpider::OnCollisionExit(Collider* _opponent)
{
}

void MonsterSpider::CreateWeb()
{
	Web* web = new Web;
	Vector2f webPosition = this->GetPosition();
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	webPosition.y += this->GetScale().y;

	web->SetPosition(webPosition);
	web->SetScale(Vector2f(20.0f, 20.0f));
	web->SetTheta(0);
	web->SetDirection(this->GetPosition() - gameObjectList[0]->GetPosition());

	CreateGameObject(web, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
}
