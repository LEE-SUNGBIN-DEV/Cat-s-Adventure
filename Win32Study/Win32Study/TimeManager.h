#pragma once
class TimeManager
{
// �����Ӵ� �ð�: Delta Time
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
	// �̱���
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

