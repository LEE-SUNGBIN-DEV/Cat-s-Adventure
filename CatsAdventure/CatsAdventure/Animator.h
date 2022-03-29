#pragma once

class Animation;
class GameObject;
class Texture;

class Animator
{
private:
	map<wstring, Animation*>	mAnimationMap;
	Animation*					mCurrentAnimation;
	GameObject*					mOwner;	// 이 컴포넌트의 소유자
	bool						mRepeat;

public:
	Animator();
	Animator(const Animator& _origin);
	~Animator();

	Animation*	FindAnimation(const wstring& _name);
	void		CreateAnimation(const wstring& _name, Texture* _texture, Vector2f _leftTop, Vector2f _sliceSize, Vector2f _interval, float _duration, UINT _frameCount);
	
	void Play(const wstring& _animationName, bool _repeat);
	void Update();
	void Render(HDC _bitmapDC);

	// get
	GameObject* GetOwner() { return this->mOwner; }

	// set
	void SetOwner(GameObject* _owner) { this->mOwner = _owner; }
};

