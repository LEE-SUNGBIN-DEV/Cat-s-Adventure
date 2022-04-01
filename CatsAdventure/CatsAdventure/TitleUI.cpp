#include "pch.h"
#include "TitleUI.h"

#include "ResourceManager.h"
#include "Texture.h"

TitleUI::TitleUI()
{
	// Load Texture
	SetTexture(ResourceManager::GetInstance()->LoadTexture(L"TITLE_UI", L"\\texture\\ui\\title.bmp"));

	this->SetUIName(L"Title UI");
	this->SetScale(Vector2f((float)this->GetTexture()->GetBitmapInfoWidth(), (float)this->GetTexture()->GetBitmapInfoHeight()));

}

TitleUI::~TitleUI()
{
}

void TitleUI::Render(HDC _bitmapDC)
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

void TitleUI::OnMouseClick()
{
}
