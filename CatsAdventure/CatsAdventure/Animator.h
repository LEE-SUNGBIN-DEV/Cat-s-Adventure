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

public:
	Animator();
	Animator(const Animator& _origin);
	~Animator();

	Animation*	FindAnimation(const wstring& _name);
	void		CreateAnimation(const wstring& _name, Texture* _texture, UINT _frameCount);
	
	void Play();
	void Update();
	void Render();

	// get

	// set
	void SetOwner(GameObject* _owner) { this->mOwner = _owner; }
};

