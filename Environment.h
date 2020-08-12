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

	/// 원본 게임에서의 시계 각도(Percentage)
	float _originalTime = 860;
	float _originalDelay = 7.96296f;
	float _originalRatio;
	/// </summary>

	float _clockCalculate;		//시간 계산
	float _currentTimeSec;		//현재 시간

	float _elapsedTime;			//연산용 시간
	float _realTimeSecond;		//현실시간(초)

	bool _isGamePause;			//게임 시간이 돌아가면

	tagClockHand _clockHand;	//시계침 struct
	int _clockValue;			//시계 값(현재 시계침의 위치)


	float _delay;
	float _count;

	bool timeUpdate(const float count)
	{
		_count += count;
		if (_count >= _delay)
		{
			_count -= _delay;
			return true;
		}
		return false;
	}

public:
	Environment()	{};
	~Environment()	{};

	HRESULT init();
	void release();
	void update();
	void render();
};

