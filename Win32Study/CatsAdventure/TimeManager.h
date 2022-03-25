#pragma once
class TimeManager
{
	// 시간 동기화!
	// 프레임당 시간: Delta Time
private:
	LARGE_INTEGER mCurrentCount;
	LARGE_INTEGER mPrevCount;
	LARGE_INTEGER mFrequency;

	double mDeltaTime;
	double mAccumulate;
	UINT mCallCount;
	UINT mFPS;

	TimeManager();
	~TimeManager();

public:
	// 싱글톤
	static TimeManager* GetInstance()
	{
		static TimeManager manager;
		return &manager;
	}
	void Init();
	void Update();

	// get
	double GetDeltaTime() { return this->mDeltaTime; };
};

