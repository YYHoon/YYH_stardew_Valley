#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	_isDayIncrease = false;
	_isInventoryOpen = false;

	_timeRatio = REALTIMEMAX / CLOCKTIMEMAX;
	_clockCalculate = 0;
	_dayCount = 1;

	_delay = ALPHADELAY;
	_count = 0;

	_clockHand.count = 0;
	_clockHand.value = 0;
	_clockHand.angle = -PI / 2;
	_clockHand.length = 72;
	_clockHand.center.x = 1385.5f;
	_clockHand.center.y = 90;

	return S_OK;
}

void Environment::release()
{
}

void Environment::update()
{
	_elapsedTime = TIMEMANAGER->getElapsedTime();
	_clockCalculate += _elapsedTime;

	if (!_isInventoryOpen)
	{
		_realTimeSecond += _elapsedTime;

		//ClockHand
		if (_clockCalculate >= _timeRatio)
		{
			//cout << _clockCalculate << endl;
			_clockHand.count++;

			if (_clockHand.count == 1)
			{
				_clockHand.value++;
				_clockCalculate = 0;
				_clockHand.count = 0;
			}

			if (_clockHand.angle <= PI / 2)
			{
				_clockHand.angle -= CLOCKMOVEDANGLE;
			}
		}

		if (_isDayIncrease) _isDayIncrease = false;

		if (_clockHand.value >= CLOCKTIMEMAX)
		{
			_clockHand.value = 0;
			_clockHand.angle = -PI / 2;

			if (_realTimeSecond >= REALTIMEHALF && !_isDayIncrease)
			{
				_isDayIncrease = true;
				_alphaValue = 0;
				_realTimeSecond = 0;
				_dayCount++;

				/// <summary>
				cout << "IsDayIncrease :" << _isDayIncrease << endl;
				cout << "DayCount : " << _dayCount << endl;
				/// </summary>
			}
		}

		/// AlphaRender
		if (timeUpdate(TIMEMANAGER->getElapsedTime() * 60) &&
			_clockHand.value >= CLOCKTIMEHALF)
		{
			_alphaValue++;

		//	cout << _alphaValue << endl;
			if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;
		}

	}
	else
	{
		_realTimeSecond += 0;
	}

	//cout << _realTimeSecond << endl;

	_clockHand.end.x = cosf(_clockHand.angle) * _clockHand.length + _clockHand.center.x;
	_clockHand.end.y = -sinf(_clockHand.angle) * _clockHand.length + _clockHand.center.y;
}

void Environment::render(HDC _hdc)
{
	//IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(_hdc, _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(_hdc, 1300, 12);

	LineMake(_hdc, _clockHand.center.x, _clockHand.center.y, _clockHand.end.x, _clockHand.end.y);
}

