#include "pch.h"
#include "StartButton.h"

#include "ResourceManager.h"
#include "Texture.h"

StartButton::StartButton()
{
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"START_BUTTON", L"\\texture\\ui\\play_button.bmp"));

	this->SetUIName(L"Start Button");
	this->SetScale(Vector2f(200.f, 200.f));
}

StartButton::~StartButton()
{
}

void StartButton::Render(HDC _bitmapDC)
{
	int width = (int)this->GetTexture()->GetBitmapInfoWidth();
	int height = (int)this->GetTexture()->GetBitmapInfoHeight();

	Vector2f position = GetPosition();
	position = GameCamera::GetInstance()->GetRenderPosition(position);

	Vector2f scale = this->GetScale();
	Vector2f halfScale = scale / 2.0f;

	// 특정 색상 제외하고 복사
	TransparentBlt(_bitmapDC,
		(int)position.x - (int)halfScale.x,
		(int)position.y - (int)halfScale.y,
		(int)scale.x, (int)scale.y,
		this->GetTexture()->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255)
	);

	this->ComponentRender(_bitmapDC);
}

void StartButton::OnMouseClick()
{
	ChangeGameScene(SCENE_TYPE::SCENE_TYPE_STAGE_01);
}
