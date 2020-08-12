#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	_isGamePause = false;

	/// <summary>
	_originalRatio = ((_originalDelay * 100) / _originalTime);
	cout << "OriginalRatio : " << _originalRatio << "%" << endl;
	/// </summary>

	//_clockCalculate = ()/REALTIMEMAX;

	_currentTimeSec = 0;
	_clockValue = 0;
	_clockHand.Angle = -PI / 2;
	_clockHand.Length = 72;
	_clockHand.Center.x = 1385.5f;
	_clockHand.Center.y = 90;

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

	if (!_isGamePause)
	{
		//ClockHand
		/////////////////////////////////////<Test>
		for (int i = 0; i < _currentTimeSec; i++)
		{
			_clockValue += i;
		}

		if (_clockHand.Angle <= PI / 2)
		{
			_clockHand.Angle -= CLOCKMOVEDANGLE;
		}

		//cout << "_currentTimeSec : " << _currentTimeSec << endl;

		if (/*_clockValue >= CLOCKMAX*/ _clockHand.Angle < PI / 2)
		{
			_clockValue = 0;
			_clockHand.Angle = -PI / 2;
		}

		_clockHand.End.x = cosf(_clockHand.Angle) * _clockHand.Length + _clockHand.Center.x;
		_clockHand.End.y = -sinf(_clockHand.Angle) * _clockHand.Length + _clockHand.Center.y;
		/////////////////////////////////////</Test>

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

}

void Environment::render()
{
	IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(getMemDC(), 1300, 12);

	LineMake(getMemDC(), _clockHand.Center.x, _clockHand.Center.y, _clockHand.End.x, _clockHand.End.y);
}
