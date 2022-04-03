#include "pch.h"
#include "SceneStart.h"

#include "GameCore.h"
#include "GameObject.h"

#include "PathManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameCamera.h"

#include "TitleUI.h"
#include "StartButton.h"
#include "ExitButton.h"

SceneStart::SceneStart()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND_MAIN", L"\\texture\\background\\background_main.bmp"));
}
SceneStart::~SceneStart()
{

}

void SceneStart::Enter()
{
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	Vector2f offsetPosition = {};
	GameCamera::GetInstance()->SetLookAtPosition(Vector2f(mainResolution.x, mainResolution.y)/2.0f, false);

	// Title UI
	TitleUI* titleUI = new TitleUI;
	offsetPosition.x = mainResolution.x / 2.0f;
	offsetPosition.y = titleUI->GetScale().y / 2.0f;
	titleUI->SetPosition(offsetPosition);
	AddGameObject(titleUI, OBJECT_TYPE::OBJECT_TYPE_UI);

	// Start Button
	StartButton* startButton = new StartButton;
	offsetPosition.x = startButton->GetScale().x /2.f;
	offsetPosition.y = mainResolution.y - startButton->GetScale().y / 2.f;
	startButton->SetPosition(offsetPosition);
	AddGameObject(startButton, OBJECT_TYPE::OBJECT_TYPE_UI);

	// Exit Button
	ExitButton* exitButton = new ExitButton;
	offsetPosition.x = mainResolution.x - exitButton->GetScale().x /2.f;
	offsetPosition.y = exitButton->GetScale().y / 2.f;
	exitButton->SetPosition(offsetPosition);
	AddGameObject(exitButton, OBJECT_TYPE::OBJECT_TYPE_UI);
}

void SceneStart::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneStart::Update()
{
	GameScene::Update();
}

void SceneStart::Render(HDC _bitmapDC)
{
	Texture* texture = GetTexture();

	int width = texture->GetBitmapInfoWidth();
	int height = texture->GetBitmapInfoHeight();

	// 복사
	BitBlt(_bitmapDC,
		0, 0,
		width, height,
		texture->GetDC(),
		0, 0,
		SRCCOPY);

	// 오브젝트
	GameScene::Render(_bitmapDC);
}