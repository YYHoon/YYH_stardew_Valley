#include "stdafx.h"
#include "EventManager.h"

void EventManager::Update()
{
	if (vEventList.empty()) return;
	bool IsEventEnd = vEventList[0]->EventUpdate();

	if (IsEventEnd)
	{
		SAFE_DELETE(vEventList[0]);
		vEventList.erase(vEventList.begin());
		if (!vEventList.empty()) {
		//	vEventList[0]->EventStart();
		}
	}
	
}

void EventManager::AddEvent(Event* event)
{
	if (vEventList.empty()) 
	{
		//event->EventStart();
	}

	vEventList.push_back(event);
}
