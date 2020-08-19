#include "stdafx.h"
#include "IsSleep.h"

HRESULT IsSleep::init()
{	
	_sleepSlect = IMAGEMANAGER->findImage("SelectUI");

	_isSleepYesRc = RectMake(191, 680, 1215, 82);
	_non = RectMake(191, 764, 1215, 82);

	_isSleep = false;

	return S_OK;
}

void IsSleep::release()
{
}

void IsSleep::update()
{

	if (PtInRect(&_isSleepYesRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isSleep = true;
		}
	}
	//	if (PtInRect(&_non, _ptMouse)) //��â ����?


}

void IsSleep::render()
{
	SetTextColor(getMemDC(), BLACK);
	_sleepSlect->render(getMemDC(), 163, 600);


	TextOut(getMemDC(), 200, 640, "�Ϸ縦 �������ұ��?", strlen("�Ϸ縦 �������ұ��?"));

	TextOut(getMemDC(), _isSleepYesRc.left + 5, _isSleepYesRc.top + 20, "��", strlen("��"));
	TextOut(getMemDC(), _non.left + 5, _non.top + 20, "�ƴϿ�", strlen("�ƴϿ�"));

	
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