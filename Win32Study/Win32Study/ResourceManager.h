#pragma once

class Texture;

class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();

	map<wstring, Texture*> mMapTexture;


public:
	static ResourceManager* GetInstance()
	{
		static ResourceManager manager;

		return &manager;
	}

	Texture* LoadTexture(const wstring& _key, const wstring& _relativePath);
	Texture* FindTexture(const wstring& _key);
};

