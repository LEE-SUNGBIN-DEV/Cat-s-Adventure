#pragma once

class Animator;
class Texture;

struct AnimationFrame
{
	Vector2f	mLeftTop;
	Vector2f	mSliceSize;
	Vector2f	mOffset;
	float		mDuration;
};

class Animation
{
private:
	wstring					mName;
	Animator*				mAnimator;
	Texture*				mTexture;
	vector<AnimationFrame>	mFrameList;
	int						mCurrentFrame;
	float					mDurationTime;

	bool					mFinish;

	void SetName(const wstring& _name) { this->mName = _name; }
public:
	Animation();
	~Animation();

	void Update();
	void Render(HDC _bitmapDC);

	void Create(Texture* _texture, Vector2f _leftTop, Vector2f _sliceSize, Vector2f _interval, float _duration, UINT _frameCount);

	// get
	const wstring&	GetName() { return this->mName; }
	Animator*		GetAnimator() { return this->mAnimator; }
	AnimationFrame& GetFrame(int _index) { return this->mFrameList[_index]; }
	bool			IsFinish() { return this->mFinish; }

	// set
	void SetAnimator(Animator* _animator) { this->mAnimator = _animator; }
	void SetFrame(int _frame)
	{
		this->mFinish = false;
		this->mCurrentFrame = _frame;
		this->mDurationTime = 0.f;
	}
	friend class Animator;
};

