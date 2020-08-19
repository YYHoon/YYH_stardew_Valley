#include "stdafx.h"
#include "Inventory.h"
#include "ToolItemManager.h"
#include "ToolItem.h"
#include "Player.h"
#include "Store.h"

HRESULT Inventory::init()
{
	_toolItemManager = new ToolItemManager;
	_toolItemManager->Init();

	_Dtset = new Dialog;
	_Dtset->init();

	_inventory.isInvenOpen = false;

	_inventory.invenTabNum = 1;							//인벤토리 탭의 기본 번호
	_inventory.craftPageNum = 1;						//제작 탭에서 첫번째 페이지

	_inventory.x = 417;
	_inventory.y = 230;

	_inventory.rc.left = 417;
	_inventory.rc.top = 230;

	_frameCount = 0;

	_trashCanFrameX = 0;

	_index = 0;

	//-----------------------QuickSlot-----------------------------------
	_quickSlot.image = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect.image = IMAGEMANAGER->findImage("QuickSlotSelect");

	_quickSlot.y = 747;
	_quickSlot.uY = 10;
	_quickSlotSelect.x = 423;
	_quickSlotSelect.y = 763;

	_quickSlotSelectYUP = 26;

	_toolList = _toolItemManager->GetToolItem();

	_toolInven.resize(13);							//사용 할 인벤토리 칸에서 + 1 해서 아이템 스왑 전용으로 사용

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
	_toolInven[7] ->SetToolEnum(TOOLS::NONE);
	_toolInven[8] ->SetToolEnum(TOOLS::NONE);
	_toolInven[9] ->SetToolEnum(TOOLS::NONE);
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

	_Dtset->update(_toolInven[1]->GetName());
	if (KEYMANAGER->isOnceKeyDown(VK_F11)) _Dtset->setDialogClear(true);
	if (KEYMANAGER->isOnceKeyDown(VK_F12)) _Dtset->setDialogClear(false);

	if (_player->GetPlayercollision().bottom >= WINSIZEY - 100)
	{
		_quickSlotUp = true;
	}
	else  _quickSlotUp = false;

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_inventory.isInvenOpen)
		{
			ENVIRONMENT->SetIsInventoryOpen(true);
			_inventory.isInvenOpen = true;
			//cout << "true" << endl;
		}
		else
		{
			ENVIRONMENT->SetIsInventoryOpen(false);
			_inventory.isInvenOpen = false;
			//cout << "false" << endl;
		}
	}

	if (!_inventory.isInvenOpen) _inventory.invenTabNum = 1;								//인벤토리 닫았을 때 1번 탭으로 리셋

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_inventory.isInvenOpen &&
			PtInRect(&_inventoryCloseRC, _ptMouse))
		{
			_inventory.isInvenOpen = false;														//인벤토리에서 [X]버튼을 눌렀을 때
			ENVIRONMENT->SetIsInventoryOpen(false);
		}

		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_invenTabRC[i], _ptMouse)) _inventory.invenTabNum = i + 1;			//각 탭을 눌렀을 때
		}

		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))
			{
				// 클릭했을 때의 인덱스 값 저장
				_itemIndexNum = i;
				//각 인벤토리 칸을 눌렀을 때
				//cout << i << endl;
			}
		}

		/////////////// <제작 페이지 이동>
		if (PtInRect(&_menuUpRC, _ptMouse)) _inventory.craftPageNum--;
		if (PtInRect(&_menuDownRC, _ptMouse)) _inventory.craftPageNum++;

		if (_inventory.craftPageNum <= 0) _inventory.craftPageNum = 1;
		if (_inventory.craftPageNum >= 3) _inventory.craftPageNum = 2;
		/////////////// </제작 페이지 이동>

		if (PtInRect(&_titleRC, _ptMouse) && _inventory.invenTabNum == 4) SCENEMANAGER->changeScene("Title");	//[타이틀 메뉴로] 눌렀을 때
		if (PtInRect(&_closeRC, _ptMouse) && _inventory.invenTabNum == 4) PostQuitMessage(0);					//[게임 종료] 눌렀을 때
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))					//아이템 인덱스 스왑
			{
				int temp = _toolInven.size() - 1;						//사용하지 않는 벡터
				_toolInven[temp] = _toolInven[i];
				_toolInven[i] = _toolInven[_itemIndexNum];
				_toolInven[_itemIndexNum] = _toolInven[temp];
				_toolInven[temp] = nullptr;

				//각 인벤토리 칸에서 땠을 때
				//cout << i << endl;										
			}
		}

		if (PtInRect(&_trashCanRC, _ptMouse))							//쓰레기통에 버리기
		{
			_toolInven[_itemIndexNum]->SetToolEnum(TOOLS::NONE);
		}
	}

	if (!_inventory.isInvenOpen)
	{

		_inventory.rc = RectMake(_inventory.rc.left, _inventory.rc.top,
			_quickSlotSelect.image->getWidth(), _quickSlotSelect.image->getHeight());
		quickSlotMove();

		if (!_vInvenIndexRC.empty()) _vInvenIndexRC.clear();
		if (!_vInvenStaticRC.empty()) _vInvenStaticRC.clear();
		if (!_vInvenDynamicRC.empty()) _vInvenDynamicRC.clear();
	}
	else
	{
		_inventory.rc = RectMake(-100, -100, 0, 0);
		_inventoryCloseRC = RectMake(1240, 102, 44, 44);								//인벤토리 [X] 버튼 렉트

		_vInvenStaticRC.push_back(_inventoryCloseRC);

		if (_vInvenIndexRC.empty() && _inventory.invenTabNum == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				_indexRC[i] = RectMake(_inventory.x + i * 64, _inventory.y, 64, 64);	//각 인벤토리 칸의 렉트
				_vInvenIndexRC.push_back(_indexRC[i]);
			}
		}
		else if (_inventory.invenTabNum != 1)
		{
			if (!_vInvenIndexRC.empty()) _vInvenIndexRC.clear();
		}

		for (int i = 0; i < 4; i++)
		{
			_invenTabRC[i] = RectMake(424 + i * 64, 126, 64, 64);						//인벤토리 탭 렉트

			_vInvenStaticRC.push_back(_invenTabRC[i]);
		}
	}

	///////////////////////////// <SortTest>
	//if (_inventory.isInvenOpen &&
	//	_inventory.invenTabNum == 1 &&
	//	KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	//{
	//	for (int i = 0; i < _toolInven.size() - 1; i++)
	//	{
	//		MergeSort(_toolInven, 0, 11);
	//
	//		/// <summary>
	//		cout << _toolInven[i] << endl;
	//		/// </summary>
	//		
	//		_toolInven[i] = _toolList[_test[i]];
	//	}
	//}
	///////////////////////////// </SortTest>

}

void Inventory::render()
{
	SetTextColor(getMemDC(), WHITE);
	char getsu[2000]; //아이템 개수 표기용

	HFONT font1, oldFont1;
	font1 = CreateFont(30, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	if (_inventory.isInvenOpen)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);

		switch (_inventory.invenTabNum)
		{
		case 1:		//인벤토리 탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_Trashcan")->frameRender(getMemDC(), 1257, 464, _trashCanFrameX, 0);
			_trashCanRC = RectMake(1260, 446, 90, 140);		//쓰레기통 렉트
			_vInvenDynamicRC.push_back(_trashCanRC);

			if (ENVIRONMENT->GetCluckValue() <= CLOCKTIMEHALF)
			{
				IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);
			}
			else if (ENVIRONMENT->GetCluckValue() > CLOCKTIMEHALF)
			{
				IMAGEMANAGER->findImage("UI_Inventory_Night")->render(getMemDC(), INVENIMAGECOOR);
			}

			for (int i = 0; i < _toolInven.size() - 1; ++i)
			{
				if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_toolInven[i]->GetImageInven()->render(getMemDC(), 416 + (i * 64), 230);
				}
				//----아이템 개수 출력----------//
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
		case 2:		//제작 탭
		{
			_vInvenDynamicRC.clear();

			if (_inventory.craftPageNum == 1)				//1번 페이지
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);
			}
			else if (_inventory.craftPageNum == 2)			//2번 페이지
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

			_titleRC = RectMake(665, 334, 272, 96);							//종료탭에서 [타이틀 메뉴로] 버튼
			_closeRC = RectMake(699, 470, 204, 96);							//종료탭에서 [게임 종료] 버튼

			//cout << "4" << endl;
		}
		break;
		}
	}
	else
	{
		if (SCENEMANAGER->GetNowScene() == "SHOP" && _store->getStoreOpen())
		{
			for (int i = 0; i < _toolInven.size() - 1; ++i)
			{
				if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_toolInven[i]->GetImageInven()->render(getMemDC(), 638 + (i * 64), 539);
				}
				//----아이템 개수 출력----------//
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
				for (int i = 0; i < _toolInven.size() - 1; ++i)
				{
					if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
					{
						_toolInven[i]->GetImageInven()->render(getMemDC(), 423 + (i * 64), 763);
					}
					//---------아이템 개수 출력----------//
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
				for (int i = 0; i < _toolInven.size() - 1; ++i)
				{
					if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
					{
						_toolInven[i]->GetImageInven()->render(getMemDC(), 423 + (i * 64), _quickSlotSelectYUP);
					}
					//---------아이템 개수 출력----------//
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

	_Dtset->render();
	SelectObject(getMemDC(), oldFont1);
	DeleteObject(oldFont1);
	

	/////////////////////////////////////////////////////////////////////////// <Debug_Rect>
   //
	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(getMemDC(), _invenTabRC[i]);
	//}
	//Rectangle(getMemDC(), _inventoryCloseRC);
	//for (int i = 0; i < _vInvenIndexRC.size(); i++)
	//{
	//	Rectangle(getMemDC(), _vInvenIndexRC[i]);
	//}
	//Rectangle(getMemDC(), _titleRC);
	//Rectangle(getMemDC(), _closeRC);
	//Rectangle(getMemDC(), _menuUpRC);
	//Rectangle(getMemDC(), _menuDownRC);
	//Rectangle(getMemDC(), _trashCanRC);
   //
	/////////////////////////////////////////////////////////////////////////// </Debug_Rect>

}

void Inventory::quickSlotMove()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_quickSlotSelect.x = 423;
		_index = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_quickSlotSelect.x = 423 + 64;
		_index = 1;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_quickSlotSelect.x = 423 + 64 * 2;
		_index = 2;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_quickSlotSelect.x = 423 + 64 * 3;
		_index = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_quickSlotSelect.x = 423 + 64 * 4;
		_index = 4;
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_quickSlotSelect.x = 423 + 64 * 5;
		_index = 5;
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_quickSlotSelect.x = 423 + 64 * 6;
		_index = 6;
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_quickSlotSelect.x = 423 + 64 * 7;
		_index = 7;
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_quickSlotSelect.x = 423 + 64 * 8;
		_index = 8;
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_quickSlotSelect.x = 423 + 64 * 9;
		_index = 9;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_quickSlotSelect.x = 423 + 64 * 10;
		_index = 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_quickSlotSelect.x = 423 + 64 * 11;
		_index = 11;
	}
}

//void Inventory::Merge(vector<ToolItem*> &vIndex, int left, int mid, int right)
//{
//	int i, j, k, l;
//	i = left;
//	j = mid + 1;
//	k = left;
//
//	while (i <= mid && j <= right)
//	{
//		if (vIndex[i] <= vIndex[j]) _sorted[k++] = vIndex[i++];
//		else _sorted[k++] = vIndex[j++];
//	}
//
//	if (i > mid)
//	{
//		for (l = j; l <= right; l++)
//		{
//			_sorted[k++] = vIndex[l];
//		}
//	}
//	else
//	{
//		for (l = i; l <= mid; l++)
//		{
//			_sorted[k++] = vIndex[l];
//		}
//	}
//
//	for (l = left; l <= right; l++)
//	{
//		vIndex[l] = _sorted[l];
//	}
//}
//
//void Inventory::MergeSort(vector<ToolItem*> &vIndex, int left, int right)
//{
//	int mid;
//
//	if (left < right)
//	{
//		mid = (left + right) / 2;
//		MergeSort(vIndex, left, mid);
//		MergeSort(vIndex, mid + 1, right);
//		Merge(vIndex, left, mid, right);
//	}
//}

void Inventory::PlayerLootItem(ToolItem* lootItme)
{
	//	for (int i = 0; i < 12; i++)
	//	{
	//		if (_toolInven[i]->GetName() == lootItme->GetName())
	//		{
	//			if (_toolInven[i]->GetNumber() > 99) continue;
	//			_toolInven[i]->SetNumber(+1);
	//			break;
	//		}
	//		else
	//		{
	//			if (_toolInven[i]->GetToolEnum() == TOOLS::NONE)
	//			{
	//				_toolInven[i] = lootItme;
	//				_toolInven[i]->SetNumber(+1);
	//				break;
	//			}
	//		}
	//	}
}

void Inventory::setPlayerBuyItme(ToolItem* buyItme)
{
	for (int i = 0; i < 12; i++)
	{
		if (_toolInven[i]->GetName() == buyItme->GetName())
		{
			if (_toolInven[i]->GetNumber() > 99) continue;
			_toolInven[i]->SetNumber(+1);
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