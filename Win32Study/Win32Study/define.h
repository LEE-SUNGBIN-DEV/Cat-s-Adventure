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

enum class OBJECT_TYPE
{
	OBJECT_TYPE_DEFALUT,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_MONSTER,
	OBJECT_TYPE_PROJECTILE,
	OBJECT_TYPE_MAP,

	OBJECT_TYPE_SIZE
};

enum class SCENE_TYPE
{
	SCENE_TYPE_TOOL,
	SCENE_TYPE_START,
	SCENE_TYPE_STAGE_01,
	SCENE_TYPE_STAGE_02,

	SCENE_TYPE_SIZE
};