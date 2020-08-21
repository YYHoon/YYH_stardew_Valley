#include "stdafx.h"
#include "Inventory.h"
#include "Crafting.h"
#include "ToolItemManager.h"
#include "ToolItem.h"
#include "Player.h"
#include "Store.h"

HRESULT Inventory::init()
{
	_toolItemManager = new ToolItemManager;
	_toolItemManager->Init();

	_Dialog = new Dialog;
	_Dialog->init();

	_crafting = new Crafting;
	_crafting->init();

	_inventory.isInvenOpen = false;

	_inventory.invenTabNum = 1;							//인벤토리 탭의 기본 번호
	_inventory.craftPageNum = 1;						//제작 탭에서 첫번째 페이지

	_inventory.x = 417;
	_inventory.y = 230;
	_inventory.craftY = 546;

	_inventory.rc.left = 417;
	_inventory.rc.top = 230;

	_frameCount = 0;

	_trashCanFrameX = 0;

	_itemIndexNum = 11;

	_index = _index1 = _index2 = 0;

	//-----------------------QuickSlot-----------------------------------
	_quickSlot.image = IMAGEMANAGER->findImage("QuickSlot");
	_quickSlotSelect.image = IMAGEMANAGER->findImage("QuickSlotSelect");

	_quickSlot.y = 747;
	_quickSlot.uY = 10;
	_quickSlotSelect.x = 423;
	_quickSlotSelect.y = 763;

	_quickSlotSelectYUP = 26;

	_toolList = _toolItemManager->GetToolItem();

	_toolInven.resize(12);							//사용 할 인벤토리 칸에서 + 1 해서 아이템 스왑 전용으로 사용
	_toolLoad.resize(12);
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
	_toolInven[7] = _toolList[15];
	_toolInven[7]->SetNumber(10);
	_toolInven[8]->SetToolEnum(TOOLS::NONE);
	_toolInven[9]->SetToolEnum(TOOLS::NONE);
	_toolInven[9]->SetToolEnum(TOOLS::NONE);
	_toolInven[10]->SetToolEnum(TOOLS::NONE);
	_toolInven[11]->SetToolEnum(TOOLS::NONE);
	//----------------------
	
	_tGetItem.ItemWindow = IMAGEMANAGER->findImage("GetItem");
	_tGetItem.ItemWindowRc = RectMake(-100, 700, _tGetItem.ItemWindow->getWidth(), _tGetItem.ItemWindow->getHeight());
	_tGetItem.Seetime = 0;
	_tGetItem.isGet = false;
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	//////////////////////////////////////////////////////////////////// <Debud>
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		_toolInven[8] = _toolList[10];
		_toolInven[8]->SetNumber(1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		_toolInven[9] = _toolList[8];
		_toolInven[9]->SetNumber(1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		_toolInven[7] = _toolList[9];
		_toolInven[7]->SetNumber(1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		_toolInven[6] = _toolList[7];
		_toolInven[6]->SetNumber(1);
	}
	//////////////////////////////////////////////////////////////////// </Debud>
	_frameCount++;

	if (_frameCount % 4 == 0)
	{
		if (PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX < 3) _trashCanFrameX++;

		if (!PtInRect(&_trashCanRC, _ptMouse) && _trashCanFrameX > 0) _trashCanFrameX--;
	}

	_inventory.rc.top = _inventory.y;

	if (_player->GetPlayercollision().bottom - CAMERAMANAGER->getT() >= WINSIZEY - 100)
	{
		_quickSlotUp = true;
	}
	else  _quickSlotUp = false;

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (!_inventory.isInvenOpen)
		{
			SOUNDMANAGER->play("Menu_Open", 0.8f);
			ENVIRONMENT->SetIsInventoryOpen(true);
			_inventory.isInvenOpen = true;
		}
		else
		{
			SOUNDMANAGER->play("Menu_Close", 0.8f);
			ENVIRONMENT->SetIsInventoryOpen(false);
			_inventory.isInvenOpen = false;
		}
	}

	if (!_inventory.isInvenOpen) _inventory.invenTabNum = 1;									//인벤토리 닫았을 때 1번 탭으로 리셋

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
			_invenTabRC[i] = RectMake(424 + i * 64, 126, 64, 64);								//인벤토리 탭 렉트

			_vInvenStaticRC.push_back(_invenTabRC[i]);

			if (PtInRect(&_invenTabRC[i], _ptMouse)) _inventory.invenTabNum = i + 1;			//각 탭을 눌렀을 때
		}

		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))
			{
				if (_toolInven[i]->GetToolEnum() != TOOLS::NONE)	//아이템이 있는 칸을 클릭했을 때의 인덱스 값 저장
				{
					_itemIndexNum = i;
				}
			}
		}
		/////////////////////////////////////////////////////////////////// <CraftPage>
		if (_inventory.invenTabNum == 2)
		{
			_crafting->SetRawFishIsPossible(false);
			_crafting->SetGrilledFishIsPossible(false);

			_craftingRC[0] = RectMake(408, 230, 64, 64);
			_craftingRC[1] = RectMake(508, 230, 64, 64);
			_craftingRC[2] = RectMake(608, 230, 64, 64);

			for (int i = 0; i < _toolInven.size(); ++i)				//생선 구이 제작
			{
				for (int j = 0; j < _toolInven.size(); ++j)
				{
					if ((_toolInven[i]->GetName() == "NormalFish" && _toolInven[i]->GetNumber() >= 1) &&
						(_toolInven[j]->GetName() == "Potato" && _toolInven[j]->GetNumber() >= 1))
					{
						_crafting->SetGrilledFishIsPossible(true);

						if (PtInRect(&_craftingRC[0], _ptMouse))
						{
							if (_toolInven[i]->GetNumber() >= 1 && _toolInven[j]->GetNumber() >= 1)
							{
								_toolInven[i]->SetNumber(-1);
								_toolInven[j]->SetNumber(-1);

								if (_toolInven[i]->GetNumber() <= 0)
								{
									_crafting->SetGrilledFishIsPossible(false);
									_toolInven[i] = new ToolItem;
									_toolInven[i]->SetToolEnum(TOOLS::NONE);
								}
								if (_toolInven[j]->GetNumber() <= 0)
								{
									_crafting->SetGrilledFishIsPossible(false);
									_toolInven[j] = new ToolItem;
									_toolInven[j]->SetToolEnum(TOOLS::NONE);
								}
							}
							cout << "생선 구이" << endl;
							PlayerLootItem("GrilledFish");
						}
					}
				}
			}

			for (int i = 0; i < _toolInven.size(); ++i)				//생선 회 제작
			{
				if (_toolInven[i]->GetName() == "NormalFish" && _toolInven[i]->GetNumber() >= 1)
				{
					_crafting->SetRawFishIsPossible(true);

					if (PtInRect(&_craftingRC[1], _ptMouse))
					{
						if (_toolInven[i]->GetNumber() >= 1)
						{
							_toolInven[i]->SetNumber(-1);

							if (_toolInven[i]->GetNumber() <= 0)
							{
								_crafting->SetRawFishIsPossible(false);
								_toolInven[i] = new ToolItem;
								_toolInven[i]->SetToolEnum(TOOLS::NONE);
							}
						}
						cout << "생선 회" << endl;
						PlayerLootItem("RawFish");
					}
				}
			}

			for (int i = 0; i < _toolInven.size(); ++i)				//샐러드 제작
			{
				for (int j = 0; j < _toolInven.size(); ++j)
				{
					if ((_toolInven[i]->GetName() == "Pasnip" && _toolInven[i]->GetNumber() >= 1) &&
						(_toolInven[j]->GetName() == "Kale" && _toolInven[j]->GetNumber() >= 1))
					{
						_crafting->SetSaladIsPossible(true);

						if (PtInRect(&_craftingRC[2], _ptMouse))
						{
							if (_toolInven[i]->GetNumber() >= 1 && _toolInven[j]->GetNumber() >= 1)
							{
								_toolInven[i]->SetNumber(-1);
								_toolInven[j]->SetNumber(-1);

								if (_toolInven[i]->GetNumber() <= 0)
								{
									_crafting->SetSaladIsPossible(false);
									_toolInven[i] = new ToolItem;
									_toolInven[i]->SetToolEnum(TOOLS::NONE);
								}
								if (_toolInven[j]->GetNumber() <= 0)
								{
									_crafting->SetSaladIsPossible(false);
									_toolInven[j] = new ToolItem;
									_toolInven[j]->SetToolEnum(TOOLS::NONE);
								}
							}
							cout << "샐러드" << endl;
							PlayerLootItem("Salad");
						}
					}
				}
			}
		}
	

		if (PtInRect(&_menuUpRC, _ptMouse)) _inventory.craftPageNum--;
		if (PtInRect(&_menuDownRC, _ptMouse)) _inventory.craftPageNum++;

		if (_inventory.craftPageNum <= 0) _inventory.craftPageNum = 1;
		if (_inventory.craftPageNum >= 3) _inventory.craftPageNum = 2;
		/////////////////////////////////////////////////////////////////// </CraftPage>

		if (PtInRect(&_titleRC, _ptMouse) && _inventory.invenTabNum == 4) SCENEMANAGER->changeScene("Title");	//[타이틀 메뉴로] 눌렀을 때
		if (PtInRect(&_closeRC, _ptMouse) && _inventory.invenTabNum == 4) PostQuitMessage(0);					//[게임 종료] 눌렀을 때

		/////////////////////////////////////////////////////////////////// <Sort>
		if (PtInRect(&_sortRC, _ptMouse) && _inventory.invenTabNum == 1)
		{
			for (int i = 0; i < _toolInven.size(); i++)
			{
				MergeSort(_toolInven, 0, 11);
			}
		}
		/////////////////////////////////////////////////////////////////// </Sort>
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < _vInvenIndexRC.size(); ++i)
		{
			if (PtInRect(&_vInvenIndexRC[i], _ptMouse))					//아이템 인덱스 스왑
			{
				ToolItem* temp = new ToolItem;
				temp = _toolInven[i];
				_toolInven[i] = _toolInven[_itemIndexNum];
				_toolInven[_itemIndexNum] = temp;
			}
		}

		if (PtInRect(&_trashCanRC, _ptMouse))							//쓰레기통에 버리기 (1번 탭에서만 할거에요)
		{
			if (_inventory.invenTabNum == 1)
			{
				_toolInven[_itemIndexNum]->SetNumber(-_toolInven[_itemIndexNum]->GetNumber());
				_toolInven[_itemIndexNum] = new ToolItem;
			}
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
		_inventoryCloseRC = RectMake(1240, 102, 44, 44);										//인벤토리 [X] 버튼 렉트

		_vInvenStaticRC.push_back(_inventoryCloseRC);

		if (_vInvenIndexRC.empty())
		{
			if (_inventory.invenTabNum == 1)													//인벤토리 탭
			{
				for (int i = 0; i < 12; i++)
				{
					_indexRC[i] = RectMake(_inventory.x + i * 64, _inventory.y, 64, 64);		//각 인벤토리 칸의 렉트
					_vInvenIndexRC.push_back(_indexRC[i]);
				}
			}
		}
		else
		{
			if (_inventory.invenTabNum != 1) _vInvenIndexRC.clear();
		}

	}
	//////////////////////////////////////////////////////////////////////// <DayResetTest>
	if (KEYMANAGER->isOnceKeyDown(VK_F7)) ENVIRONMENT->SetIsDayReset(true);
	//////////////////////////////////////////////////////////////////////// </DayResetTest>
	if (_inventory.invenTabNum == 1)
	{
		for (int i = 0; i < 12; ++i)
		{
			_dialogRc[i] = RectMake(425 + (i * 64), 236, 45, 45);
			if (PtInRect(&_dialogRc[i], _ptMouse) && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
			{
				_Dialog->update(_toolInven[i]->GetName());
			}
		}
	}

	if (_inventory.invenTabNum == 2)
	{
		for (int i = 0; i < 12; ++i)
		{
			_dialogRc[i] = RectMake(425 + (i * 64), 550, 45, 45);
			if (PtInRect(&_dialogRc[i], _ptMouse) && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
			{
				_Dialog->update(_toolInven[i]->GetName());
			}
		}
	}

	_Dialog->setDialogClear(false);
}

void Inventory::render()
{
	SetTextColor(getMemDC(), BLACK);
	char getsu[30]; //아이템 개수 표기용

	HFONT font1, oldFont1;
	font1 = CreateFont(30, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	oldFont1 = (HFONT)SelectObject(getMemDC(), font1);

	char pGold[10];
	sprintf_s(pGold, "%d", _player->GetMoney());
	
	if (_inventory.isInvenOpen)
	{
		IMAGEMANAGER->findImage("Inventory_BG")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("Inventory_Close")->render(getMemDC(), 1240, 102);
		TextOut(getMemDC(), 1370, 203, pGold, strlen(pGold));
		switch (_inventory.invenTabNum)
		{
		case 1:		//인벤토리 탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_Trashcan")->frameRender(getMemDC(), 1257, 464, _trashCanFrameX, 0);
			IMAGEMANAGER->findImage("UI_Inventory_Sort")->render(getMemDC(), 1240, 280);
			_trashCanRC = RectMake(1260, 446, 90, 140);		//쓰레기통 렉트
			_sortRC = RectMake(1240, 280, 64, 64);
			_vInvenDynamicRC.push_back(_trashCanRC);
			_vInvenDynamicRC.push_back(_sortRC);
			
			//아이템 정보보기//
			for (int i = 0; i < _vInvenIndexRC.size(); ++i)
			{
				if (PtInRect(&_dialogRc[i], _ptMouse) && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					 _Dialog->setDialogClear(true);	
					 break;
				}
				else
				{
					_Dialog->setDialogClear(false);
				}
			}

			if (ENVIRONMENT->GetCluckValue() <= CLOCKTIMEHALF)
			{
				IMAGEMANAGER->findImage("UI_Inventory_Day")->render(getMemDC(), INVENIMAGECOOR);
			}
			else if (ENVIRONMENT->GetCluckValue() > CLOCKTIMEHALF)
			{
				IMAGEMANAGER->findImage("UI_Inventory_Night")->render(getMemDC(), INVENIMAGECOOR);
			}

			for (int i = 0; i < _toolInven.size(); ++i)
			{
				if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_toolInven[i]->GetImageInven()->render(getMemDC(), 416 + (i * 64), 230);
				}
				//----아이템 개수 출력----------//
				if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
					_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
				{
					SetTextColor(getMemDC(), WHITE);
					sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
					TextOut(getMemDC(), 453 + (i * 64), 275, getsu, strlen(getsu));
				}
			}

			HFONT font2, oldFont2;
			font2 = CreateFont(50, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
				PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
			oldFont2 = (HFONT)SelectObject(getMemDC(), font2);

			SetTextColor(getMemDC(), BLACK);
			TextOut(getMemDC(), 950, 570, pGold, strlen(pGold));

			SelectObject(getMemDC(), oldFont2);
			DeleteObject(font2);
		}
		break;
		case 2:		//제작 탭
		{
			_vInvenDynamicRC.clear();

			if (_inventory.craftPageNum == 1)				//1번 페이지
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_top")->render(getMemDC(), INVENIMAGECOOR);

				_crafting->render();
			}
			else if (_inventory.craftPageNum == 2)			//2번 페이지
			{
				IMAGEMANAGER->findImage("UI_Inventory_Craft_bot")->render(getMemDC(), INVENIMAGECOOR);
			}

			_menuUpRC = RectMake(1170, 233, 32, 35);		//제작 탭에서 위 화살표
			_menuDownRC = RectMake(1170, 464, 32, 35);		//제작 탭에서 아래 화살표

			_vInvenDynamicRC.push_back(_menuUpRC);
			_vInvenDynamicRC.push_back(_menuDownRC);

			for (int i = 0; i < _toolInven.size(); ++i)
			{
				if (_toolInven[i] != nullptr && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_toolInven[i]->GetImageInven()->render(getMemDC(), 416 + (i * 64), 545);
				}
				//----아이템 개수 출력----------//
				if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM || _toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
					_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
				{
					sprintf_s(getsu, "%d", _toolInven[i]->GetNumber());
					TextOut(getMemDC(), 453 + (i * 64), 590, getsu, strlen(getsu));
				}
				//아이템 정보보기//
				
			}
			for (int i = 0; i < 12; i++)
			{
				if (PtInRect(&_dialogRc[i], _ptMouse) && _toolInven[i]->GetToolEnum() != TOOLS::NONE)
				{
					_Dialog->setDialogClear(true);
					break;
				}
				else
				{
					_Dialog->setDialogClear(false);
				}
			}
		}
		break;
		case 3:		//키 알림 탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_KeyInfo")->render(getMemDC(), INVENIMAGECOOR);

			SetTextColor(getMemDC(), BLACK);

			TextOut(getMemDC(), 540, 220, "위로이동 : W", strlen("위로이동 : W"));
			TextOut(getMemDC(), 420, 260, "오른쪽이동 : A                왼쪽이동 : D", strlen("오른쪽이동 : A                왼쪽이동 : D"));
			TextOut(getMemDC(), 540, 300, "아래이동 : S", strlen("아래이동 : S"));

			TextOut(getMemDC(), 820, 220, "도구 사용, 상호작용 : 마우스 좌클릭", strlen("도구 사용, 상호작용 : 마우스 좌클릭"));

			TextOut(getMemDC(), 420, 350, "인벤토리 열기, 메뉴 열기 : E", strlen("인벤토리 열기, 메뉴 열기 : E"));
			TextOut(getMemDC(), 420, 380, "인벤토리 단축키 : 1 ~ 0,-,=", strlen("인벤토리 단축키 : 1 ~ 9,-,="));
		}
		break;
		case 4:		//게임 종료탭
		{
			_vInvenDynamicRC.clear();

			IMAGEMANAGER->findImage("UI_Inventory_Game_Close")->render(getMemDC(), INVENIMAGECOOR);

			_titleRC = RectMake(665, 334, 272, 96);							//종료탭에서 [타이틀 메뉴로] 버튼
			_closeRC = RectMake(699, 470, 204, 96);							//종료탭에서 [게임 종료] 버튼

		}
		break;
		}
	}
	else
	{
		if (SCENEMANAGER->GetNowScene() == "CAVE" && _store->getStoreOpen())
		{
			for (int i = 0; i < _toolInven.size(); ++i)
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
				TextOut(getMemDC(), 1370, -100, pGold, strlen(pGold));
			}
		}
		else
		{
			TextOut(getMemDC(), 1370, 203, pGold, strlen(pGold));
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
				for (int i = 0; i < _toolInven.size(); ++i)
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

	HFONT font3, oldFont3;
	font3 = CreateFont(40, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	oldFont3 = (HFONT)SelectObject(getMemDC(), font3);

	for (int i = 0; i < _qGetItem.size(); i++)
	{
		_tGetItem.ItemWindowRc = RectMake(-100, 700, _tGetItem.ItemWindow->getWidth(), _tGetItem.ItemWindow->getHeight());

		if (_qGetItem.front().ItemWindowRc.right <= 210)
		{
			_qGetItem.front().ItemWindowRc.left += 3;
			_qGetItem.front().ItemWindowRc.right += 3;
		}
		if (_qGetItem.front().isGet)
		{
			_qGetItem.front().ItemWindow->render(getMemDC(), _qGetItem.front().ItemWindowRc.left, _qGetItem.front().ItemWindowRc.top);
			_qGetItem.front().Item->render(getMemDC(), _qGetItem.front().ItemWindowRc.left + 5, _qGetItem.front().ItemWindowRc.top + 5);
			TextOut(getMemDC(), _qGetItem.front().ItemWindowRc.left + 80, _qGetItem.front().ItemWindowRc.top + 20,
				_qGetItem.front().ItemName.c_str(), strlen(_qGetItem.front().ItemName.c_str()));
			_qGetItem.front().Seetime++;
		}
		if (_qGetItem.front().Seetime > 150)
		{
			_qGetItem.front().ItemWindowRc.left -= 7;
			_qGetItem.front().ItemWindowRc.right -= 7;
			if (_qGetItem.front().ItemWindowRc.right < -10)
			{
				_qGetItem.front().isGet = false;
				_qGetItem.pop();
			}
		}
	}
	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);

	_Dialog->render();

	SelectObject(getMemDC(), oldFont1);
	DeleteObject(font1);

	/////////////////////////////////////////////////////////////////////////// <Debug_Rect>

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
	//Rectangle(getMemDC(), _sortRC);
	//Rectangle(getMemDC(), _craftingRC[0]);
	//Rectangle(getMemDC(), _craftingRC[1]);
	//Rectangle(getMemDC(), _craftingRC[2]);

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

void Inventory::Decrease()
{
	_toolInven[_index]->SetNumber(-1);
	if (_toolInven[_index]->GetNumber() <= 0)
	{
		_toolInven[_index] = new ToolItem;
		_toolInven[_index]->SetToolEnum(TOOLS::NONE);
		_player->ChangeEquipment(TOOLS::NONE);
	}
}

void Inventory::Merge(vector<ToolItem*>& vIndex, int left, int mid, int right)
{
	vector<ToolItem*> copy(right + 1);
	int copyIndex = 0;
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right)
	{
		if (vIndex[i]->GetNumber() >= vIndex[j]->GetNumber()) copy[copyIndex++] = vIndex[i++];
		else copy[copyIndex++] = vIndex[j++];
	}
	while (i <= mid) copy[copyIndex++] = vIndex[i++];
	while (j <= right) copy[copyIndex++] = vIndex[j++];
	for (int k = left, copyIndex = 0; k <= right; k++, copyIndex++)
		vIndex[k] = copy[copyIndex];

}

void Inventory::MergeSort(vector<ToolItem*>& vIndex, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(vIndex, left, mid);
		MergeSort(vIndex, mid + 1, right);
		Merge(vIndex, left, mid, right);
	}
}

void Inventory::PlayerLootItem(string itemName)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		if (_toolList[i]->GetName() == itemName)
		{
			for (int j = 0; j < 12; j++)
			{
				if (_toolInven[j]->GetName() == itemName)
				{
					if (_toolInven[j]->GetNumber() > 99) continue;
					_toolInven[j]->SetNumber(+1);
					_tGetItem.Item = _toolInven[j]->GetImageInven();
					_tGetItem.ItemName = _toolInven[j]->GetName();
					_tGetItem.isGet = true;
					_qGetItem.push(_tGetItem);
					return;
				}
			}
			for (int j = 0; j < 12; j++)
			{
				if (_toolInven[j]->GetToolEnum() == TOOLS::NONE)
				{
					_toolInven[j] = _toolList[i];
					_toolInven[j]->SetNumber(+1);
					_tGetItem.Item = _toolInven[j]->GetImageInven();
					_tGetItem.ItemName = _toolInven[j]->GetName();
					_tGetItem.isGet = true;
					_qGetItem.push(_tGetItem);
					return;
				}
			}
		}
	}
}

void Inventory::setPlayerBuyItme(ToolItem* buyItme)
{
	for (int i = 0; i < 12; i++)
	{
		if (_toolInven[i]->GetName() == buyItme->GetName())
		{
			if (_toolInven[i]->GetNumber() > 99) continue;
			_toolInven[i]->SetNumber(+1);
			if (_toolInven[i]->GetName() == "PasnipSeed") _player->SetDecreaseMoney(50);
			if (_toolInven[i]->GetName() == "PotatoSeed") _player->SetDecreaseMoney(50);
			if (_toolInven[i]->GetName() == "KaleSeed") _player->SetDecreaseMoney(70);
			if (_toolInven[i]->GetName() == "Stone") _player->SetDecreaseMoney(10);
			if (_toolInven[i]->GetName() == "Wood")	_player->SetDecreaseMoney(10);
			if (_toolInven[i]->GetName() == "Weed")	_player->SetDecreaseMoney(5);
			if (_toolInven[i]->GetName() == "Sap")	_player->SetDecreaseMoney(200);
			return;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (_toolInven[i]->GetName() != buyItme->GetName())
		{
			if (_toolInven[i]->GetToolEnum() == TOOLS::NONE)
			{
				_toolInven[i] = buyItme;
				_toolInven[i]->SetNumber(+1);
				if (_toolInven[i]->GetName() == "PasnipSeed") _player->SetDecreaseMoney(50);
				if (_toolInven[i]->GetName() == "PotatoSeed") _player->SetDecreaseMoney(50);
				if (_toolInven[i]->GetName() == "KaleSeed") _player->SetDecreaseMoney(70);
				if (_toolInven[i]->GetName() == "Stone") _player->SetDecreaseMoney(10);
				if (_toolInven[i]->GetName() == "Wood")	_player->SetDecreaseMoney(10);
				if (_toolInven[i]->GetName() == "Weed")	_player->SetDecreaseMoney(5);
				if (_toolInven[i]->GetName() == "Sap")	_player->SetDecreaseMoney(200);
				return;
			}
		}
	}
}

void Inventory::setPlayerSellItem(int num)
{
	for (int i = 0; i < _toolInven.size(); i++)
	{
		if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM ||
			_toolInven[i]->GetToolEnum() == TOOLS::EATITEM ||
			_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM)
		{
			if (_toolInven[i]->GetName() == _toolInven[num]->GetName())
			{
				if (_toolInven[i]->GetNumber() > 0)
				{
					_toolInven[i]->SetNumber(-1);
					if (_toolInven[i]->GetToolEnum() == TOOLS::RESOURCEITEM) _player->SetIncreaseMoney(2);
					if (_toolInven[i]->GetToolEnum() == TOOLS::ACTIVEITEM) _player->SetIncreaseMoney(25);
					if (_toolInven[i]->GetToolEnum() == TOOLS::EATITEM) _player->SetIncreaseMoney(100);
					if (_toolInven[i]->GetToolEnum() == TOOLS::ITEM) _player->SetIncreaseMoney(50);
				}

				if (_toolInven[i]->GetNumber() == 0)
				{
					_toolInven[i] = new Wood;
				}
				break;
			}
		}
	}
}
