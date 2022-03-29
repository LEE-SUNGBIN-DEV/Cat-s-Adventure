#pragma once
class GameResource
{
private:
	wstring mKey;
	wstring mRelativePath;

public:
	GameResource();
	virtual ~GameResource();

	// get
	const wstring& GetKey() { return this->mKey; }
	const wstring& GetRelativePath() { return this->mRelativePath; }

	// set
	void SetKey(const wstring& _key) { this->mKey = _key; }
	void SetRelativePath(const wstring& _relativePath) { this->mRelativePath = _relativePath; }
};