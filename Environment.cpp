#include "stdafx.h"
#include "Environment.h"

HRESULT Environment::init()
{
	_alphaValue = 0;
	_realTimeSecond = 0;

	return S_OK;
}

void Environment::release()
{
}

void Environment::update()
{
	_timeCount = TIMEMANAGER->getElapsedTime();

	_alphaCount++;

	_realTimeSecond += _timeCount;

	cout << _realTimeSecond << endl;

	if (_realTimeSecond >= REALTIMEHALF)
	{
		if (_alphaCount % COUNTDELAY == 0)
		{
			if (_alphaValue < ALPHAVALUEMAX) _alphaValue++;
			if (_alphaValue > ALPHAVALUEMAX) _alphaValue = ALPHAVALUEMAX;

			if (_realTimeSecond > REALMAXTIME) init();
		}
	}
}

void Environment::render()
{
	IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), _alphaValue);

}
