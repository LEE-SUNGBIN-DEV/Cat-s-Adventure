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
	// 이전 프레임에서 등록해둔 Remove Object들을 삭제 처리
	size_t listSize = this->mRemoveObjectList.size();
	for (size_t i = 0; i < listSize; ++i)
	{
		delete this->mRemoveObjectList[i];
	}
	this->mRemoveObjectList.clear();

	// 이벤트 처리
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
		// Object를 REMOVE 상태로 변경
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
	// 동일한 오브젝트에 대한 삭제 요청이 이미 존재할 경우 (여러 번 지우는거 방지)
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
