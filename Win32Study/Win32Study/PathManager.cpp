#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
	:mContentPath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// 현재 디렉토리
	GetCurrentDirectory(255, mContentPath);

	int CurrentDirectoryLength = wcslen(mContentPath);

	// 상위 폴더로 이동
	for (int i = CurrentDirectoryLength - 1; i >= 0; --i)
	{
		if (mContentPath[i] == '\\')
		{
			mContentPath[i] = '\0';
			break;
		}
	}

	// Resource 경로 붙여넣기
	wcscat_s(mContentPath, 255, L"\\Binary\\Resource");

}
