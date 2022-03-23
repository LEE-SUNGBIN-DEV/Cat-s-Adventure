#pragma once

#define SINGLETON(type) \
public static type* GetInstance()\
{\
	static type manager;\
	return &manager;\
}\
private:\
type();\
~type();

#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()