#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;


	_isInventoryOpen = false;

	/// <summary>
	_ratio = (_originalDelay * 100) / _originalTime;
	//cout << "Ratio : " << _ratio << "%" << endl;
	/// </summary>

	_clockCalculate = 0;
	_dayCount = 1;

	_clockHand.count = 0;

	_currentTimeSec = 0;
	_clockHand.value = 0;
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
	_clockCalculate += _elapsedTime;

	_currentTimeSec = (int)_realTimeSecond;

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_isInventoryOpen)
		{
			_isInventoryOpen = true;
		}
		else
		{
			_isInventoryOpen = false;
		}
	}

	if (!_isInventoryOpen) _realTimeSecond += _elapsedTime;
	else _realTimeSecond += 0;

	if (!_isInventoryOpen)
	{
		//ClockHand
		/////////////////////////////////////<Test>

		///////////////////<↓↓↓↓시간 계산 현재 20초 기준 차후 수식으로 고칠 것↓↓↓↓>///////////////////
		if (_clockCalculate >= 0.1669f)
		{
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
		///////////////////<↑↑↑↑시간 계산 현재 20초 기준 차후 수식으로 고칠 것↑↑↑↑>///////////////////

		//	cout << "ClockValue : " << _clockHand.value << endl;

		if (_clockHand.value >= CLOCKTIMEMAX)
		{
			_clockHand.value = 0;
			_clockHand.angle = -PI / 2;
		}

		_clockHand.end.x = cosf(_clockHand.angle) * _clockHand.length + _clockHand.center.x;
		_clockHand.end.y = -sinf(_clockHand.angle) * _clockHand.length + _clockHand.center.y;

		/////////////////////////////////////</Test>

		/// AlphaRender
		if (_realTimeSecond >= REALTIMEHALF)
		{
			if (timeUpdate(TIMEMANAGER->getElapsedTime() * 60) && _clockHand.value >= CLOCKTIMEHALF)
			{
				_alphaValue++;

				if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;
			}
			if (_clockHand.value >= CLOCKTIMEMAX && _alphaValue == ALPHAVALUEMAX)
			{
				_alphaValue = 0;
				_realTimeSecond = 0;
				_dayCount++;
			}
		}
	}
}

void Environment::render()
{
	IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(getMemDC(), 1300, 12);

	LineMake(getMemDC(), _clockHand.center.x, _clockHand.center.y, _clockHand.end.x, _clockHand.end.y);

}
