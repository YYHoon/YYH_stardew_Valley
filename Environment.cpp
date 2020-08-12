#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	_isGamePause = false;

	/// <summary>
	//_defaultRatio = (_defaultDelay * 100) / _defaultTime;
	//cout << "DefaultRatio : " << _defaultRatio << endl;
	/// </summary>
	

	//_clockCalculate = ()/REALTIMEMAX;

	_currentTimeSec = 0;
	_clockValue = 0;
	_clockHand.angle = -PI / 2;
	_clockHand.length = 72;
	_clockHand.center.x = 1385.5f;
	_clockHand.center.y = 90;

	_delay = ALPHADELAY;

	return S_OK;
}

void Environment::release()
{
}

void Environment::update()
{
	_elapsedTime = TIMEMANAGER->getElapsedTime();

	_currentTimeSec = (int)_realTimeSecond;

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		!_isGamePause ? _isGamePause = true : _isGamePause = false;
	}

	!_isGamePause ? _realTimeSecond += _elapsedTime : _realTimeSecond += 0;

	//ClockHand
	if (!_isGamePause)
	{
		for (int i = 0; i < _currentTimeSec; i++)
		{
			_clockValue + i;

		}
		if (_clockHand.angle <= PI / 2)
		{
			_clockHand.angle -= CLOCKMOVEDANGLE;
		}

		if (_clockValue >= CLOCKMAX)
		{
			_clockValue = 0;
			_clockHand.angle = -PI / 2;
		}
	}

	_clockHand.End.x = cosf(_clockHand.angle) * _clockHand.length + _clockHand.center.x;
	_clockHand.End.y = -sinf(_clockHand.angle) * _clockHand.length + _clockHand.center.y;

	/// AlphaRender
	if (_realTimeSecond >= REALTIMEHALF)
	{
		if (timeUpdate(TIMEMANAGER->getElapsedTime() * 60))
		{
			_alphaValue++;

			if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;

			/// <summary>
			///cout << "AlphaValue : " << _alphaValue << endl;
			/// </summary>
		}

		if (_realTimeSecond > REALTIMEMAX)
		{
			_alphaValue = 0;
			_realTimeSecond = 0;
		}
	}

}

void Environment::render()
{
	IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(getMemDC(), 1300, 12);

	LineMake(getMemDC(), _clockHand.center.x, _clockHand.center.y, _clockHand.End.x, _clockHand.End.y);
}
