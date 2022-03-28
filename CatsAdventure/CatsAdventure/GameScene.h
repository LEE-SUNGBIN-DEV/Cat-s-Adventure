#pragma once

class GameObject;
class Texture;

class GameScene
{
private:
	wstring				mSceneName;
	vector<GameObject*>	mGameObjectList[(UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE];
	
	Texture* mTexture;

public:
	GameScene();
	virtual ~GameScene();

	virtual void	Enter() = 0;
	virtual void	Exit() = 0;
	virtual void	Render(HDC _bitmapDC);
	virtual void	Update();

	void			LateUpdate();
	void			AddGameObject(GameObject* _gameObject, OBJECT_TYPE _objectType) { this->mGameObjectList[(UINT)_objectType].push_back(_gameObject); }
	void			RemoveObject(OBJECT_TYPE _objectType);
	void			RemoveAll();
	// get
	const wstring&				GetName() { return this->mSceneName; }
	const vector<GameObject*>&	GetGameObjectList(OBJECT_TYPE _objectType) { return this->mGameObjectList[(UINT)_objectType]; }
	Texture*					GetTexture() { return this->mTexture; }
	
	// set
	void SetName(const wstring& _sceneName) { this->mSceneName = _sceneName; }
	void SetTexture(Texture* _texture) { this->mTexture = _texture; }
};

