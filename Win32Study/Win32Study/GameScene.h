#pragma once

class GameObject;

class GameScene
{
private:
	// GameObject로 부터 파생되는 모든 클래스에 대해 다형성 이용 가능
	// 그룹별로 나눠서 관리
	vector<GameObject*> gameObjectList[(UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE];
	wstring sceneName;

public:
	GameScene();
	virtual ~GameScene();

	virtual void EnterScene() = 0;
	virtual void ExitScene() = 0;

	void Update();
	void Render(HDC _bitmapDC);

	void AddGameObject(GameObject* _gameObject, OBJECT_TYPE _objectType)
	{
		this->gameObjectList[(UINT)_objectType].push_back(_gameObject);
	}

	// get
	const wstring& GetName() { return this->sceneName; }

	// set
	void SetName(const wstring& _sceneName) { this->sceneName = _sceneName; }
};

