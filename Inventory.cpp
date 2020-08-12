#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_isInventoryOpen = false;								//인벤토리 초기값은 닫혀있음
	_tabNum = 1;											//인벤토리 탭의 기본 번호
	_craftTabNum = 1;										//제작 탭에서 첫번째 페이지

	_invenOpenX = 417;
	_invenOpenY = 230;

	//_invenCloseUX = 423;
	//_invenCloseUY = 10;

	_selecRcX = 417;
	_selecRcY = 230;

//-----------------------QuickSlot-----------------------------------
	_quickSlot.Image = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect.Image = IMAGEMANAGER->findImage("QuickSlotSelect");
	
	_quickSlotY = 747;
	_quickSlotSelectRcX = 423;
	_quickSlotSelectRcY = 763;

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
			if (PtInRect(&_inventoryCloseRC, _ptMouse)) _isInventoryOpen = false;		//인벤토리에서 [X]버튼을 눌렀을 때
			
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_invenTabRC[i], _ptMouse)) _tabNum = i + 1;				//각 탭을 눌렀을 때
			}
		}

		for (_viInvenDynamicRC = _vInvenDynamicRC.begin(); _viInvenDynamicRC != _vInvenDynamicRC.end(); ++_viInvenDynamicRC)
		{
			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				if (PtInRect(&_indexRC[InventoryIndex], _ptMouse))
				{
					//cout << InventoryIndex + 1 << endl;									//각 인벤토리 칸을 눌렀을 때
				}
			}

			/////////////// <제작 페이지 이동>
			if (PtInRect(&_menuUpRC, _ptMouse)) _craftTabNum--;
			if (PtInRect(&_menuDownRC, _ptMouse)) _craftTabNum++;

			if (_craftTabNum <= 0) _craftTabNum = 1;
			if (_craftTabNum >= 3) _craftTabNum = 2;
			/////////////// </제작 페이지 이동>
		}

		//if (PtInRect(&_TitleRC, _ptMouse) && _tabNum == 4) SCENEMANAGER->changeScene();	//[타이틀 메뉴로] 눌렀을 때
		if (PtInRect(&_closeRC, _ptMouse) && _tabNum == 4) PostQuitMessage(0);			//[게임 종료] 눌렀을 때
	}


	for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
	{
		_indexRC[InventoryIndex] = RectMake(_invenOpenX + InventoryIndex * 64, _invenOpenY, 64, 64);	//각 인벤토리 칸의 렉트
		_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
	}

	if (!_isInventoryOpen)
	{
		_quickSlotSelect.RC = RectMake(_selecRcX, _selecRcY, _quickSlotSelect.Image->getWidth(), _quickSlotSelect.Image->getHeight());
		quickSlotMove();
	}
	else
	{
		_quickSlotSelect.RC = RectMake(-100,-100,0,0);
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

			IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);

			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				_indexRC[InventoryIndex] = RectMake(_invenOpenX + InventoryIndex *64 , _invenOpenY, 64, 64);	//각 인벤토리 칸의 렉트
				_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
			
			}			
		}
		break;
		case 2:		//제작 탭
		{
			_vInvenDynamicRC.clear();

			if (_craftTabNum == 1)							//1번 페이지
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);
			}
			else if (_craftTabNum == 2)						//2번 페이지
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_bot")->render(getMemDC(), INVENIMAGECOOR);
			}

			_menuUpRC = RectMake(1170, 233, 32, 35);		//제작 탭에서 위 화살표
			_menuDownRC = RectMake(1170, 464, 32, 35);		//제작 탭에서 아래 화살표

			_vInvenDynamicRC.push_back(_menuUpRC);
			_vInvenDynamicRC.push_back(_menuDownRC);

			//cout << "2" << endl;
		}
		break;
		case 3:		//키 알림 탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_KeyInfo")->render(getMemDC(), INVENIMAGECOOR);

			//cout << "3" << endl;
		}
		break;
		case 4:		//게임 종료탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_Game_Close")->render(getMemDC(), INVENIMAGECOOR);

			_titleRC = RectMake(665, 334, 272, 96);										//종료탭에서 [타이틀 메뉴로] 버튼
			_closeRC = RectMake(699, 470, 204, 96);										//종료탭에서 [게임 종료] 버튼

			//cout << "4" << endl;
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
	}

	else
	{
		_vInvenStaticRC.clear();
		_vInvenDynamicRC.clear();
	}


	////////////////////////QuickSlot///////////////////////////////////////////
	RECT temp;
	if (!_isInventoryOpen)
	{
		_quickSlot.Image->render(getMemDC(), 407, _quickSlotY);
		for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
		{
			_indexRC[InventoryIndex] = RectMake(423 + InventoryIndex * 64, 763, 64, 64);	//각 인벤토리 칸의 렉트
			/*if (IntersectRect(&temp, &_vInvenIndexRC[0], &_quickSlotSelectRc))
			{
				cout << "낫" << endl;
			}
			if (IntersectRect(&temp, &_vInvenIndexRC[1], &_quickSlotSelectRc))
			{
				cout << "단검" << endl;
			}*/
		}
		
		_quickSlotSelect.Image->render(getMemDC(), _quickSlotSelectRcX, _quickSlotSelectRcY);
	}
	Rectangle(getMemDC(), _quickSlotSelect.RC);
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
	//
	//Rectangle(getMemDC(), _menuUpRC);
	//Rectangle(getMemDC(), _menuDownRC);

	/////////////////////////////////////////////////////////////////////////// </Debug_Rect>

}

void Inventory::quickSlotMove()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_quickSlotSelectRcX = 423;
		_selecRcX = 417;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotSelectRcX = 423 + 64;
		_selecRcX = 417 + 64;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotSelectRcX = 423 + 64 * 2;
		_selecRcX = 417 + 64 * 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotSelectRcX = 423 + 64 * 3;
		_selecRcX = 417 + 64 * 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotSelectRcX = 423 + 64 * 4;
		_selecRcX = 417 + 64 * 4;
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_quickSlotSelectRcX = 423 + 64 * 5;
		_selecRcX = 417 + 64 * 5;
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_quickSlotSelectRcX = 423 + 64 * 6;
		_selecRcX = 417 + 64 * 6;
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_quickSlotSelectRcX = 423 + 64 * 7;
		_selecRcX = 417 + 64 * 7;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_quickSlotSelectRcX = 423 + 64 * 8;
		_selecRcX = 417 + 64 * 8;
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_quickSlotSelectRcX = 423 + 64 * 9;
		_selecRcX = 417 + 64 * 9;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_quickSlotSelectRcX = 423 + 64 * 10;
		_selecRcX = 417 + 64 * 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_quickSlotSelectRcX = 423 + 64 * 11;
		_selecRcX = 417 + 64 * 11;
	}
}
