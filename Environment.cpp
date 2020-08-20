#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	_isDayIncrease = false;
	_isInventoryOpen = false;
	_isDayReset = false;

	_timeRatio = REALTIMEMAX / CLOCKTIMEMAX;
	_clockCalculate = 0;
	_monthCount = 3;
	_dayCount = 1;
	_dayOfWeek = 1;

	_delay = ALPHADELAY;
	_count = 0;

	_clockHand.count = 0;
	_clockHand.value = 0;
	_clockHand.angle = -PI / 2;
	_clockHand.length = 72;
	_clockHand.center.x = 1385.5f;
	_clockHand.center.y = 90;
	_timeOut = false;
	_minute = 0;
	_hour = 6;

	return S_OK;
}

void Environment::release()
{
}

void Environment::update()
{
	_elapsedTime = TIMEMANAGER->getElapsedTime();
	_clockCalculate += _elapsedTime;
	if (_hour == 23&&_minute ==5) 
	{
		_timeOut = true;
		SCENEMANAGER->changeScene("FARM");
	}
	if (!_isInventoryOpen)
	{
		_realTimeSecond += _elapsedTime;

		//ClockHand
		if (_clockCalculate >= _timeRatio)
		{
			_clockHand.count++;

			if (_clockHand.count == 1)
			{
				_clockHand.value++;
				_clockCalculate = 0;
				_clockHand.count = 0;
				_minute++;
				if (_minute == 6)
				{
					_hour += 1;
					_minute = 0;
				}
			}

			if (_clockHand.angle <= PI / 2)
			{
				_clockHand.angle -= CLOCKMOVEDANGLE;
			}
		}

		if (_isDayIncrease) {
			_isDayIncrease = false;
			_timeOut = false;
		}

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
				_dayOfWeek++;
				_hour = 6;
				_minute = 0;
				/// <summary>
				/// </summary>
			}
		}

		/// AlphaRender
		if (timeUpdate(TIMEMANAGER->getElapsedTime() * 60) &&
			_clockHand.value >= CLOCKTIMEHALF)
		{
			_alphaValue++;
			if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;
		}

	}
	else
	{
		_realTimeSecond += 0;
	}

	if (_dayCount >= 31)
	{
		_dayCount = 1;
		_monthCount++;
		if (_monthCount >= 13) _monthCount = 1;
	}

	if (_isDayReset)
	{
		_isDayReset = false;
		_clockHand.value = 0;
		_clockHand.angle = -PI / 2;

		_isDayIncrease = true;
		_alphaValue = 0;
		_realTimeSecond = 0;
		_dayCount++;
		_dayOfWeek++;
		_hour = 6;
		_minute = 0;
		/// <summary>
		/// </summary>
	}

	_clockHand.end.x = cosf(_clockHand.angle) * _clockHand.length + _clockHand.center.x;
	_clockHand.end.y = -sinf(_clockHand.angle) * _clockHand.length + _clockHand.center.y;
}

void Environment::render(HDC _hdc)
{
	//IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(_hdc, _alphaValue);

	IMAGEMANAGER->findImage("Environment_Clock")->render(_hdc, 1300, 12);

	if (_timeOut)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->render(_hdc);
	}
	//----------------------시계---------------------------------------------------//
	SetTextColor(_hdc, BLACK);

	HFONT font1, oldFont1;
	font1 = CreateFont(40, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	oldFont1 = (HFONT)SelectObject(_hdc, font1);

	char month[30];
	char day[30];
	char time[30];
	sprintf_s(month, "%d.", _monthCount);
	sprintf_s(day, "%d,", _dayCount);
	sprintf_s(time, "%d : %d0", _hour, _minute);

	TextOut(_hdc, 1452, 30, day, strlen(day));
	TextOut(_hdc, 1420, 30, month, strlen(month));
	TextOut(_hdc, 1435, 120, time, strlen(time));

	if (_dayOfWeek % 7 == 1) 	TextOut(_hdc, 1492, 30, "월요일", strlen("월요일"));
	if (_dayOfWeek % 7 == 2) 	TextOut(_hdc, 1492, 30, "화요일", strlen("화요일"));
	if (_dayOfWeek % 7 == 3) 	TextOut(_hdc, 1492, 30, "수요일", strlen("수요일"));
	if (_dayOfWeek % 7 == 4) 	TextOut(_hdc, 1492, 30, "목요일", strlen("목요일"));
	if (_dayOfWeek % 7 == 5) 	TextOut(_hdc, 1492, 30, "금요일", strlen("금요일"));
	if (_dayOfWeek % 7 == 6) 	TextOut(_hdc, 1492, 30, "토요일", strlen("토요일"));
	if (_dayOfWeek % 7 == 0) 	TextOut(_hdc, 1492, 30, "일요일", strlen("일요일"));

	SelectObject(_hdc, oldFont1);
	DeleteObject(oldFont1);

	LineMake(_hdc, _clockHand.center.x, _clockHand.center.y, _clockHand.end.x, _clockHand.end.y);
	//-----------------------------------------------------------------------------//
}

