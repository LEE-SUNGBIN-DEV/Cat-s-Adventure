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
	size_t listSize = this->mRemoveObjectList.size();
	for (size_t i = 0; i < listSize; ++i)
	{
		delete this->mRemoveObjectList[i];
	}
	this->mRemoveObjectList.clear();

	// �̺�Ʈ ó��
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
	{
		// lParameter: Scene Adress
		// wParameter: Scene Type
		SCENE_TYPE sceneType = (SCENE_TYPE)_eventMessage.lParameter;

		SceneManager::GetInstance()->ChangeScene((SCENE_TYPE)_eventMessage.lParameter);
	}
		break;
	}
}

void EventManager::AddEvent(const EventMessage& _eventMessage)
{
	// ������ ������Ʈ�� ���� ���� ��û�� �̹� ������ ��� (���� �� ����°� ����)
	if (_eventMessage.mEventType == EVENT_TYPE::EVENT_TYPE_REMOVE_OBJECT)
	{
		for (UINT i = 0; i < this->mEventList.size(); ++i)
		{
			if (this->mEventList[i].lParameter == _eventMessage.lParameter)
			{
				return;
			}
		}
	}

	mEventList.push_back(_eventMessage);
}
