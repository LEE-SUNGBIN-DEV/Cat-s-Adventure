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
	// 파일로부터 로드한 데이터를 비트맵으로 생성
	this->mBitmap = (HBITMAP)LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(mBitmap);

	// 비트맵과 연결할 DC
	this->mDC = CreateCompatibleDC(GameCore::GetInstance()->GetMainDC());

	// 비트맵과 연결
	HBITMAP prevBitmap = (HBITMAP)SelectObject(this->mDC, this->mBitmap);
	DeleteObject(prevBitmap);

	// 비트맵 정보 저장
	GetObject(mBitmap, sizeof(BITMAP), &mBitmapInfo);
}
