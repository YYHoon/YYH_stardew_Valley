#pragma once
#include "Event.h"
class EventManager
{
private:
	EventManager();
	~EventManager();
public : 
	static EventManager* GetInstance()
	{
		static EventManager instance;
		return &instance;
	}
	vector<Event*> vEventList;

	void Update();
	void AddEvent(Event* event);
};

