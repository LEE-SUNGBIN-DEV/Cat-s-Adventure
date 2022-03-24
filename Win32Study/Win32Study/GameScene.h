#pragma once

class GameObject;

class GameScene
{
private:
	// GameObject�� ���� �Ļ��Ǵ� ��� Ŭ������ ���� ������ �̿� ����
	// �׷캰�� ������ ����
	vector<GameObject*> mGameObjectList[(UINT)OBJECT_TYPE::OBJECT_TYPE_SIZE];
	wstring mSceneName;

public:
	GameScene();
	virtual ~GameScene();

	virtual void EnterScene() = 0;
	virtual void ExitScene() = 0;

	void Update();
	void Render(HDC _bitmapDC);

	void AddGameObject(GameObject* _gameObject, OBJECT_TYPE _objectType)
	{
		this->mGameObjectList[(UINT)_objectType].push_back(_gameObject);
	}

	// get
	const wstring& GetName() { return this->mSceneName; }

	// set
	void SetName(const wstring& _sceneName) { this->mSceneName = _sceneName; }
};

