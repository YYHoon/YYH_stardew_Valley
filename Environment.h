#pragma once
#include "gameNode.h"

struct tagClockHand
{
	POINT center;	//중점
	POINT End;		//시계침 끝점
	int length;		//시계침 길이
	float angle;	//시계침 각도
};

class Environment : public gameNode
{
private:
	int _alphaValue;			//알파값
	int _alphaCount;			//알파렌더 속도 조절

	float _clockCalculrate;		//뭐였지

	float _elapsedTime;			//연산용 시간
	float _realTimeSecond;		//현실시간(초)

	bool _inGameTimeRunning;

	tagClockHand _clockHand;
	int _clockCount;			//시계의 카운트
	int _clockValue;			//시계 값(현재 시계침의 위치)

public:
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

