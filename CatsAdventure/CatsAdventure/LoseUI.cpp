#include "pch.h"
#include "LoseUI.h"

#include "GameCore.h"
#include "ResourceManager.h"
#include "Texture.h"

LoseUI::LoseUI()
{
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"LOSE", L"\\texture\\ui\\lose.bmp"));

	this->SetUIName(L"Lose UI");
	this->SetScale(Vector2f((float)this->GetTexture()->GetBitmapInfoWidth(), (float)this->GetTexture()->GetBitmapInfoHeight()));
}

LoseUI::~LoseUI()
{
}

void LoseUI::Render(HDC _bitmapDC)
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

void LoseUI::OnMouseClick()
{
	ChangeGameScene(SCENE_TYPE::SCENE_TYPE_START);
}