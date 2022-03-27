#pragma once
#include "GameResource.h"
class Texture :
	public GameResource
{
private:
	HDC		mDC;
	HBITMAP	mBitmap;
	BITMAP	mBitmapInfo;

public:
	Texture();
	~Texture();

	void Load(const wstring& _filePath);

	// get
	UINT GetBitmapInfoWidth() { return this->mBitmapInfo.bmWidth; }
	UINT GetBitmapInfoHeight() { return this->mBitmapInfo.bmHeight; }
	HDC GetDC() { return this->mDC; }
};


