#pragma once
class GameScene;

class SceneManager
{
private:
	GameScene*	mGameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_SIZE];
	GameScene*	mCurrentScene;

	SceneManager();
	~SceneManager();
	void ChangeScene(SCENE_TYPE _sceneType);

public:
	// Singleton
	static SceneManager* GetInstance()
	{
		static SceneManager manager;

		return &manager;
	}

	void Init();
	void Update();
	void Render(HDC _bitmapDC);

	// get
	GameScene* GetCurrentScene() { return this->mCurrentScene; }

	// set
	void SetCurrentScene(GameScene* _currentScene) { this->mCurrentScene = _currentScene; }

	friend class EventManager;
};
