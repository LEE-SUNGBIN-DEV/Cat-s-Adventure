#pragma once
class TimeManager
{
	// �ð� ����ȭ!
	// �����Ӵ� �ð�: Delta Time
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
	// �̱���
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

