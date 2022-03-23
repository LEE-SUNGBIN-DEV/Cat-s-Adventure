#pragma once
class TimeManager
{
	// 시간 동기화!
	// 프레임당 시간: Delta Time
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
	// 싱글톤
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

