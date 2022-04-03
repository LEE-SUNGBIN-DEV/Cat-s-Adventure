#pragma once

class GameScene;

class RandomManager
{
private:
	GameScene*	mCurrentScene;
	GameObject*	mTarget;
	float		mAccumulatedTime;
	float		mUpdateDuration;

	RandomManager();
	~RandomManager();

public:
	// Singleton
	static RandomManager* GetInstance()
	{
		static RandomManager manager;
		return &manager;
	}

	void Init(GameScene* _currentScene, GameObject* _target, float _updateDuration);
	void Update();

	Vector2f	CreateRandomPosition();
	int			CreateRandomNumber(int _minRange, int _maxRange);
	void		CreateRandomTile();
	void		CreateRandomMonster();

};

