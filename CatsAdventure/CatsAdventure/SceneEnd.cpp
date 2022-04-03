#include "pch.h"
#include "SceneEnd.h"

#include "GameCore.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "GameCamera.h"

#include "GameObject.h"

#include "Texture.h"

SceneEnd::SceneEnd()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND_WIN", L"\\texture\\background\\background_win.bmp"));
}
SceneEnd::~SceneEnd()
{
}

void SceneEnd::Enter()
{
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();

	// Set Camera
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.0f, true);
}

void SceneEnd::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneEnd::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_MOUSE_LEFT_BUTTON, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_START);
	}
}

void SceneEnd::Render(HDC _bitmapDC)
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