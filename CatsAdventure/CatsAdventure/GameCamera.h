#pragma once
class GameObject;

class GameCamera
{
private:
	Vector2f	mPrevLookAtPosition;
	Vector2f	mCurrentLookAtPosition;
	Vector2f	mLookAtPosition;
	Vector2f	mDiffrence;
	GameObject*	mTargetObject;

	float		mCameraSpeedByKeyboard;

	float		mCameraSpeedByMouse;
	float		mCameraMoveTimeByMouse;
	float		mAccumulatedTime;

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
	Vector2f	GetRealPosition(Vector2f _renderPosition) { return _renderPosition + this->mDiffrence; }
	
	//get
	Vector2f GetCurrentLookAtPosition(){ return this->mCurrentLookAtPosition; }

	//set
	void SetLookAtPosition(Vector2f _lookAtPosition)
	{
		this->mLookAtPosition = _lookAtPosition;
		float length = (this->mLookAtPosition - this->mPrevLookAtPosition).Length();
		this->mCameraSpeedByMouse = length / this->mCameraMoveTimeByMouse;
		this->mAccumulatedTime = 0.f;
	}
	void SetTargetObject(GameObject* _gameObject) { this->mTargetObject = _gameObject; }
	void SetCameraSpeed(float _cameraSpeed) { this->mCameraSpeedByKeyboard = _cameraSpeed; }
};

