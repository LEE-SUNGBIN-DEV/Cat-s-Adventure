#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	map<wstring, Texture*>::iterator iter = mMapTexture.begin();
	for (; iter != mMapTexture.end(); ++iter)
	{
		delete iter->second;
	}
}

Texture* ResourceManager::LoadTexture(const wstring& _key, const wstring& _relativePath)
{
	Texture* texture = FindTexture(_key);
	if (texture != nullptr)
	{
		return texture;
	}

	wstring filePath = PathManager::GetInstance()->GetContentPath();
	filePath += _relativePath;

	texture = new Texture;
	texture->Load(filePath);
	texture->SetKey(_key);
	texture->SetRelativePath(_relativePath);

	mMapTexture.insert(make_pair(_key, texture));

	return texture;
}

Texture* ResourceManager::FindTexture(const wstring& _key)
{
	map<wstring, Texture*>::iterator iter = mMapTexture.find(_key);

	if (iter == mMapTexture.end())
	{
		return nullptr;
	}

	return iter->second;
}
