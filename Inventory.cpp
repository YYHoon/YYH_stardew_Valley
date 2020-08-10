#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	InventoryImageInit();

	_isInventoryOpen = false;								//인벤토리 초기값은 닫혀있음
	_tabNum = 1;											//인벤토리 탭의 기본 번호
	_craftTabNum = 1;
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_isInventoryOpen) _isInventoryOpen = true;		//인벤토리가 열렸을 때
		else _isInventoryOpen = false;						//인벤토리가 닫혔을 때
	}

	if (!_isInventoryOpen) _tabNum = 1;						//인벤토리 닫았을 때 1번 탭으로 리셋

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (_viInvenStaticRC = _vInvenStaticRC.begin(); _viInvenStaticRC != _vInvenStaticRC.end(); ++_viInvenStaticRC)
		{
			if (PtInRect(&_inventoryCloseRC, _ptMouse)) _isInventoryOpen = false;				//인벤토리에서 [X]버튼을 눌렀을 때

			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_invenTabRC[i], _ptMouse)) _tabNum = i + 1;						//각 탭을 눌렀을 때
			}
		}

		for (_viInvenDynamicRC = _vInvenDynamicRC.begin(); _viInvenDynamicRC != _vInvenDynamicRC.end(); ++_viInvenDynamicRC)
		{
			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				if (PtInRect(&_inventoryRC[InventoryIndex], _ptMouse))
				{
					cout << InventoryIndex + 1 << endl;											//각 인벤토리 칸을 눌렀을 때
				}
			}

			if (PtInRect(&_menuUpRC, _ptMouse)) _craftTabNum--;
			if (PtInRect(&_menuDownRC, _ptMouse)) _craftTabNum++;

			if (_craftTabNum <= 0) _craftTabNum = 1;
			if (_craftTabNum >= 3) _craftTabNum = 2;
		}
		
		//if (PtInRect(&_TitleRC, _ptMouse) && _tabNum == 4) SCENEMANAGER->changeScene();			//[타이틀 메뉴로] 눌렀을 때
		if (PtInRect(&_closeRC, _ptMouse) && _tabNum == 4) PostQuitMessage(0);					//[게임 종료] 눌렀을 때

		/*
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(_vInvenTabRC[i], _ptMouse))
			{
				_tabNum = i + 1;
			}
		}

		for (int i = 0; i < 12; i++)
		{
			if (PtInRect(_vInvenDynamicRC[i], _ptMouse))
			{
				cout << i+1 << endl;
			}
		}


		//if (PtInRect(&_titleRC, _ptMouse)) SCENEMANAGER->changeScene();		//[타이틀 메뉴로] 눌렀을 때
		if (PtInRect(&_closeRC, _ptMouse)) PostQuitMessage(0);					//[게임 종료] 눌렀을 때
	*/
	}
}

void Inventory::render()
{
	if (_isInventoryOpen)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);

		switch (_tabNum)
		{
			case 1:		//인벤토리 탭
			{
				_vInvenDynamicRC.clear();

				IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), IMAGECOOR);
					
				for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
				{
					_inventoryRC[InventoryIndex] = RectMake(417 + InventoryIndex * 64, 230, 64, 64);	//각 인벤토리 칸의 렉트
					_vInvenDynamicRC.push_back(_inventoryRC[InventoryIndex]);
				}

				cout << "1" <<endl;
			}
			break;
			case 2:		//제작 탭
			{
				_vInvenDynamicRC.clear();

				if (_craftTabNum == 1)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), IMAGECOOR);
				}
				else if (_craftTabNum == 2)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Craft_bot")->render(getMemDC(), IMAGECOOR);
				}

				_menuUpRC = RectMake(1170, 233, 32, 35);									//제작 탭에서 아래 화살표
				_menuDownRC = RectMake(1170, 464, 32, 35);									//제작 탭에서 아래 화살표

				_vInvenDynamicRC.push_back(_menuUpRC);
				_vInvenDynamicRC.push_back(_menuDownRC);

				cout << "2" << endl;
			}
			break;
			case 3:		//키 알림 탭
			{
				_vInvenDynamicRC.clear();

				IMAGEMANAGER->findImage("UI_Inventory_KeyInfo")->render(getMemDC(), IMAGECOOR);

				cout << "3" << endl;
			}
			break;
			case 4:		//게임 종료탭
			{
				_vInvenDynamicRC.clear();

				IMAGEMANAGER->findImage("UI_Inventory_Game_Close")->render(getMemDC(), IMAGECOOR);

				_titleRC = RectMake(665, 334, 272, 96);										//종료탭에서 [타이틀 메뉴로] 버튼
				_closeRC = RectMake(699, 470, 204, 96);										//종료탭에서 [게임 종료] 버튼

				cout << "4" << endl;
			}
			break;
		}

		for (int InvenTab = 0; InvenTab < 4; InvenTab++)
		{
			_invenTabRC[InvenTab] = RectMake(424 + InvenTab * 64, 126, 64, 64);				//인벤토리 탭 렉트

			_vInvenStaticRC.push_back(_invenTabRC[InvenTab]);
		}

		_inventoryCloseRC = RectMake(1240, 102, 44, 44);
		_vInvenStaticRC.push_back(_inventoryCloseRC);										//인벤토리 [X] 버튼
		/*		
		Rectangle(getMemDC(), _inventoryCloseRC);

		Rectangle(getMemDC(), _titleRC);

		Rectangle(getMemDC(), _closeRC);

		for (int i = 0; i < 5; i++) 
		{
			Rectangle(getMemDC(), _vInvenTabRC[i]);
		}


		for (int i = 0; i < 12; i++)
		{
			Rectangle(getMemDC(), _vInventoryRC[i]);
		}
		*/
	}

	else
	{
		_vInvenStaticRC.clear();
		_vInvenDynamicRC.clear();
	}

	
	/////////////////////////////////////////////////////////////////////////// <Debug_Rect>

	//for (int InvenTab = 0; InvenTab < 4; InvenTab++)
	//{
	//	Rectangle(getMemDC(), _invenTabRC[InvenTab]);
	//}
	//
	//Rectangle(getMemDC(), _inventoryCloseRC);
	//
	//for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
	//{
	//	Rectangle(getMemDC(), _inventoryRC[InventoryIndex]);
	//}
	//
	//Rectangle(getMemDC(), _closeRC);

	//Rectangle(getMemDC(), _menuUpRC);
	//Rectangle(getMemDC(), _menuDownRC);

	/////////////////////////////////////////////////////////////////////////// </Debug_Rect>
	
}

void Inventory::InventoryImageInit()
{
	IMAGEMANAGER->addImage("Inventory_BG", "Image/Inventory_BG.bmp", 1600, 900, false, BLACK);
	IMAGEMANAGER->addImage("UI_Inventory_Day", "Image/UI_Inventory_Day.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Night", "Image/UI_Inventory_Night.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_top", "Image/UI_Inventory_Craft_top.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_bot", "Image/UI_Inventory_Craft_bot.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_KeyInfo", "Image/UI_Inventory_KeyInfo.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Game_Close", "Image/UI_Inventory_Game_Close.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("Inventory_Close", "Image/Inventory_Close.bmp", 44, 44, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI_Inventory_Trashcan", "Image/UI_Inventory_Trashcan.bmp", 184, 71, 4, 1, true, MAGENTA);

	/////////////////////<Testing>
	IMAGEMANAGER->addImage("Item_Axe", "Image/ItemTest/Item_Axe.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Item_Handplow", "Image/ItemTest/Item_Handplow.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Item_Knife", "Image/ItemTest/Item_Knife.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Item_Pickaxe", "Image/ItemTest/Item_Pickaxe.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Item_Sickle", "Image/ItemTest/Item_Sickle.bmp", 64, 64, true, MAGENTA);
	/////////////////////</Testing>
}
