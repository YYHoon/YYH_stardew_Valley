#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_environment = new Environment;
	_environment->init();

	_inventory.isInvenOpen = false;						//�κ��丮 �ʱⰪ�� ��������

	_inventory.invenTabNum = 1;							//�κ��丮 ���� �⺻ ��ȣ
	_inventory.craftPageNum = 1;						//���� �ǿ��� ù��° ������

	_inventory.x = 417;
	_inventory.y = 230;

	//_invenCloseUX = 423;
	//_invenCloseUY = 10;

	_quickSlotSelect.rc.left = 417;
	_quickSlotSelect.rc.top = 230;

	_frameCount = 0;

	_trashCanFrameX = 0;
	_trashCanRC.left = 1260;
	_trashCanRC.top = 446;

//-----------------------QuickSlot-----------------------------------
	_quickSlot.image = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect.image = IMAGEMANAGER->findImage("QuickSlotSelect");
	
	_quickSlot.y = 747;
	_quickSlotSelect.x = 423;
	_quickSlotSelect.y = 763;

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	_frameCount++;

	if (_frameCount % 4 == 0)
	{
		if (PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX < 3)
		{
			_trashCanFrameX++;
		}
		if (!PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX > 0)
		{
			_trashCanFrameX--;
		}
	}

	_environment->update();
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_inventory.isInvenOpen)
		{
			_inventory.isInvenOpen = true;					//�κ��丮�� ������ ��
			//cout << "true" << endl;
		}
		else
		{
			_inventory.isInvenOpen = false;					//�κ��丮�� ������ ��
			//cout << "false" << endl;
		}
	}

	if (!_inventory.isInvenOpen) _inventory.invenTabNum = 1;								//�κ��丮 �ݾ��� �� 1�� ������ ����

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (_viInvenStaticRC = _vInvenStaticRC.begin(); _viInvenStaticRC != _vInvenStaticRC.end(); ++_viInvenStaticRC)
		{
			if (PtInRect(&_inventoryCloseRC, _ptMouse)) _inventory.isInvenOpen = false;		//�κ��丮���� [X]��ư�� ������ ��
			
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_invenTabRC[i], _ptMouse)) _inventory.invenTabNum = i + 1;	//�� ���� ������ ��
			}
		}

		for (_viInvenDynamicRC = _vInvenDynamicRC.begin(); _viInvenDynamicRC != _vInvenDynamicRC.end(); ++_viInvenDynamicRC)
		{
			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				if (PtInRect(&_indexRC[InventoryIndex], _ptMouse))
				{
					cout << InventoryIndex + 1 << endl;										//�� �κ��丮 ĭ�� ������ ��
				}
			}

			/////////////// <���� ������ �̵�>
			if (PtInRect(&_menuUpRC, _ptMouse)) _inventory.craftPageNum--;
			if (PtInRect(&_menuDownRC, _ptMouse)) _inventory.craftPageNum++;

			if (_inventory.craftPageNum <= 0) _inventory.craftPageNum = 1;
			if (_inventory.craftPageNum >= 3) _inventory.craftPageNum = 2;
			/////////////// </���� ������ �̵�>
		}

		//if (PtInRect(&_TitleRC, _ptMouse) && _tabNum == 4) SCENEMANAGER->changeScene();				//[Ÿ��Ʋ �޴���] ������ ��
		if (PtInRect(&_closeRC, _ptMouse) && _inventory.invenTabNum == 4) PostQuitMessage(0);			//[���� ����] ������ ��
	}

	for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
	{
		_indexRC[InventoryIndex] = RectMake(_inventory.x + InventoryIndex * 64, _inventory.y, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
		_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
	}

	if (!_inventory.isInvenOpen)
	{
		_quickSlotSelect.rc = RectMake(_quickSlotSelect.rc.left, _quickSlotSelect.rc.top,
			_quickSlotSelect.image->getWidth(), _quickSlotSelect.image->getHeight());
		quickSlotMove();
	}
	else _quickSlotSelect.rc = RectMake(-100,-100,0,0);
}

void Inventory::render()
{
	if (_inventory.isInvenOpen)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);

		switch (_inventory.invenTabNum)
		{
			case 1:		//�κ��丮 ��
			{
				_vInvenDynamicRC.clear();

				IMAGEMANAGER->findImage("UI_Inventory_Trashcan")->frameRender(getMemDC(), 1257, 464, _trashCanFrameX, 0);
				_trashCanRC = RectMake(_trashCanRC.left, _trashCanRC.top, 90, 140);
				_vInvenDynamicRC.push_back(_trashCanRC);

				if (_environment->GetCluckValue() <= CLOCKTIMEHALF)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);
				}
				else if (_environment->GetCluckValue() > CLOCKTIMEHALF)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Night")->render(getMemDC(), INVENIMAGECOOR);
				}
	
				for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
				{
					_indexRC[InventoryIndex] = RectMake(_inventory.x + InventoryIndex * 64, _inventory.y, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
					_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
				}

				//cout << "1" << endl;
			}
			break;
			case 2:		//���� ��
			{
				_vInvenDynamicRC.clear();
		
				if (_inventory.craftPageNum == 1)							//1�� ������
				{
					IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);
				}
				else if (_inventory.craftPageNum == 2)						//2�� ������
				{
					IMAGEMANAGER->findImage("UI_Inventory_Craft_bot")->render(getMemDC(), INVENIMAGECOOR);
				}
	
				_menuUpRC = RectMake(1170, 233, 32, 35);		//���� �ǿ��� �� ȭ��ǥ
				_menuDownRC = RectMake(1170, 464, 32, 35);		//���� �ǿ��� �Ʒ� ȭ��ǥ
	
				_vInvenDynamicRC.push_back(_menuUpRC);
				_vInvenDynamicRC.push_back(_menuDownRC);
	
				//cout << "2" << endl;
			}
			break;
			case 3:		//Ű �˸� ��
			{
				_vInvenDynamicRC.clear();
	
				IMAGEMANAGER->findImage("UI_Inventory_KeyInfo")->render(getMemDC(), INVENIMAGECOOR);
	
				//cout << "3" << endl;
			}
			break;
			case 4:		//���� ������
			{
				_vInvenDynamicRC.clear();
	
				IMAGEMANAGER->findImage("UI_Inventory_Game_Close")->render(getMemDC(), INVENIMAGECOOR);
	
				_titleRC = RectMake(665, 334, 272, 96);										//�����ǿ��� [Ÿ��Ʋ �޴���] ��ư
				_closeRC = RectMake(699, 470, 204, 96);										//�����ǿ��� [���� ����] ��ư
	
				//cout << "4" << endl;
			}
			break;
		}

		for (int InvenTab = 0; InvenTab < 4; InvenTab++)
		{
			_invenTabRC[InvenTab] = RectMake(424 + InvenTab * 64, 126, 64, 64);				//�κ��丮 �� ��Ʈ

			_vInvenStaticRC.push_back(_invenTabRC[InvenTab]);
		}

		_inventoryCloseRC = RectMake(1240, 102, 44, 44);
		_vInvenStaticRC.push_back(_inventoryCloseRC);										//�κ��丮 [X] ��ư
	}
	else
	{
		_vInvenStaticRC.clear();
		_vInvenDynamicRC.clear();
	}

	////////////////////////QuickSlot///////////////////////////////////////////
	RECT temp;
	if (!_inventory.isInvenOpen)
	{
		_quickSlot.image->render(getMemDC(), 407, _quickSlot.y);
		for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
		{
			_indexRC[InventoryIndex] = RectMake(423 + InventoryIndex * 64, 763, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
			if (IntersectRect(&temp, &_vInvenIndexRC[0], &_quickSlotSelect.rc))
			{
				//////////////////////////////////////////////////////////////////////////////���⿡ ������ �׽�Ʈ�ϱ�
			}
		}

		_quickSlotSelect.image->render(getMemDC(), _quickSlotSelect.x, _quickSlotSelect.y);
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
	//	Rectangle(getMemDC(), _indexRC[InventoryIndex]);
	//}
	//
	//Rectangle(getMemDC(), _closeRC);
	//
	//Rectangle(getMemDC(), _menuUpRC);
	//Rectangle(getMemDC(), _menuDownRC);
	//Rectangle(getMemDC(), _quickSlotSelect.rc);

	/////////////////////////////////////////////////////////////////////////// </Debug_Rect>
}

void Inventory::quickSlotMove()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_quickSlotSelect.x = 423;
		_quickSlotSelect.rc.left = 417;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotSelect.x = 423 + 64;
		_quickSlotSelect.rc.left = 417 + 64;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotSelect.x = 423 + 64 * 2;
		_quickSlotSelect.rc.left = 417 + 64 * 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotSelect.x = 423 + 64 * 3;
		_quickSlotSelect.rc.left = 417 + 64 * 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotSelect.x = 423 + 64 * 4;
		_quickSlotSelect.rc.left = 417 + 64 * 4;
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_quickSlotSelect.x = 423 + 64 * 5;
		_quickSlotSelect.rc.left = 417 + 64 * 5;
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_quickSlotSelect.x = 423 + 64 * 6;
		_quickSlotSelect.rc.left = 417 + 64 * 6;
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_quickSlotSelect.x = 423 + 64 * 7;
		_quickSlotSelect.rc.left = 417 + 64 * 7;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_quickSlotSelect.x = 423 + 64 * 8;
		_quickSlotSelect.rc.left = 417 + 64 * 8;
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_quickSlotSelect.x = 423 + 64 * 9;
		_quickSlotSelect.rc.left = 417 + 64 * 9;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_quickSlotSelect.x = 423 + 64 * 10;
		_quickSlotSelect.rc.left = 417 + 64 * 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_quickSlotSelect.x = 423 + 64 * 11;
		_quickSlotSelect.rc.left = 417 + 64 * 11;
	}
}
