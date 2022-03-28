#pragma once

#define DELTA_TIME TimeManager::GetInstance()->GetDeltaTime()
#define KEY_CHECK(_keyInput, _keyState) KeyManager::GetInstance()->GetKeyState(_keyInput) == _keyState
#define PI 3.141592f

enum class OBJECT_TYPE
{
	OBJECT_TYPE_DEFALUT,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_MONSTER,
	OBJECT_TYPE_PLAYER_PROJECTILE,
	OBJECT_TYPE_MONSTER_PROJECTILE,
	OBJECT_TYPE_MAP,

	OBJECT_TYPE_SIZE = 32
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

enum class EVENT_TYPE
{
	EVENT_TYPE_CREATE_OBJECT,
	EVENT_TYPE_REMOVE_OBJECT,
	EVENT_TYPE_CHANGE_SCENE,

	EVENT_TYPE_SIZE
};