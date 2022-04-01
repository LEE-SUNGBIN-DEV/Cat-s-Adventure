#include "pch.h"
#include "MonsterSpider.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Web.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameTimer.h"

MonsterSpider::MonsterSpider()
{
	this->SetObjectName(L"Spider");
	this->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	this->SetScale(monsterSpiderScale);

	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"SPIDER", L"\\texture\\spider.bmp"));

	// Create Collider
	this->AddCollider();
	this->GetCollider()->SetPosition(this->GetPosition());
	this->GetCollider()->SetScale(this->GetScale());

	// Create TImer
	this->AddTimer();
	this->GetTimer()->SetTargetTime(spiderAttackDelay);
}
MonsterSpider::~MonsterSpider()
{

}

void MonsterSpider::Update()
{
	const vector<GameObject*>& gameObjectList = SceneManager::GetInstance()->GetCurrentScene()->GetGameObjectList(OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	if (!gameObjectList.empty())
	{
		if (this->GetTimer()->Timer())
		{
			CreateWeb();
		}
	}
}

void MonsterSpider::Render(HDC _bitmapDC)
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
		(int)monsterSpiderScale.x, (int)monsterSpiderScale.y,
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
