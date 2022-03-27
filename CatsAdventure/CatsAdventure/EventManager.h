#pragma once

struct EventMessage
{
	EVENT_TYPE	mEventType;
	DWORD_PTR	lParameter;
	DWORD_PTR	wParameter;
};

class EventManager
{
private:
	vector<EventMessage> mEventList;
	vector<GameObject*> mRemoveObjectList;

	EventManager();
	~EventManager();

public:

	static EventManager* GetInstance()
	{
		static EventManager manager;

		return &manager;
	}

	void Init();
	void Update();
	void Execute(const EventMessage& _eventMessage);
	void AddEvent(const EventMessage& _eventMessage)
	{
		mEventList.push_back(_eventMessage);
	}
};

