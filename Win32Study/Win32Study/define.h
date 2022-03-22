#pragma once

#define SINGLETON(type) static type* GetInstance()\
{\
	static type manager;\
	return &manager;\
}