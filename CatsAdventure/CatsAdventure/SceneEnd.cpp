#include "pch.h"
#include "SceneEnd.h"

#include "GameCore.h"
#include "GameCamera.h"

SceneEnd::SceneEnd()
{
}

SceneEnd::~SceneEnd()
{
}

void SceneEnd::Render(HDC _bitmapDC)
{
}

void SceneEnd::Enter()
{
	// Set Camera
	Vector2f mainResolution = GameCore::GetInstance()->GetMainResolution();
	GameCamera::GetInstance()->SetLookAtPosition(mainResolution / 2.f, false);
}

void SceneEnd::Exit()
{
}

void SceneEnd::Update()
{
}
