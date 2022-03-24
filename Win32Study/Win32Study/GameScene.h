#pragma once

class GameObject;

class GameScene
{
private:
	// GameObject�� ���� �Ļ��Ǵ� ��� Ŭ������ ���� ������ �̿� ����
	// �׷캰�� ������ ����
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

