#include "stdafx.h"
#include "MapToolScene.h"



void MapToolScene::Button()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		EFFECTMANAGER->play("RockDis", _ptMouse.x, _ptMouse.y);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1) || (PtInRect(&_f1Btn,_ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))))
	{
		if (_Window)
		{
			_Window = false;
		}
		else
		{
			_Window = true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * _horizontal + (j + cullX);

				if (_vtiles[index].object == MAPOBJECT::HOETILE)
				{
				_vtiles[index].wet = true;
				}
			}
		}
		Auto();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * _horizontal + (j + cullX);

				_vtiles[index].wet = false;
			}
		}
	}

	if (PtInRect(&_inBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		OutToIn(50, 50);
	}
	if (PtInRect(&_outBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		InToOut(50, 50);
	}

	if (PtInRect(&_terrainBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::TERRAINDRAW;
		_terrainPage = 0;
	}
	if (_crtSelect == CRTSELECT::TERRAINDRAW ||
		_crtSelect == CRTSELECT::HOETILEDRAW ||
		_crtSelect == CRTSELECT::WALLDRAW)
	{
		if (PtInRect(&_upBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) && (_terrainPage > 0))
		{
			_terrainPage--;
		}
		if (PtInRect(&_downBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) && (_terrainPage < 2))
		{
			_terrainPage++;
		}
		if (_inout == INOUT::OUTDOOR)
		{
			switch (_terrainPage)
			{
			case 0:
				_crtSelect = CRTSELECT::TERRAINDRAW;
				_currentTile.object = MAPOBJECT::NONE;
				SetSample("Terrain");
				break;
			case 1:
				_crtSelect = CRTSELECT::WALLDRAW;
				SetSample("Wall");
				break;
			case 2:
				_crtSelect = CRTSELECT::HOETILEDRAW;
				SetSample("HoeTile");
				break;
			}
		}
		else
		{
			switch (_terrainPage)
			{
			case 0:
				_crtSelect = CRTSELECT::TERRAINDRAW_INDOOR;
				_currentTile.object = MAPOBJECT::NONE;
				SetSample("Terrain_InDoor");
				break;
			case 1:
				_crtSelect = CRTSELECT::TERRAINDRAW_CAVE;
				break;
			case 2:
				_crtSelect = CRTSELECT::HOETILEDRAW;
				break;
			}
		}
	}

	if (PtInRect(&_treeBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		if (_inout == INOUT::OUTDOOR)
		{
			_crtSelect = CRTSELECT::OBJECTDRAW;
			SetSample("Tree");
		}
		else
		{
			_crtSelect = CRTSELECT::OBJECTDRAW;
			SetSample("Bed");
		}
	}
	if (PtInRect(&_buildingBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		if (_inout == INOUT::OUTDOOR)
		{
			_crtSelect = CRTSELECT::BUILDINGDRAW;
			SetSample("House");
		}
		else
		{
			_crtSelect = CRTSELECT::BUILDINGDRAW;
			SetSample("Wall_Cave");
		}
	}

	if (PtInRect(&_enemyBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::ENEMYDRAW;
	}
	if (PtInRect(&_collisionBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::COLLISION;
		SetSample("POS");
	}
	if (PtInRect(&_eraserBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) || (KEYMANAGER->isOnceKeyDown('E')))
	{
		_crtSelect = CRTSELECT::ERASER;
	}
	if (PtInRect(&_saveBtn[0], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		Save("mapCave.map",_horizontal,_vertical,_vtiles);
		_saveimg = true;
		_count = 0;
	}

	if (_count >= 50)
	{
		_saveimg = false;
		_count = 0;
	}
	if (PtInRect(&_saveBtn[1], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		Save("mapCave.map", _horizontal, _vertical, _vtiles);
	}
	if (PtInRect(&_saveBtn[2], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		Save("mapCave.map", _horizontal, _vertical, _vtiles);
	}
	if (PtInRect(&_loadBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_vtiles = Load("mapCave.map", _horizontal, _vertical);
	}
	if (PtInRect(&_exitBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		SCENEMANAGER->changeScene("Title");
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		SetMap_L();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_drag = true;
		_Ex.x = _ptMouse.x + CAMERAMANAGER->getX() - 800 - 1;
		_Ex.y = _ptMouse.y + CAMERAMANAGER->getY() - 450 - 1;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_drag = false;
		SetMap_R();
	}

	if (_Window)
	{
		_f1Btn = RectMake(WINSIZEX - IMAGEMANAGER->findImage("F1")->getWidth()-700, 100,64,52);
		_terrainBtn = RectMake(939, 59, 99, 41);
		_treeBtn = RectMake(1046, 59, 99, 41);
		_buildingBtn = RectMake(1156, 59, 99, 41);
		_enemyBtn = RectMake(1263, 59, 99, 41);
		_collisionBtn = RectMake(1370, 59, 99, 41);
		_eraserBtn = RectMake(1160, 791, 99, 41);
		_saveBtn[0] = RectMake(946, 745, 99, 41);
		_saveBtn[1] = RectMake(1053, 745, 99, 41);
		_saveBtn[2] = RectMake(1160, 745, 99, 41);
		_loadBtn = RectMake(1053, 791, 99, 41);
		_inBtn = RectMake(1421, 770, 99, 41);
		_outBtn = RectMake(1310, 770, 99, 41);
		_exitBtn = RectMake(1531, 35, 31, 32);
		_upBtn = RectMake(WINSIZEX - 100, 300, 44, 44);
		_downBtn = RectMake(WINSIZEX - 100, 500, 44, 44);
		_sampleArea = RectMake(WINSIZEX - 650, 40 + TILESIZE, 550, 600);
	}
	else
	{
		_f1Btn = RectMake(WINSIZEX - IMAGEMANAGER->findImage("F1")->getWidth(), 100, 64, 52);
		_terrainBtn = RectMake(939 + 900, 59, 99, 41);
		_treeBtn = RectMake(1046 + 900, 59, 99, 41);
		_buildingBtn = RectMake(1156 + 900, 59, 99, 41);
		_enemyBtn = RectMake(1263 + 900, 59, 99, 41);
		_collisionBtn = RectMake(1370 + 900, 59, 99, 41);
		_eraserBtn = RectMake(1160 + 900, 791, 99, 41);
		_saveBtn[0] = RectMake(946 + 900, 745, 99, 41);
		_saveBtn[1] = RectMake(1053 + 900, 745, 99, 41);
		_saveBtn[2] = RectMake(1160 + 900, 745, 99, 41);
		_loadBtn = RectMake(1053 + 900, 791, 99, 41);
		_inBtn = RectMake(1421 + 900, 770, 99, 41);
		_outBtn = RectMake(1310 + 900, 770, 99, 41);
		_exitBtn = RectMake(1531 + 900, 35, 31, 32);
		_upBtn = RectMake(WINSIZEX - 100 + 900, 300, 44, 44);
		_downBtn = RectMake(WINSIZEX - 100 + 900, 500, 44, 44);
		_sampleArea = RectMake(WINSIZEX, 40 + TILESIZE, 550, 600);
	}

}