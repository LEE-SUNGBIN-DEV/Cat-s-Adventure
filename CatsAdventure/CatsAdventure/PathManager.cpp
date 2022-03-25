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
	// ���� ���丮
	GetCurrentDirectory(255, mContentPath);

	int CurrentDirectoryLength = wcslen(mContentPath);

	// ���� ������ �̵�
	for (int i = CurrentDirectoryLength - 1; i >= 0; --i)
	{
		if (mContentPath[i] == '\\')
		{
			mContentPath[i] = '\0';
			break;
		}
	}

	// Resource ��� �ٿ��ֱ�
	wcscat_s(mContentPath, 255, L"\\Binary\\Resource");

}
