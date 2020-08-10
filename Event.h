#pragma once
class Event
{
public:
	//이벤트가 시작할때 실행할 함수
	virtual void EventStart(float centerX, float centerY) = 0;
	//이벤트 업데이트
	virtual bool EventUpdate() = 0;

};

class StopCamera : public Event
{

public:

	void EventStart(float centerX, float centerY)override;
	bool EventUpdate()override;
};