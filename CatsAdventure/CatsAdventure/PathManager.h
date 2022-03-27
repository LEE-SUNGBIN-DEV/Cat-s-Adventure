#pragma once
class PathManager
{
private:
	wchar_t	mContentPath[255];

	PathManager();
	~PathManager();

public:
	// Singleton
	static PathManager* GetInstance()
	{
		static PathManager manager;

		return &manager;
	}

	void Init();
	const wchar_t* GetContentPath() { return this->mContentPath; }
};

