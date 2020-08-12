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
	_CloseButton = IMAGEMANAGER->findImage("CloseButton");

	_CloseRc = RectMake(1400, 30, _CloseButton->getWidth(), _CloseButton->getHeight());

	_StoreNpcRect = RectMake(WINSIZEX / 2, WINSIZEY / 2 - 100, _StoreNPC->getFrameWidth(), _StoreNPC->getFrameHeight());
	_StoreNpcOpen = RectMakeCenter(_StoreNpcRect.left + 25, _StoreNpcRect.top + 50, 200, 200);

	for (int i = 0; i < 20; i++)
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
}

void Store::render()
{
}
