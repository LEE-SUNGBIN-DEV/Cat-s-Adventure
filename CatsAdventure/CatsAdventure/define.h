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
#define KEY_CHECK(_keyInput, _keyState) KeyManager::GetInstance()->GetKeyState(_keyInput) == _keyState
#define PI 3.141592f

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

enum class BRUSH_TYPE
{
	BRUSH_TYPE_HOLLOW,

	BRUSH_TYPE_SIZE
};

enum class PEN_TYPE
{
	PEN_TYPE_RED,
	PEN_TYPE_GREEN,
	PEN_TYPE_BLUE,

	PEN_TYPE_SIZE
};