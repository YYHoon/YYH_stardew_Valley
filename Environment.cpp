#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	_inGameTimeRunning = true;

	_clockCalculrate = 0;
	_clockValue = 0;
	_clockHand.angle = -PI / 2;
	_clockHand.length = 72;
	_clockHand.center.x = 1384;
	_clockHand.center.y = 89;

	return S_OK;
}

void Environment::release()
{
}

void Environment::update()
{
	_elapsedTime = TIMEMANAGER->getElapsedTime();

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_inGameTimeRunning) _inGameTimeRunning = false;
		else _inGameTimeRunning = true;
	}

	_alphaCount++;
	_clockCount++;

	if (_inGameTimeRunning) _realTimeSecond += _elapsedTime;
	if (!_inGameTimeRunning) _realTimeSecond += 0;

	//cout << _realTimeSecond << endl;

	if (_realTimeSecond >= REALTIMEHALF)
	{
		if (_alphaCount % ALPHADELAY == 0)
		{
			if (_alphaValue < ALPHAVALUEMAX) _alphaValue++;
			if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;

			if (_realTimeSecond > REALTIMEMAX)
			{
				_alphaValue = 0;
				_realTimeSecond = 0;
			}
		}
	}

	if (_clockCount % 11 == 0)
	{
		if (_clockHand.angle <= PI / 2)
		{
			if (_inGameTimeRunning)
			{
				_clockHand.angle -= CLOCKMOVEDANGLE;
			}
		}

		if (_clockValue >= 109 && _alphaValue >= ALPHAVALUEMAX)
		{
			_clockValue = 0;
			_clockHand.angle = -PI / 2;
		}
	}

	_clockHand.End.x = cosf(_clockHand.angle) * _clockHand.length + _clockHand.center.x;
	_clockHand.End.y = -sinf(_clockHand.angle) * _clockHand.length + _clockHand.center.y;

}

void Environment::render()
{
	IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(getMemDC(), 1300, 12);

	//LineMake(getMemDC(), _clockHand.center.x, _clockHand.center.y, _clockHand.End.x, _clockHand.End.y);
}
