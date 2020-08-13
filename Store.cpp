#include "stdafx.h"
#include "Store.h"

Store::Store()
{
}

Store::~Store()
{
}

HRESULT Store::init()
{
	_StoreWindow = IMAGEMANAGER->findImage("StoreWindow");
	_StorePortrait = IMAGEMANAGER->findImage("StoreOwnerPortrait");

	for (int i = 0; i < 4; i++)
	{
		_StoreItem[i] = IMAGEMANAGER->findImage("StoreItme");
	}

	_StoreInfo = IMAGEMANAGER->findImage("StoreInfo");
	_StoreNPC = IMAGEMANAGER->findImage("StoreOwnerDot");

	_StoreNpcRect = RectMake(WINSIZEX / 2, WINSIZEY / 2 - 100, _StoreNPC->getFrameWidth(), _StoreNPC->getFrameHeight());
	_StoreNpcOpen = RectMakeCenter(_StoreNpcRect.left + 25, _StoreNpcRect.top + 50, 200, 200);

	for (int i = 0; i < 4; i++)
	{
		_Item.push_back(RectMake(378, 68 + i * 104, 1041, 104));
	}

	return S_OK;
}

void Store::release()
{
}

void Store::update()
{
	_StoreItmeFrameY = 0;
	_StoreItmeFrameY2 = 0;
	_StoreItmeFrameY3 = 0;
	_StoreItmeFrameY4 = 0;

	if (PtInRect(&_Item[0], _ptMouse)) _StoreItmeFrameY = 1;
	if (PtInRect(&_Item[1], _ptMouse)) _StoreItmeFrameY2 = 1;
	if (PtInRect(&_Item[2], _ptMouse)) _StoreItmeFrameY3 = 1;
	if (PtInRect(&_Item[3], _ptMouse)) _StoreItmeFrameY4 = 1;


}

void Store::render()
{
	
	Rectangle(getMemDC(), _StoreNpcOpen);
	_StoreNPC->frameRender(getMemDC(), _StoreNpcRect.left, _StoreNpcRect.top, 0, 0);
}

void Store::OpenStoreRender()
{
	SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), BLACK);

	HFONT font1, oldFont1;
	font1 = CreateFont(40, 0, 0, 0, 300, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("Sandoll 미생"));
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	_StoreWindow->render(getMemDC(), 350, 50);
	_StorePortrait->frameRender(getMemDC(), 140, 50, 0, 0);
	_StoreInfo->render(getMemDC(), 100, 260);
	RECT rcText = RectMake(110, 270, 230, 200);
	DrawText(getMemDC(), TEXT("어서와, 여기는 상점이야 물건은없지만!"), 38, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	draw();
	DeleteObject(oldFont1);
}

void Store::draw()
{
	_StoreItem[0]->frameRender(getMemDC(), _Item[0].left, _Item[0].top, 0, _StoreItmeFrameY);
	_StoreItem[1]->frameRender(getMemDC(), _Item[1].left, _Item[1].top, 0, _StoreItmeFrameY2);
	_StoreItem[2]->frameRender(getMemDC(), _Item[2].left, _Item[2].top, 0, _StoreItmeFrameY3);
	_StoreItem[3]->frameRender(getMemDC(), _Item[3].left, _Item[3].top, 0, _StoreItmeFrameY4);
}
