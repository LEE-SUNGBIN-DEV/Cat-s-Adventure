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

	// true: 타겟을 추적, false: 마우스 입력
	bool		mTargetMode;
	Vector2f	mTargetOffset;

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
	void SetLookAtPosition(Vector2f _lookAtPosition, bool _targetMode);
	void SetTargetObject(GameObject* _gameObject) { this->mTargetObject = _gameObject; }
	void SetCameraMode(bool _mode) { this->mTargetMode = _mode; }
	void SetTargetOffset(Vector2f _offset) { this->mTargetOffset = _offset; }
};

