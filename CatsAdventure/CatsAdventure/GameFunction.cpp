#include "pch.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "EventManager.h"

void CreateGameObject(GameObject* _gameObject, OBJECT_TYPE _objectType)
{
	EventMessage eventMessage = {};
	
	eventMessage.mEventType = EVENT_TYPE::EVENT_TYPE_CREATE_OBJECT;
	eventMessage.lParameter = (DWORD_PTR)_gameObject;
	eventMessage.wParameter = (DWORD_PTR)_objectType;

	EventManager::GetInstance()->AddEvent(eventMessage);
}

void RemoveGameObject(GameObject* _gameObject)
{
	EventMessage eventMessage = {};

	eventMessage.mEventType = EVENT_TYPE::EVENT_TYPE_REMOVE_OBJECT;
	eventMessage.lParameter = (DWORD_PTR)_gameObject;

	EventManager::GetInstance()->AddEvent(eventMessage);
}
