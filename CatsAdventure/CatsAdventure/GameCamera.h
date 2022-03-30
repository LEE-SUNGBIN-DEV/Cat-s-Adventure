#pragma once
class GameObject;

class GameCamera
{
private:
	Vector2f	mLookAtPosition;
	Vector2f	mDiffrence;
	GameObject*	mTargetObject;

	float		mCameraSpeed;

	GameCamera();
	~GameCamera();
public:
	static GameCamera* GetInstance()
	{
		static GameCamera manager;
		return &manager;
	}

	void		Update();
	void		CalculateDifference();
	Vector2f	GetRenderPosition(Vector2f _objectPosition) { return _objectPosition - this->mDiffrence; }

	//get

	//set
	void SetLookAtPosition(Vector2f _lookAtPosition) { this->mLookAtPosition = _lookAtPosition; }
	void SetTargetObject(GameObject* _gameObject) { this->mTargetObject = _gameObject; }
	void SetCameraSpeed(float _cameraSpeed) { this->mCameraSpeed = _cameraSpeed; }
};

