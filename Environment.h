#pragma once
#include "gameNode.h"

class Environment : public gameNode
{
private:
	int _alphaValue;			//알파값
	int _alphaCount;			//알파렌더 속도 조절

	float _timeCount;			//연산용 시간
	float _realTimeSecond;		//현실시간(초)

public:
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

