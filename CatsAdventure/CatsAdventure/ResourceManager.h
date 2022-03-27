#pragma once

class Texture;

class ResourceManager
{
private:
	map<wstring, Texture*>	mMapTexture;

	ResourceManager();
	~ResourceManager();

public:
	// Singleton
	static ResourceManager* GetInstance()
	{
		static ResourceManager manager;

		return &manager;
	}

	Texture* LoadTexture(const wstring& _key, const wstring& _relativePath);
	Texture* FindTexture(const wstring& _key);
};

