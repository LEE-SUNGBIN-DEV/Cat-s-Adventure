#pragma once
class GameScene;

class SceneManager
{
private:
	GameScene* gameSceneList[(UINT)SCENE_TYPE::SCENE_TYPE_SIZE];
	GameScene* curScene;

	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance()
	{
		static SceneManager manager;

		return &manager;
	}

	void Init();
	void Update();
	void Render(HDC _bitmapDC);

	// get
	// set

};

