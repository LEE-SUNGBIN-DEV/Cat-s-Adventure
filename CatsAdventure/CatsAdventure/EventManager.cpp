#include "pch.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameObject.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::Init()
{
}

void EventManager::Update()
{
	// ���� �����ӿ��� ����ص� Remove Object���� ���� ó��
	for (size_t i = 0; i < this->mRemoveObjectList.size(); ++i)
	{
		delete this->mRemoveObjectList[i];
	}
	this->mRemoveObjectList.clear();

	for (size_t i = 0; i < mEventList.size(); ++i)
	{
		this->Execute(mEventList[i]);
	}

	this->mEventList.clear();
}

void EventManager::Execute(const EventMessage& _eventMessage)
{
	_eventMessage.mEventType;

	switch (_eventMessage.mEventType)
	{
	case EVENT_TYPE::EVENT_TYPE_CREATE_OBJECT:
	{
		// lParameter: Object Adress
		// wParameter: Object Type
		GameObject* gameObject = (GameObject*)_eventMessage.lParameter;
		OBJECT_TYPE objectType = (OBJECT_TYPE)_eventMessage.wParameter;

		SceneManager::GetInstance()->GetCurrentScene()->AddGameObject(gameObject, objectType);
	}

		break;

	case EVENT_TYPE::EVENT_TYPE_REMOVE_OBJECT:
	{
		// lParameter: Object Adress
		// Object�� REMOVE ���·� ����
		GameObject* gameObject = (GameObject*)_eventMessage.lParameter;

		gameObject->SetIsAlive(false);
		this->mRemoveObjectList.push_back(gameObject);
	}
		break;

	case EVENT_TYPE::EVENT_TYPE_CHANGE_SCENE:



		break;
	}
}
