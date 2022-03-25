#include "pch.h"
#include "Texture.h"
#include "GameCore.h"

Texture::Texture()
	:mDC(nullptr), mBitmap(nullptr), mBitmapInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(this->mDC);
	DeleteObject(this->mBitmap);
}

void Texture::Load(const wstring& _filePath)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	this->mBitmap = (HBITMAP)LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(mBitmap);

	// ��Ʈ�ʰ� ������ DC
	this->mDC = CreateCompatibleDC(GameCore::GetInstance()->GetMainDC());

	// ��Ʈ�ʰ� ����
	HBITMAP prevBitmap = (HBITMAP)SelectObject(this->mDC, this->mBitmap);
	DeleteObject(prevBitmap);

	// ��Ʈ�� ���� ����
	GetObject(mBitmap, sizeof(BITMAP), &mBitmapInfo);
}
