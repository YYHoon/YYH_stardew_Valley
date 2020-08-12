#include "stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init()
{
	_isInventoryOpen = false;								//�κ��丮 �ʱⰪ�� ��������
	_tabNum = 1;											//�κ��丮 ���� �⺻ ��ȣ
	_craftTabNum = 1;										//���� �ǿ��� ù��° ������

	_invenOpenX = 417;
	_invenOpenY = 230;

	_invenCloseUX = 423;
	_invenCloseUY;
	_invenCloseDX = 423;
	_invenCloseDY = 763;


//-----------------------QuickSlot-----------------------------------
	_quickSlot = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect = IMAGEMANAGER->findImage("QuickSlotSelect");

	_quickSlotY = 747;
	_quickSlotSelectRcX = 423;
	_quickSlotSelectRcY = 763;

//-----------------------�ι����������׽�Ʈ���̹���-------------------------
	_testImage = IMAGEMANAGER->findImage("������1");
	_testImage2 = IMAGEMANAGER->findImage("������2");


	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_isInventoryOpen) _isInventoryOpen = true;		//�κ��丮�� ������ ��
		else _isInventoryOpen = false;						//�κ��丮�� ������ ��
	}

	if (!_isInventoryOpen) _tabNum = 1;						//�κ��丮 �ݾ��� �� 1�� ������ ����

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (_viInvenStaticRC = _vInvenStaticRC.begin(); _viInvenStaticRC != _vInvenStaticRC.end(); ++_viInvenStaticRC)
		{
			if (PtInRect(&_inventoryCloseRC, _ptMouse)) _isInventoryOpen = false;		//�κ��丮���� [X]��ư�� ������ ��
			
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_invenTabRC[i], _ptMouse)) _tabNum = i + 1;				//�� ���� ������ ��
			}
		}

		for (_viInvenDynamicRC = _vInvenDynamicRC.begin(); _viInvenDynamicRC != _vInvenDynamicRC.end(); ++_viInvenDynamicRC)
		{
			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				if (PtInRect(&_indexRC[InventoryIndex], _ptMouse))
				{
					//cout << InventoryIndex + 1 << endl;									//�� �κ��丮 ĭ�� ������ ��
				}
			}

			/////////////// <���� ������ �̵�>
			if (PtInRect(&_menuUpRC, _ptMouse)) _craftTabNum--;
			if (PtInRect(&_menuDownRC, _ptMouse)) _craftTabNum++;

			if (_craftTabNum <= 0) _craftTabNum = 1;
			if (_craftTabNum >= 3) _craftTabNum = 2;
			/////////////// </���� ������ �̵�>
		}

		//if (PtInRect(&_TitleRC, _ptMouse) && _tabNum == 4) SCENEMANAGER->changeScene();	//[Ÿ��Ʋ �޴���] ������ ��
		if (PtInRect(&_closeRC, _ptMouse) && _tabNum == 4) PostQuitMessage(0);			//[���� ����] ������ ��
	}


	for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
	{
		_indexRC[InventoryIndex] = RectMake(_invenOpenX + InventoryIndex * 64, _invenOpenY, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
		_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
		_testImage->render(getMemDC(), _indexRC[0].left, _indexRC[0].top);
		_testImage2->render(getMemDC(), _indexRC[1].left, _indexRC[1].top);
	}

	if(!_isInventoryOpen) _quickSlotSelectRc = RectMake(_quickSlotSelectRcX, _quickSlotSelectRcY, _quickSlotSelect->getWidth(), _quickSlotSelect->getHeight());
	quickSlotMove();
}

void Inventory::render()
{
	if (_isInventoryOpen)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);

		switch (_tabNum)
		{
		case 1:		//�κ��丮 ��
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);

			for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
			{
				_indexRC[InventoryIndex] = RectMake(_invenOpenX + InventoryIndex *64 , _invenOpenY, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
				_vInvenIndexRC.push_back(_indexRC[InventoryIndex]);
				//Rectangle(getMemDC(), _vInvenIndexRC[InventoryIndex]);
				_testImage->render(getMemDC(), _indexRC[0].left, _indexRC[0].top);
				_testImage2->render(getMemDC(), _indexRC[1].left, _indexRC[1].top);
			}			
		}
		break;
		case 2:		//���� ��
		{
			_vInvenDynamicRC.clear();

			if (_craftTabNum == 1)							//1�� ������
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);
			}
			else if (_craftTabNum == 2)						//2�� ������
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
	if (!_isInventoryOpen)
	{
		_quickSlot->render(getMemDC(), 407, _quickSlotY);
		//Rectangle(getMemDC(), _vInvenIndexRC[0]);
		for (int InventoryIndex = 0; InventoryIndex < 12; InventoryIndex++)
		{
			_indexRC[InventoryIndex] = RectMake(_invenCloseDX + InventoryIndex * 64, _invenCloseDY, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
			_testImage->render(getMemDC(), _indexRC[0].left, _indexRC[0].top);
			_testImage2->render(getMemDC(), _indexRC[1].left, _indexRC[1].top);
			//Rectangle(getMemDC(), _indexRC[InventoryIndex]);
			if (IntersectRect(&temp, &_vInvenIndexRC[0], &_quickSlotSelectRc))
			{
				cout << "��" << endl;
			}
		}
		_quickSlotSelect->render(getMemDC(), _quickSlotSelectRc.left, _quickSlotSelectRc.top);	
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
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotSelectRcX = 423 + 64;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotSelectRcX = 423 + 64 * 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotSelectRcX = 423 + 64 * 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotSelectRcX = 423 + 64 * 4;
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_quickSlotSelectRcX = 423 + 64 * 5;
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_quickSlotSelectRcX = 423 + 64 * 6;
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_quickSlotSelectRcX = 423 + 64 * 7;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_quickSlotSelectRcX = 423 + 64 * 8;
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_quickSlotSelectRcX = 423 + 64 * 9;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_quickSlotSelectRcX = 423 + 64 * 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_quickSlotSelectRcX = 423 + 64 * 11;
	}
}
