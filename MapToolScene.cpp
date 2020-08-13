#include "stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
}

MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init()
{
	_Mouse = IMAGEMANAGER->findImage("mouse");

	_draw = RectMake(-65, -65, 0, 0);
	_sampleArea = RectMake(WINSIZEX - 650, 100 + TILESIZE, 550, 600);
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
	
	_Line.x = -100;
	_Line.y = -100;

	_Window = false;
	_count = 0;
	_terrainPage = 0;

	SetUp();
	SetSample("Terrain");

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
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

	if (PtInRect(&_inBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		OutToIn(30,30);
	}
	if (PtInRect(&_outBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		InToOut(100,100);
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
		_crtSelect = CRTSELECT::TREEDRAW;
		SetSample("Tree");
		}
		else
		{

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

		}
	}

	if (PtInRect(&_enemyBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::ENEMYDRAW;
	}
	if (PtInRect(&_collisionBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::COLLISION;
	}
	if (PtInRect(&_eraserBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) ||(KEYMANAGER->isOnceKeyDown('E')))
	{
		_crtSelect = CRTSELECT::ERASER;
	}
	if (PtInRect(&_saveBtn[0], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::SAVE;
		Save();
	}
	if (PtInRect(&_saveBtn[1], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::SAVE;
		Save();
	}
	if (PtInRect(&_saveBtn[2], _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::SAVE;
		Save();
	}
	if (PtInRect(&_loadBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::LOAD;
		Load();
	}
	if (PtInRect(&_exitBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		SCENEMANAGER->changeScene("타이틀화면");
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

	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (PtInRect(&_vtiles[index].rc, _CameraMouse) && (!_drag))
			{
				_Line.x = _vtiles[index].rc.left;
				_Line.y = _vtiles[index].rc.top;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (PtInRect(&_sampleTile[i * 8 + j].rc, _ptMouse))
			{
				_Line.x = _sampleTile[i * 8 + j].rc.left + CAMERAMANAGER->getL();
				_Line.y = _sampleTile[i * 8 + j].rc.top + CAMERAMANAGER->getT();
			}
		}
	}

	//렉트의 너비, 높이 값이 음수가 될 경우 렉트충돌이 되지않아서
	//상황마다 바꿔준다
	if (_drag)
	{
		if (_Ex.x < _CameraMouse.x)
		{
			_draw.left = _Ex.x;
			_draw.top = _Ex.y;
			_draw.right = _CameraMouse.x;
			_draw.bottom = _CameraMouse.y;
		}
		else if (_Ex.x > _CameraMouse.x)
		{
			_draw.left = _CameraMouse.x;
			_draw.top = _Ex.y;
			_draw.right = _Ex.x;
			_draw.bottom = _CameraMouse.y;
		}
		if (_Ex.y > _CameraMouse.y)
		{

			if (_Ex.x > _CameraMouse.x)
			{
				_draw.left = _CameraMouse.x;
				_draw.top = _CameraMouse.y;
				_draw.right = _Ex.x;
				_draw.bottom = _Ex.y;
			}
			else
			{
				_draw.left = _Ex.x;
				_draw.top = _CameraMouse.y;
				_draw.right = _CameraMouse.x;
				_draw.bottom = _Ex.y;
			}
		}
	}
	
	_count++;
}

void MapToolScene::render()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (_inout == INOUT::OUTDOOR)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].terrainframeX, _vtiles[index].terrainframeY);
			}
			else
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain_InDoor"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].terrainframeX, _vtiles[index].terrainframeY);
			}

			if (_count % 20 == 0)
			{

				if (_inout == INOUT::OUTDOOR)
				{
					if ((_vtiles[index].terrainframeX == 6 || _vtiles[index].terrainframeX == 5) && _vtiles[index].terrainframeY == 2 &&
						_vtiles[index].terrain == TERRAIN::GRASS)
					{
						if (_vtiles[index].terrainframeX > 5)_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeX++;
					}
					if (_vtiles[index].terrain == TERRAIN::WATER)
					{
						if (_vtiles[index].terrainframeX == 3)_vtiles[index].terrainframeX = -1;
						_vtiles[index].terrainframeX++;
					}
				}
			}
		}
	}

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;

			if (_vtiles[index].object == MAPOBJECT::BUILDING)
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"),
					_vtiles[index].rc.left - TILESIZE * 8, _vtiles[index].rc.top - TILESIZE * 8,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom);

			}
			if ((_vtiles[index].object == MAPOBJECT::TREE1) ||
				(_vtiles[index].object == MAPOBJECT::TREE2) ||
				(_vtiles[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					_vtiles[index].rc.left - TILESIZE, _vtiles[index].rc.top - TILESIZE * 5,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom + 1);
			}

			if (j > 14 || i > 14) continue;

			if ((_vtiles[index].object == MAPOBJECT::HOETILE) ||
				(_vtiles[index].object == MAPOBJECT::HOETILE_WET) ||
				(_vtiles[index].object == MAPOBJECT::WEED) ||
				(_vtiles[index].object == MAPOBJECT::BRANCH) ||
				(_vtiles[index].object == MAPOBJECT::ROCK))
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY);
			}
			if (_vtiles[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY);
			}
		}
	}
	ZORDER->ZOrderRender();

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			////////////////////////////////////////////////////////////// 스폰 지점
			if (_vtiles[index].pos != POS::NONE)
			{
				Rectangle(getMemDC(), _vtiles[index].rc);
			}
			///////////////////////////////////////////////////////////////

			if (_vtiles[index].collision && (KEYMANAGER->isToggleKey(VK_TAB)))
			{
				CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Collision"), _vtiles[index].rc.left, _vtiles[index].rc.top);
			}
			if (isCollision(_vtiles[index].rc, _draw))
			{
				CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"), _vtiles[index].rc.left, _vtiles[index].rc.top);

			}
		}
	}

	if (_Window)
	{
		_sampleArea = RectMake(WINSIZEX - 650, 100 + TILESIZE, 550, 600);
		IMAGEMANAGER->render("Window", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth(), 0);
	}
	else
	{
		_sampleArea = RectMake(WINSIZEX, 100 + TILESIZE, 550, 600);
	}

	switch (_crtSelect)
	{
	case CRTSELECT::TERRAINDRAW:
		IMAGEMANAGER->render("Terrain", getMemDC(), _sampleArea.left, _sampleArea.top);

		if (!_Window)break;
		IMAGEMANAGER->render("DownArrow", getMemDC(), WINSIZEX - 100, 500);
		break;
	case CRTSELECT::TERRAINDRAW_INDOOR:
		IMAGEMANAGER->render("Terrain_InDoor", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::WALLDRAW:
		IMAGEMANAGER->render("Wall", getMemDC(), _sampleArea.left, _sampleArea.top);

		if (!_Window)break;
		IMAGEMANAGER->render("UpArrow", getMemDC(), WINSIZEX - 100, 300);
		IMAGEMANAGER->render("DownArrow", getMemDC(), WINSIZEX - 100, 500);
		break;
	case CRTSELECT::HOETILEDRAW:
		IMAGEMANAGER->render("HoeTile", getMemDC(), _sampleArea.left, _sampleArea.top);

		if (!_Window)break;
		IMAGEMANAGER->render("UpArrow", getMemDC(), WINSIZEX - 100, 300);
		break;
	case CRTSELECT::TREEDRAW:
		IMAGEMANAGER->render("Tree", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::BUILDINGDRAW:
		IMAGEMANAGER->render("House", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	}
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"), _Line.x, _Line.y);

	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
}

void MapToolScene::SetUp()
{
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZE * 100 -900, TILESIZE * 100);

	_currentTile.terrainframeX = 0;
	_currentTile.terrainframeY = 0;

	_inout = INOUT::OUTDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW;

	_vertical = 100;
	_horizontal = 100;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = 0;
			tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.autoIndex = 0;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_vtiles.push_back(tile);
		}
	}
}

void MapToolScene::SetSample(string img)
{
	int SampleX = IMAGEMANAGER->findImage(img)->getWidth() / TILESIZE;
	int SampleY = IMAGEMANAGER->findImage(img)->getHeight() / TILESIZE;

	switch (_crtSelect)
	{
	case CRTSELECT::TERRAINDRAW:
	case CRTSELECT::TERRAINDRAW_INDOOR:
	case CRTSELECT::WALLDRAW:
	case CRTSELECT::HOETILEDRAW:
		for (int i = 0; i < SampleY; ++i)
		{
			for (int j = 0; j < SampleX; ++j)
			{
				_sampleTile[i * SampleX + j].terrainframeX = j;
				_sampleTile[i * SampleX + j].terrainframeY = i;

				_sampleTile[i * SampleX + j].rc = RectMake(
					_sampleArea.left + j * TILESIZE,
					_sampleArea.top + i * TILESIZE,
					TILESIZE,
					TILESIZE);
			}
		}
		break;
	case CRTSELECT::TREEDRAW:
		for (int i = 0; i < 1; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				_sampleTile[i * SampleX + j].terrainframeX = j;
				_sampleTile[i * SampleX + j].terrainframeY = i;

				_sampleTile[i * SampleX + j].rc = RectMake(
					_sampleArea.left + j * (TILESIZE * 3),
					_sampleArea.top + i * TILESIZE,
					TILESIZE * 3,
					TILESIZE * 6);
			}
		}
		break;
	case CRTSELECT::BUILDINGDRAW:
		_sampleTile[0].terrainframeX = 0;
		_sampleTile[0].terrainframeY = 0;

		_sampleTile[0].rc = RectMake(
			_sampleArea.left,
			_sampleArea.top,
			TILESIZE * 9,
			TILESIZE * 9);
		break;
	}
}

void MapToolScene::InToOut(int Horizontal, int Vertical)
{
	_vtiles.clear();

	_horizontal = Horizontal;
	_vertical = Vertical;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = 0;
			tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.autoIndex = 0;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_vtiles.push_back(tile);
		}
	}
	_inout = INOUT::OUTDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW;
}

void MapToolScene::OutToIn(int Horizontal, int Vertical)
{
	_vtiles.clear();

	_horizontal = Horizontal;
	_vertical = Vertical;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = 0;
			tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.autoIndex = 0;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_vtiles.push_back(tile);
		}
	}
	_inout = INOUT::INDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW_INDOOR;
}

void MapToolScene::SetMap_L()
{
	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());
	for (int i = 0; i < 15 * 8; ++i)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_currentTile.terrainframeX = _sampleTile[i].terrainframeX;
			_currentTile.terrainframeY = _sampleTile[i].terrainframeY;

			_currentTile.terrain = TerrainSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
			break;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (PtInRect(&_vtiles[index].rc, _CameraMouse))
			{
				if (_ptMouse.x < WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth())
				{
					if (_crtSelect == CRTSELECT::TERRAINDRAW)
					{
						_vtiles[index].terrainframeX = _currentTile.terrainframeX;
						_vtiles[index].terrainframeY = _currentTile.terrainframeY;

						_vtiles[index].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
					}

					if (_crtSelect == CRTSELECT::TERRAINDRAW_INDOOR)
					{
						_vtiles[index].terrainframeX = _currentTile.terrainframeX;
						_vtiles[index].terrainframeY = _currentTile.terrainframeY;

						_vtiles[index].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
					}

					if (_crtSelect == CRTSELECT::WALLDRAW)
					{
						_vtiles[index].objectframeX = _currentTile.terrainframeX;
						_vtiles[index].objectframeY = _currentTile.terrainframeY;

						_vtiles[index].object = MAPOBJECT::WALL;
						_vtiles[index].collision = true;
					}

					if ((_vtiles[index].terrain != TERRAIN::WATER) && (!_vtiles[index].collision))
					{
						if (_crtSelect == CRTSELECT::HOETILEDRAW)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);

							if ((_vtiles[index].object != MAPOBJECT::HOETILE ) && (_vtiles[index].object != MAPOBJECT::HOETILE_WET))
							{
								_vtiles[index].collision = true;
							}
						}

						if (_crtSelect == CRTSELECT::TREEDRAW)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
							_vtiles[index].collision = true;
							_vtiles[index].hp = 5;
						}
						if (_crtSelect == CRTSELECT::BUILDINGDRAW)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeX;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);

							for (int i = 0; i < 5; ++i)
							{
								for (int j = 0; j < 9; j++)
								{
									if (index - _vertical * i - j < 0)continue;
									if ((i == 0) &&( j > 1 && j< 5) || (i == 1) && (j > 0 && j < 8))continue;
										_vtiles[index - _vertical * i - j].collision = true;
										_vtiles[index - _vertical * 2 - 3].pos = POS::HOME;
								}
							}

						}
					}
					if (_crtSelect == CRTSELECT::ERASER)
					{
						_vtiles[index].objectframeX = NULL;
						_vtiles[index].objectframeY = NULL;
						_vtiles[index].collision = false;
						_vtiles[index].object = MAPOBJECT::NONE;
						_vtiles[index].pos = POS::NONE;
					}
					if (_crtSelect == CRTSELECT::COLLISION)
					{
						_vtiles[index].collision = false;
					}
				}
			}
		}
	}
}

void MapToolScene::SetMap_R()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			_vtiles[index].autoIndex = 0;
			if (isCollision(_vtiles[index].rc, _draw))
			{
				if (_ptMouse.x < WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth())
				{
					if (_crtSelect == CRTSELECT::TERRAINDRAW)
					{
						if (_currentTile.terrain == TERRAIN::DIRT)
						{
							if (_vtiles[index].terrain == TERRAIN::WATER)
							{
								_vtiles[index].collision = false;
							}
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 6);
							_vtiles[index].terrainframeY = RND->getFromIntTo(0, 2);
							_vtiles[index].terrain = TERRAIN::DIRT;
						}
						else if (_currentTile.terrain == TERRAIN::GRASS)
						{
							if (_vtiles[index].terrain == TERRAIN::WATER)
							{
								_vtiles[index].collision = false;
							}
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 6);
							_vtiles[index].terrainframeY = 2;
							_vtiles[index].terrain = TERRAIN::GRASS;
						}
						else if (_currentTile.terrain == TERRAIN::WATER)
						{
							_vtiles[index].terrainframeX = 0;
							_vtiles[index].terrainframeY = 6;
							_vtiles[index].objectframeX = NULL;
							_vtiles[index].objectframeY = NULL;
							_vtiles[index].object = MAPOBJECT::NONE;
							_vtiles[index].terrain = TERRAIN::WATER;
							_vtiles[index].collision = true;
						}
						else
						{
							_vtiles[index].terrainframeX = _currentTile.terrainframeX;
							_vtiles[index].terrainframeY = _currentTile.terrainframeY;
							_vtiles[index].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
						}
					}
					if (_crtSelect == CRTSELECT::TERRAINDRAW_INDOOR)
					{
						_vtiles[index].terrainframeX = _currentTile.terrainframeX;
						_vtiles[index].terrainframeY = _currentTile.terrainframeY;
					}
					if (_crtSelect == CRTSELECT::ERASER)
					{
						_vtiles[index].objectframeX = NULL;
						_vtiles[index].objectframeY = NULL;
						_vtiles[index].object = MAPOBJECT::NONE;
						_vtiles[index].collision = false;
						_vtiles[index].pos = POS::NONE;
					}
					if (_crtSelect == CRTSELECT::COLLISION)
					{
						_vtiles[index].collision = true;
					}
				}
			}
		}
	}
	_draw = RectMake(0, 0, -1, -1);
	if (_crtSelect == CRTSELECT::TERRAINDRAW)
	{
		Auto();
	}
}

void MapToolScene::Save()
{
	tagTile* saveTile = new tagTile[_vertical*_horizontal+1];
	for (int i = 0; i < _vtiles.size(); i++)
	{
		saveTile[i] = _vtiles[i];
	}
	HANDLE file;
	DWORD write;

	file = CreateFile("map.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveTile, sizeof(tagTile) * _vtiles.size(), &write, NULL);


	CloseHandle(file);
}

void MapToolScene::Load()
{
	tagTile* saveTile = new tagTile[_vertical * _horizontal + 1];
	HANDLE file;
	DWORD read;

	file = CreateFile("map.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(tagTile) * _vtiles.size(), &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < _vtiles.size(); i++)
	{
		_vtiles[i] = saveTile[i];
	}
}

void MapToolScene::Auto()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;
			int index = (i + cullY) * _horizontal + (j + cullX);

			_vtiles[index].autoIndex = 0;

			if (_vtiles[index].terrain == TERRAIN::GRASS)
			{
				/////////////////  좌
				if (_vtiles[index].rc.left / TILESIZE > 0)
				{
					if (_vtiles[index - 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 8;
					}
				}
				/////////////////  우
				if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 2;
					}
				}
				/////////////////  위
				if (_vtiles[index].rc.top / TILESIZE > 0)
				{
					if (_vtiles[index - _vertical].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 1;
					}
				}
				/////////////////  아래
				if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + _vertical].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 4;
					}
				}
				///////////////// 우 상단
				if (_vtiles[index].rc.top / TILESIZE > 0)
				{
					if (_vtiles[index - _vertical + 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 16;
					}
				}
				///////////////// 우 하단
				//if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + _vertical + 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 32;
					}
				}
				/////////////////// 좌 상단
				if (_vtiles[index].rc.top / TILESIZE > 0 && _vtiles[index].rc.left / TILESIZE > 0)
				{
					if (_vtiles[index - _vertical - 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 128;
					}
				}
				/////////////////// 좌 하단
				//if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + _vertical - 1].terrain == TERRAIN::GRASS)
					{
						_vtiles[index].autoIndex += 64;
					}
				}
			}


			switch (_vtiles[index].autoIndex)
			{
			case 255:
				_vtiles[index].terrainframeX = RND->getFromIntTo(0, 6);
				_vtiles[index].terrainframeY = 2;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른쪽
			case 205:
			case 221:
			case 237:
			case 253:
				_vtiles[index].terrainframeX = 2;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼쪽
			case 55:
			case 183:
			case 119:
			case 247:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//위
			case 110:
			case 126:
			case 238:
			case 254:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//아래
			case 155:
			case 187:
			case 219:
			case 251:
				_vtiles[index].terrainframeX = 0;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼아래
			case 19:
			case 51:
			case 82:
			case 83:
			case 87:
			case 179:
			case 147:
			case 211:
			case 215:
				_vtiles[index].terrainframeX = 2;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼위
			case 38:
			case 54:
			case 102:
			case 118:
			case 166:
			case 167:
				_vtiles[index].terrainframeX = 0;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른위
			case 76:
			case 92:
			case 93:
			case 204:
			case 108:
			case 220:
			case 124:
			case 222:
			case 236:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른아래
			case 137:
			case 169:
			case 173:
			case 153:
			case 201:
			case 217:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//왼위경사
			case 127:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//오른위경사
			case 239:
				_vtiles[index].terrainframeX = 2;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//왼아래경사
			case 191:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//오른아래경사
			case 193:
			case 223:
				_vtiles[index].terrainframeX = 0;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//오른쪽대각 1칸
			case 95:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼쪽 대각 1칸
			case 175:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//위로 1칸
			case 4:
			case 100:
			case 68:
			case 36:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼쪽 1칸
			case 18:
			case 2:
			case 66:
			case 50:
			case 34:
			case 168:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른쪽 1칸
			case 200:
			case 8:
			case 136:
			case 72:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//아래 1칸
			case 52:
			case 129:
			case 145:
			case 1:
			case 196:
			case 17:
			case 33:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				////////////////////////////////////////////////////////////////////////////////

				//위로 솟아나
			case 111:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//아래로 솟아나
			case 159:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른쪽으로 솟아나
			case 207:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼쪽으로 솟아나
			case 63:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//가로
			case 10:
			case 26:
			case 42:
			case 58:
			case 250:
			case 106:
			case 186:
			case 154:
			case 138:
			case 218:
			case 234:
			case 202:
			case 74:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//세로
			case 101:
			case 149:
			case 69:
			case 181:
			case 5:
			case 53:
			case 245:
			case 85:
			case 197:
			case 229:
			case 21:
			case 133:
			case 37:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//기억자 <아래
			case 12:
			case 44:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 0;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//기억자 아래>
			case 9:
			case 86:
			case 163:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 1;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//기억자 위>
			case 3:
			case 35:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 1;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//기억자1 <위
			case 6:
			case 131:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 0;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				////////////////////////이상한 대각선들
			case 174:
			case 46:
				_vtiles[index].terrainframeX = 0;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 27:
			case 91:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 231:
			case 39:
			case 103:
				_vtiles[index].terrainframeX = 2;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 23:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 206:
			case 94:
			case 78:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 139:
			case 171:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 77:
			case 109:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 189:
			case 141:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 7;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//////////////////////  세갈래 
				// <아래>
			case 14:
			case 158:
			case 142:
			case 30:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				// <위>
			case 11:
			case 43:
			case 75:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				// <위아래
			case 13:
			case 29:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				// 위아래>
			case 7:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				// 사방
			case 15:
				_vtiles[index].terrainframeX = 7;
				_vtiles[index].terrainframeY = 2;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			}
		}
	}
}


TERRAIN MapToolScene::TerrainSelect(int frameX, int frameY)
{
	if (frameY == 2)return TERRAIN::GRASS;
	
	if (frameY <= 2 && frameX <= 5)
	{
		return TERRAIN::DIRT;
	}
	else if (frameY == 6 && frameX <= 3)
	{
		return TERRAIN::WATER;
	}
	else
	{
		return TERRAIN::GRASS;
	}
}

MAPOBJECT MapToolScene::ObjectSelect(int frameX, int frameY)
{
	switch (_crtSelect)
	{
	case CRTSELECT::WALLDRAW:
		if (frameX >= 4 && (frameY <= 2))return MAPOBJECT::WALL;
		else return MAPOBJECT::WALL;
		break;
	case CRTSELECT::HOETILEDRAW:
		if (frameX <= 4 && (frameY <= 2))return MAPOBJECT::HOETILE;
		if ((frameY >= 3))return MAPOBJECT::HOETILE_WET;
		if (frameX == 5 && (frameY == 0))return MAPOBJECT::ROCK;
		if (frameX == 5 && (frameY == 1))return MAPOBJECT::BRANCH;
		if (frameX == 5 && (frameY == 2))return MAPOBJECT::WEED;
		break;
	case CRTSELECT::TREEDRAW:
		if (frameX == 0)return MAPOBJECT::TREE1;
		if (frameX == 1)return MAPOBJECT::TREE2;
		if (frameX == 2)return MAPOBJECT::TREE3;
		break;
	case CRTSELECT::BUILDINGDRAW:
		if (frameX ==0)return MAPOBJECT::BUILDING;
		break;
	case CRTSELECT::ENEMYDRAW:
		break;
	}
	return MAPOBJECT();
}
