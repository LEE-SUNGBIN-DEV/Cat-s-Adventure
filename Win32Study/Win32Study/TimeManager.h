#pragma once
class TimeManager
{
// ÇÁ·¹ÀÓ´ç ½Ã°£: Delta Time
private:
	LARGE_INTEGER curCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;

	double deltaTime;
	double accumulate;
	UINT callCount;
	UINT FPS;

	TimeManager();
	~TimeManager();

public:
	// ½Ì±ÛÅæ
	static TimeManager* GetInstance()
	{
		static TimeManager manager;
		return &manager;
	}
	void Init();
	void Update();

	// get
	double GetDeltaTime() { return this->deltaTime; };
};

