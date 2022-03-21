#pragma once

// 싱글톤 패턴
// 객체의 개수를 1개로 제한
// 언제 어디서든 쉽게 접근 가능해야함

class CCore
{
public:
	static CCore* GetInstance()
	{


		return nullptr;
	}

private:
	CCore()
	{

	}
	~CCore()
	{

	}
};

