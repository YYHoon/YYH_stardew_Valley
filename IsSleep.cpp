#include "stdafx.h"
#include "IsSleep.h"

HRESULT IsSleep::init()
{
	_sleepSlect = IMAGEMANAGER->findImage("SelectUI");
	_black = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");

	_isSleepYesRc = RectMake(191, 680, 1215, 82);
	_non = RectMake(191, 764, 1215, 82);

	_isSleep = false;
	_isSelectOpen = false;

	_alp = 0;


	return S_OK;
}

void IsSleep::release()
{
}

void IsSleep::update()
{
	if (_isSelectOpen)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&_isSleepYesRc, _ptMouse))
			{
				_isSleep = true;
				_alp = 255;
			}

			if (PtInRect(&_non, _ptMouse))
			{
				_isSelectOpen = false;
			}
		}
	}
	else _isSelectOpen = false;

	if (_isSleep)
	{
		_isSelectOpen = false;
		_isSleep = false;
	}

	_alp -= 10;
	if (_alp <= 0) _alp = 0;
}

void IsSleep::render()
{
	HFONT SleepFont, oldSleepFont;

	SleepFont = CreateFont(40, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	oldSleepFont = (HFONT)SelectObject(getMemDC(), SleepFont);
	if (_isSelectOpen)
	{
		SetTextColor(getMemDC(), BLACK);
		_sleepSlect->render(getMemDC(), 163, 600);

		TextOut(getMemDC(), 200, 640, "하루를 마무리할까요?", strlen("하루를 마무리할까요?"));

		TextOut(getMemDC(), _isSleepYesRc.left + 5, _isSleepYesRc.top + 20, "네", strlen("네"));
		TextOut(getMemDC(), _non.left + 5, _non.top + 20, "아니요", strlen("아니요"));


		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		HPEN myPen = CreatePen(0, 3, RGB(255, 0, 0));
		HGDIOBJ oldPen = SelectObject(getMemDC(), myPen);

		if (PtInRect(&_isSleepYesRc, _ptMouse)) Rectangle(getMemDC(), _isSleepYesRc);
		if (PtInRect(&_non, _ptMouse)) Rectangle(getMemDC(), _non);

		SelectObject(getMemDC(), oldBrush);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(myBrush);
		DeleteObject(myPen);
	}

	SelectObject(getMemDC(), oldSleepFont);
	DeleteObject(oldSleepFont);

	_black->alphaRender(getMemDC(), 0, 0, _alp);
}