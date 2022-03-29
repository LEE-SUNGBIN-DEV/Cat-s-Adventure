#pragma once

class Animator;
class Texture;

class Animation
{
private:
	wstring			mName;
	Animator*		mAnimator;

	void SetName(const wstring& _name) { this->mName = _name; }
public:
	Animation();
	~Animation();

	void Update();
	void Render();

	void Create(Texture* _texture, UINT _frameCount);

	// get
	const wstring& GetName() { return this->mName; }

	// set
	void SetAnimator(Animator* _animator) { this->mAnimator = _animator; }

	friend class Animator;
};

