#include "stdafx.h"
#include "Store.h"
#include "ToolItemManager.h"
#include "ToolItem.h"
#include "Player.h"
#include "Inventory.h"

Store::Store()
{
}

Store::~Store()
{
}

HRESULT Store::init(int x, int y)
{
	_ItemManager = new ToolItemManager;
	_ItemManager->Init();

	_StoreWindow = IMAGEMANAGER->findImage("StoreWindow");
	_StorePortrait = IMAGEMANAGER->findImage("StoreOwnerPortrait");

	for (int i = 0; i < 4; i++)
	{
		_StoreItem[i] = IMAGEMANAGER->findImage("StoreItme");
	}

	_StoreInfo = IMAGEMANAGER->findImage("StoreInfo");
	_StoreNPC = IMAGEMANAGER->findImage("StoreOwnerDot");

	_StoreNpcRect = RectMake(x, y, _StoreNPC->getFrameWidth(), _StoreNPC->getFrameHeight());
	_StoreNpcOpen = RectMakeCenter(_StoreNpcRect.left + 25, _StoreNpcRect.top + 50, 200, 200);

	for (int i = 0; i < 4; i++)
	{
		_Item.push_back(RectMake(378, 68 + i * 104, 1041, 104));
	}
	_StoreUpArrow = IMAGEMANAGER->findImage("UpArrow");
	_StoreDownArrow = IMAGEMANAGER->findImage("DownArrow");

	_CloseButton = IMAGEMANAGER->findImage("CloseButton");
	_BlackWindow = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");
	_CloseRc = RectMake(1400, 30, _CloseButton->getWidth(), _CloseButton->getHeight());

	_StoreSearchMin = 0;

	_itemInfo = _ItemManager->GetItemList();

	_noMoney = IMAGEMANAGER->findImage("LowMoney");
	_noMoneyAlpha = 255;

	_saleItem.resize(7); //물건6개만 1개는 nullptr

	for (int i = 0; i < _saleItem.size(); i++)
	{
		_saleItem[i] = nullptr;
	}

	//------------------물품--------------------------// 

	_saleItem[0] = _itemInfo[13];  //파스닙
	_saleItem[1] = _itemInfo[14];  //감자
	_saleItem[2] = _itemInfo[15];  //케일
	_saleItem[3] = _itemInfo[16];  //돌
	_saleItem[4] = _itemInfo[17];  //잡초
	_saleItem[5] = _itemInfo[18];  //나무

	_saleKoName[0] = "파스닙 씨앗";
	_saleKoName[1] = "감자 씨앗";
	_saleKoName[2] = "케일 씨앗";
	_saleKoName[3] = "돌";
	_saleKoName[4] = "섬유";
	_saleKoName[5] = "나무";

	_saleMoney[0] = 50;    //돈
	_saleMoney[1] = 50;
	_saleMoney[2] = 70;
	_saleMoney[3] = 10;
	_saleMoney[4] = 5;
	_saleMoney[5] = 10;

	_storeOpen = false;

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

	_noMoneyAlpha -= 10;
	if (_noMoneyAlpha <= 0) _noMoneyAlpha = 0;


	if (_storeOpen)
	{
		if (PtInRect(&_Item[0], _ptMouse))
		{
			_StoreItmeFrameY = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_player->GetMoney() >= _saleMoney[_StoreSearchMin])
				{
					_inven->setPlayerBuyItme(_saleItem[_StoreSearchMin]);
					_player->SetDecreaseMoney(_saleMoney[_StoreSearchMin]);
				}
				if (_player->GetMoney() < _saleMoney[_StoreSearchMin])
				{
					_noMoneyAlpha = 255;
				}
			}
		}
		if (PtInRect(&_Item[1], _ptMouse))
		{
			_StoreItmeFrameY2 = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_player->GetMoney() >= _saleMoney[_StoreSearchMin + 1])
				{
					_inven->setPlayerBuyItme(_saleItem[_StoreSearchMin + 1]);
					_player->SetDecreaseMoney(_saleMoney[_StoreSearchMin + 1]);
				}
				if (_player->GetMoney() < _saleMoney[_StoreSearchMin + 1])
				{
					_noMoneyAlpha = 255;
				}
			}
		}
		if (PtInRect(&_Item[2], _ptMouse))
		{
			_StoreItmeFrameY3 = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_player->GetMoney() >= _saleMoney[_StoreSearchMin + 2])
				{
					_inven->setPlayerBuyItme(_saleItem[_StoreSearchMin + 2]);
					_player->SetDecreaseMoney(_saleMoney[_StoreSearchMin + 2]);
				}
				if (_player->GetMoney() < _saleMoney[_StoreSearchMin + 2])
				{
					_noMoneyAlpha = 255;
				}
			}
		}
		if (PtInRect(&_Item[3], _ptMouse))
		{
			_StoreItmeFrameY4 = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_player->GetMoney() >= _saleMoney[_StoreSearchMin + 3])
				{
					_inven->setPlayerBuyItme(_saleItem[_StoreSearchMin + 3]);
					_player->SetDecreaseMoney(_saleMoney[_StoreSearchMin + 3]);
				}
				if (_player->GetMoney() < _saleMoney[_StoreSearchMin + 3])
				{
					_noMoneyAlpha = 255;
				}
			}
		}
	}

	if (PtInRect(&_CloseRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_storeOpen = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		if (!_storeOpen) _storeOpen = true;
		else _storeOpen = false;
	}

}

void Store::render()
{
	CAMERAMANAGER->frameRender(getMemDC(), _StoreNPC, _StoreNpcRect.left, _StoreNpcRect.top);
	//if (_storeOpen)
	//{
	//	OpenStoreRender();
	//}
}

void Store::OpenStoreRender()
{
	SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), BLACK);
	_BlackWindow->alphaRender(getMemDC(), 0, 0, 200);

	HFONT font1, oldFont1;
	font1 = CreateFont(50, 0, 0, 0, 300, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("Sandoll 미생"));
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	_StoreWindow->render(getMemDC(), 350, 50);
	_StorePortrait->frameRender(getMemDC(), 140, 50, 0, 0);

	_StoreUpArrowRc = RectMake(1460, 50, _StoreUpArrow->getWidth(), _StoreUpArrow->getHeight());
	_StoreDownArrowRc = RectMake(1460, 450, _StoreDownArrow->getWidth(), _StoreDownArrow->getHeight());


	if (PtInRect(&_StoreUpArrowRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_StoreSearchMin -= 1;
		}
	}
	if (PtInRect(&_StoreDownArrowRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_StoreSearchMin += 1;
		}
	}

	_StoreItem[0]->frameRender(getMemDC(), _Item[0].left, _Item[0].top, 0, _StoreItmeFrameY);
	_StoreItem[1]->frameRender(getMemDC(), _Item[1].left, _Item[1].top, 0, _StoreItmeFrameY2);
	_StoreItem[2]->frameRender(getMemDC(), _Item[2].left, _Item[2].top, 0, _StoreItmeFrameY3);
	_StoreItem[3]->frameRender(getMemDC(), _Item[3].left, _Item[3].top, 0, _StoreItmeFrameY4);

	if (_StoreSearchMin < 0) _StoreSearchMin = 2;
	if (_StoreSearchMin > 2) _StoreSearchMin = 0;

	int RcNum = 0;
	RECT RcTxt1 = RectMake(_Item[0].left + 110, _Item[0].top + 30, 300, 70);
	RECT RcTxt2 = RectMake(_Item[1].left + 110, _Item[1].top + 30, 300, 70);
	RECT RcTxt3 = RectMake(_Item[2].left + 110, _Item[2].top + 30, 300, 70);
	RECT RcTxt4 = RectMake(_Item[3].left + 110, _Item[3].top + 30, 300, 70);

	char gold[30];

	//영어원할시 _saleItem 주석걸린거 풀고 _saleKoName 주석처리 한글은 반대

	//1번 상자
	_saleItem[_StoreSearchMin]->GetImageInven()->render(getMemDC(), _Item[0].left + 20, _Item[0].top + 20);
	//DrawText(getMemDC(), TEXT(_saleItem[_StoreSearchMin]->GetName().c_str()), 50, &RcTxt1, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	DrawText(getMemDC(), TEXT(_saleKoName[_StoreSearchMin].c_str()), 12, &RcTxt1, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	sprintf_s(gold, "%d", _saleMoney[_StoreSearchMin]);
	TextOut(getMemDC(), 1300, _Item[0].top + 30, gold, strlen(gold));

	//2번 상자
	_saleItem[_StoreSearchMin + 1]->GetImageInven()->render(getMemDC(), _Item[1].left + 20, _Item[1].top + 20);
	//DrawText(getMemDC(), TEXT(_saleItem[_StoreSearchMin + 1]->GetName().c_str()), 50, &RcTxt2, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	DrawText(getMemDC(), TEXT(_saleKoName[_StoreSearchMin + 1].c_str()), 12, &RcTxt2, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	sprintf_s(gold, "%d", _saleMoney[_StoreSearchMin + 1]);
	TextOut(getMemDC(), 1300, _Item[1].top + 30, gold, strlen(gold));

	//3번 상자
	_saleItem[_StoreSearchMin + 2]->GetImageInven()->render(getMemDC(), _Item[2].left + 20, _Item[2].top + 20);
	//DrawText(getMemDC(), TEXT(_saleItem[_StoreSearchMin + 2]->GetName().c_str()), 50, &RcTxt3, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	DrawText(getMemDC(), TEXT(_saleKoName[_StoreSearchMin + 2].c_str()), 12, &RcTxt3, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	sprintf_s(gold, "%d", _saleMoney[_StoreSearchMin + 2]);
	TextOut(getMemDC(), 1300, _Item[2].top + 30, gold, strlen(gold));

	//4번 상자
	_saleItem[_StoreSearchMin + 3]->GetImageInven()->render(getMemDC(), _Item[3].left + 20, _Item[3].top + 20);
	//DrawText(getMemDC(), TEXT(_saleItem[_StoreSearchMin + 3]->GetName().c_str()), 50, &RcTxt4, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	DrawText(getMemDC(), TEXT(_saleKoName[_StoreSearchMin + 3].c_str()), 12, &RcTxt4, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
	sprintf_s(gold, "%d", _saleMoney[_StoreSearchMin + 3]);
	TextOut(getMemDC(), 1300, _Item[3].top + 30, gold, strlen(gold));

	for (int i = 0; i < 6; i++)
	{
		if (_player->GetMoney() < _saleMoney[i])
		{
			_noMoney->alphaRender(getMemDC(), 373, 578, _noMoneyAlpha);
		}
	}

	char mo[50];
	sprintf_s(mo, "%d", _player->GetMoney());
	TextOut(getMemDC(), 392, 525, mo, strlen(mo));

	SelectObject(getMemDC(), oldFont1);
	DeleteObject(oldFont1);

	if (_StoreSearchMin < 0) _StoreSearchMin = 2;
	if (_StoreSearchMin > _saleItem.size()) _StoreSearchMin = 0;

	//==========================================================//

	_StoreUpArrow->render(getMemDC(), _StoreUpArrowRc.left, _StoreUpArrowRc.top);
	_StoreDownArrow->render(getMemDC(), _StoreDownArrowRc.left, _StoreDownArrowRc.top);
	_StoreInfo->render(getMemDC(), 100, 260);

	HFONT font2, oldFont2;
	font2 = CreateFont(40, 0, 0, 0, 300, false, false, false,
		DEFAULT_CHARSET,
		OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("Sandoll 미생"));
	oldFont2 = (HFONT)SelectObject(getMemDC(), font2);

	RECT rcText = RectMake(120, 270, 230, 200);
	DrawText(getMemDC(), TEXT("어서와, 처음이지    가죽클럽은 2블럭   아래에 있어"), 51, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(oldFont2);

	_CloseButton->render(getMemDC(), _CloseRc.left, _CloseRc.top);
}