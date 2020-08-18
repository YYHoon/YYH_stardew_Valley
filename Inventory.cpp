#include "stdafx.h"
#include "Inventory.h"
#include "ToolItemManager.h"
#include "ToolItem.h"
#include "Player.h"
#include "Store.h"

HRESULT Inventory::init()
{
	_environment = new Environment;
	_environment->init();

	_test = false;

	//_inventory.isInvenOpen = false;					//�κ��丮 �ʱⰪ�� ��������

	_inventory.invenTabNum = 1;							//�κ��丮 ���� �⺻ ��ȣ
	_inventory.craftPageNum = 1;						//���� �ǿ��� ù��° ������

	_inventory.x = 417;
	_inventory.y = 230;

	_inventory.rc.left = 417;
	_inventory.rc.top = 230;

	_frameCount = 0;

	_trashCanFrameX = 0;
	_trashCanRC.left = 1260;
	_trashCanRC.top = 446;
	
//-----------------------QuickSlot-----------------------------------
	_quickSlot.image = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect.image = IMAGEMANAGER->findImage("QuickSlotSelect");
	
	_quickSlot.y = 747;
	_quickSlot.uY = 10;
	_quickSlotSelect.x = 423;
	_quickSlotSelect.y = 763;

	_quickSlotSelectYUP = 26;

	_environment->SetIsInventoryOpen(false);

	_toolList = _toolItemManager->GetToolItem();

	_toolInven.resize(13);							//��� �� �κ��丮 ĭ���� + 1 �ؼ� ������ ���� �������� ���

	for (int i = 0; i < _toolInven.size(); ++i)
	{
		_toolInven[i] = new Axe;
	}

	_quickSlotUp = false;

	_toolInven[0] = _toolList[0];
	_toolInven[1] = _toolList[1];
	_toolInven[2] = _toolList[2];
	_toolInven[3] = _toolList[3];
	_toolInven[4] = _toolList[4];
	_toolInven[5] = _toolList[5];
	_toolInven[6] = _toolList[6];
	_toolInven[7]->SetToolEnum(TOOLS::NONE);
	_toolInven[8]->SetToolEnum(TOOLS::NONE);
	_toolInven[9]->SetToolEnum(TOOLS::NONE);
	_toolInven[10]->SetToolEnum(TOOLS::NONE);
	_toolInven[11]->SetToolEnum(TOOLS::NONE);
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
		if (PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX < 3) _trashCanFrameX++;

		if (!PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX > 0) _trashCanFrameX--;
	}

	_inventory.rc.top = _inventory.y;
	
	if (_player->GetPlayercollision().bottom >= WINSIZEY - 100)
	{
		_quickSlotUp = true;
	}
	else  _quickSlotUp = false;
	

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_environment->GetIsInventoryOpen())
		{
			_environment->SetIsInventoryOpen(true);
			//cout << "true" << endl;
		}
		else
		{
			_environment->SetIsInventoryOpen(false);
			//cout << "false" << endl;
		}
	}

	if (!_environment->GetIsInventoryOpen()) _inventory.invenTabNum = 1;					//�κ��丮 �ݾ��� �� 1�� ������ ����

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_environment->GetIsInventoryOpen() &&
			PtInRect(&_inventoryCloseRC, _ptMouse)) _environment->SetIsInventoryOpen(false);	//�κ��丮���� [X]��ư�� ������ ��
		
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_invenTabRC[i], _ptMouse)) _inventory.invenTabNum = i + 1;				//�� ���� ������ ��
		}

		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))
			{
				// Ŭ������ ���� �ε��� �� ����
				_itemIndexNum = i;

				cout << i << endl;										//�� �κ��丮 ĭ�� ������ ��
			}
		}

		/////////////// <���� ������ �̵�>
		if (PtInRect(&_menuUpRC, _ptMouse)) _inventory.craftPageNum--;
		if (PtInRect(&_menuDownRC, _ptMouse)) _inventory.craftPageNum++;

		if (_inventory.craftPageNum <= 0) _inventory.craftPageNum = 1;
		if (_inventory.craftPageNum >= 3) _inventory.craftPageNum = 2;
		/////////////// </���� ������ �̵�>
		
		if (PtInRect(&_titleRC, _ptMouse)) SCENEMANAGER->changeScene("Title");							//[Ÿ��Ʋ �޴���] ������ ��
		if (PtInRect(&_closeRC, _ptMouse) && _inventory.invenTabNum == 4) PostQuitMessage(0);			//[���� ����] ������ ��
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))					//������ �ε��� ����
			{
				int temp = _toolInven.size() - 1;						//������� �ʴ� ����
				_toolInven[temp] = _toolInven[i];
				_toolInven[i] = _toolInven[_itemIndexNum];
				_toolInven[_itemIndexNum] = _toolInven[temp];

				cout << i << endl;										//�� �κ��丮 ĭ�� ������ ��
			}
		}
		if (PtInRect(&_trashCanRC, _ptMouse))							//�������뿡 ������
		{
			_toolInven[_itemIndexNum]->SetToolEnum(TOOLS::NONE);
			cout << "Throw away" << endl;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////// <Test>
	if (!_environment->GetIsInventoryOpen())
	{
		_inventory.rc = RectMake(_inventory.rc.left, _inventory.rc.top,
		_quickSlotSelect.image->getWidth(), _quickSlotSelect.image->getHeight());
		quickSlotMove();
		if (!_vInvenIndexRC.empty()) _vInvenIndexRC.clear();
	}
	else
	{
		_inventory.rc = RectMake(-100, -100, 0, 0);
		if (_vInvenIndexRC.empty() && _inventory.invenTabNum == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				_indexRC[i] = RectMake(_inventory.x + i * 64, _inventory.y, 64, 64);	//�� �κ��丮 ĭ�� ��Ʈ
				_vInvenIndexRC.push_back(_indexRC[i]);
			}
		}
		else if (_inventory.invenTabNum != 1)
		{
			if (!_vInvenIndexRC.empty()) _vInvenIndexRC.clear();
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////// </Test>
}

void Inventory::render()
{
	SetTextColor(getMemDC(), WHITE);
	char getsu[2000]; //������ �ټ� ǥ���

	HFONT font1, oldFont1;
	font1 = CreateFont(30, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll �̻�"));
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	if (_environment->GetIsInventoryOpen())
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);

		switch (_inventory.invenTabNum)
		{
			case 1:		//�κ��丮 ��
			{
				_vInvenDynamicRC.clear();

				IMAGEMANAGER->findImage("UI_Inventory_Trashcan")->frameRender(getMemDC(), 1257, 464, _trashCanFrameX, 0);
				_trashCanRC = RectMake(_trashCanRC.left, _trashCanRC.top, 90, 140);		//�������� ��Ʈ
				_vInvenDynamicRC.push_back(_trashCanRC);

				if (_environment->GetCluckValue() <= CLOCKTIMEHALF)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);
				}
				else if (_environment->GetCluckValue() > CLOCKTIMEHALF)
				{
					IMAGEMANAGER->findImage("UI_Inventory_Night")->render(getMemDC(), INVENIMAGECOOR);
				}
				
				
				for (int i = 0; i < _toolInven.size() - 1; ++i)
				{
					if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
					{
						_toolInven[i]->GetImageInven()->render(getMemDC(), 416 + (i * 64), 230);
					}
					//----������ �ټ� ���----------//
					if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
						_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
					{
						sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
						TextOut(getMemDC(), 453 + (i * 64), 275, getsu, strlen(getsu));
					}
				}

				//cout << "1" << endl;
			}
			break;
			case 2:		//���� ��
			{
				_vInvenDynamicRC.clear();

				if (_inventory.craftPageNum == 1)				//1�� ������
				{
					IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);
				}
				else if (_inventory.craftPageNum == 2)			//2�� ������
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
	
				_titleRC = RectMake(665, 334, 272, 96);							//�����ǿ��� [Ÿ��Ʋ �޴���] ��ư
				_closeRC = RectMake(699, 470, 204, 96);							//�����ǿ��� [���� ����] ��ư
	
				//cout << "4" << endl;
			}
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			_invenTabRC[i] = RectMake(424 + i * 64, 126, 64, 64);				//�κ��丮 �� ��Ʈ

			_vInvenStaticRC.push_back(_invenTabRC[i]);
		}

		_inventoryCloseRC = RectMake(1240, 102, 44, 44);						//�κ��丮 [X] ��ư ��Ʈ
		_vInvenStaticRC.push_back(_inventoryCloseRC);
	}
	else
	{
		_vInvenStaticRC.clear();
		_vInvenDynamicRC.clear();
		
		if (SCENEMANAGER->GetNowScene()=="SHOP" && _store->getStoreOpen())
		{
			for (int i = 0; i < _toolInven.size(); ++i)
			{
				if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_toolInven[i]->GetImageInven()->render(getMemDC(), 638 + (i * 64), 539);
				}
				//----������ �ټ� ���----------//
				if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
					_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
				{
					sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
					TextOut(getMemDC(), 675 + (i * 64), 583, getsu, strlen(getsu));
				}
			}
		}
		else
		{
			if (!_quickSlotUp)
			{
				_quickSlot.image->render(getMemDC(), 407, _quickSlot.y);
				_quickSlotSelect.image->render(getMemDC(), _quickSlotSelect.x, _quickSlotSelect.y);
				for (int i = 0; i < _toolInven.size(); ++i)
				{
					if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
					{
						_toolInven[i]->GetImageInven()->render(getMemDC(), 423 + (i * 64), 763);
					}
					//---------������ �ټ� ���----------//
					if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
						_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
					{
						sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
						TextOut(getMemDC(), 462 + (i * 64), 806, getsu, strlen(getsu));
					}
				}
			}
			else
			{
				_quickSlot.image->render(getMemDC(), 407, _quickSlot.uY);
				_quickSlotSelect.image->render(getMemDC(), _quickSlotSelect.x, _quickSlotSelectYUP);
				for (int i = 0; i < _toolInven.size(); ++i)
				{
					if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
					{
						_toolInven[i]->GetImageInven()->render(getMemDC(), 423 + (i * 64), _quickSlotSelectYUP);
					}
					//---------������ �ټ� ���----------//
					if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
						_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
					{
						sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
						TextOut(getMemDC(), 462 + (i * 64), 69, getsu, strlen(getsu));
					}
				}
			}		
		}
	}

	////////////////////////QuickSlot///////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////// <Debug_Rect>

	//for (int InvenTab = 0; InvenTab < 4; InvenTab++)
	//{
	//	Rectangle(getMemDC(), _invenTabRC[InvenTab]);
	//}
	//Rectangle(getMemDC(), _inventoryCloseRC);
	//for (int i = 0; i < _vInvenIndexRC.size(); i++)
	//{
	//	Rectangle(getMemDC(), _vInvenIndexRC[i]);
	//}
	//Rectangle(getMemDC(), _closeRC);
	//Rectangle(getMemDC(), _menuUpRC);
	//Rectangle(getMemDC(), _menuDownRC);
	//Rectangle(getMemDC(), _inventory.rc);
	//Rectangle(getMemDC(), _trashCanRC);

	SelectObject(getMemDC(), oldFont1);
	DeleteObject(oldFont1);

	/////////////////////////////////////////////////////////////////////////// </Debug_Rect>

}

void Inventory::quickSlotMove()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_quickSlotSelect.x = 423;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotSelect.x = 423 + 64;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotSelect.x = 423 + 64 * 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotSelect.x = 423 + 64 * 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotSelect.x = 423 + 64 * 4;
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_quickSlotSelect.x = 423 + 64 * 5;
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_quickSlotSelect.x = 423 + 64 * 6;
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_quickSlotSelect.x = 423 + 64 * 7;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_quickSlotSelect.x = 423 + 64 * 8;
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_quickSlotSelect.x = 423 + 64 * 9;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_quickSlotSelect.x = 423 + 64 * 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_quickSlotSelect.x = 423 + 64 * 11;
	}
}

void Inventory::PlayerLootItem(ToolItem* item)
{
	//for (int i = 0; i < 12; i++)
	//{
	//	if (_toolInven[i]->GetName() == item->GetName())
	//	{
	//		//if(_toolInven[i]->getnum()>10) contine;
	//		//_toolInven[i]->setnum(+1);
	//	}
	//	else
	//	{
	//		if (_toolInven[i]->GetToolEnum()==TOOLS::NONE)
	//		{
	//			_toolInven[i] = item;
	//			// _toolInven[i]->setnum(+1);
	//			break;
	//		}
	//	}
	//}
}

void Inventory::setPlayerBuyItme(ToolItem* buyItme)
{
	for (int i = 0; i < 12; i++)
	{
		if (_toolInven[0]->GetName() == buyItme->GetName())
		{
			if (_toolInven[0]->GetNumber() > 99) continue;
			_toolInven[0]->SetNumber(+1);
			break;
		}
		else if (_toolInven[1]->GetName() == buyItme->GetName())
		{
			if (_toolInven[1]->GetNumber() > 99) continue;
			_toolInven[1]->SetNumber(+1);
			break;
		}
		else if (_toolInven[2]->GetName() == buyItme->GetName())
		{
			if (_toolInven[2]->GetNumber() > 99) continue;
			_toolInven[2]->SetNumber(+1);
			break;
		}
		else if (_toolInven[3]->GetName() == buyItme->GetName())
		{
			if (_toolInven[3]->GetNumber() > 99) continue;
			_toolInven[3]->SetNumber(+1);
			break;
		}
		else if (_toolInven[4]->GetName() == buyItme->GetName())
		{
			if (_toolInven[4]->GetNumber() > 99) continue;
			_toolInven[4]->SetNumber(+1);
			break;
		}
		else if (_toolInven[5]->GetName() == buyItme->GetName())
		{
			if (_toolInven[5]->GetNumber() > 99) continue;
			_toolInven[5]->SetNumber(+1);
			break;
		}
		else if (_toolInven[6]->GetName() == buyItme->GetName())
		{
			if (_toolInven[6]->GetNumber() > 99) continue;
			_toolInven[6]->SetNumber(+1);
			break;
		}
		else if (_toolInven[7]->GetName() == buyItme->GetName())
		{
			if (_toolInven[7]->GetNumber() > 99) continue;
			_toolInven[7]->SetNumber(+1);
			break;
		}
		else if (_toolInven[8]->GetName() == buyItme->GetName())
		{
			if (_toolInven[8]->GetNumber() > 99) continue;
			_toolInven[8]->SetNumber(+1);
			break;
		}
		else if (_toolInven[9]->GetName() == buyItme->GetName())
		{
			if (_toolInven[9]->GetNumber() > 99) continue;
			_toolInven[9]->SetNumber(+1);
			break;
		}
		else if (_toolInven[10]->GetName() == buyItme->GetName())
		{
			if (_toolInven[10]->GetNumber() > 99) continue;
			_toolInven[10]->SetNumber(+1);
			break;
		}
		else if (_toolInven[11]->GetName() == buyItme->GetName())
		{
			if (_toolInven[11]->GetNumber() > 99) continue;
			_toolInven[11]->SetNumber(+1);
			break;
		}
		else
		{
			if (_toolInven[i]->GetToolEnum() == TOOLS::NONE)
			{
				_toolInven[i] = buyItme;
				_toolInven[i]->SetNumber(+1);
				break;
			}
		}
	}
}
