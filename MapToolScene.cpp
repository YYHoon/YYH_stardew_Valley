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

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZE*50-900, TILESIZE * 50);

	_vertical = 100;
	_horizontal = 100;

	_currentTile.terrainframeX = 0;
	_currentTile.terrainframeY = 0;

	_draw = RectMake(-65, -65, 0, 0);
	_sampleArea = RectMake(WINSIZEX - 650, 100 + TILESIZE, 550, 600);
	_terrainBtn = RectMake(939, 59, 99, 41);
	_treeBtn = RectMake(1046, 59, 99, 41);
	_buildingBtn = RectMake(1156, 59, 99, 41);
	_enemyBtn = RectMake(1263, 59, 99, 41);
	_collisionBtn = RectMake(1370, 59, 99, 41);
	_eraserBtn = RectMake(1160, 791, 99, 41);
	_saveBtn = RectMake(946, 791, 99, 41);
	_loadBtn = RectMake(1053, 791, 99, 41);
	_exitBtn = RectMake(1531, 35, 31, 32);

	_Line.x = -100;
	_Line.y = -100;

	_count = 0;

	SetUp();
	SetSample("Terrain");

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	if (PtInRect(&_terrainBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) || KEYMANAGER->isOnceKeyDown('1'))
	{
		_crtSelect = CRTSELECT::TERRAINDRAW;
		_currentTile.object = MAPOBJECT::NONE;
		SetSample("Terrain");
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_crtSelect = CRTSELECT::WALLDRAW;
		SetSample("Wall");
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_crtSelect = CRTSELECT::HOETILEDRAW;
		SetSample("HoeTile");
	}
	if (PtInRect(&_treeBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::TREEDRAW;
		SetSample("Tree");
	}
	if (PtInRect(&_buildingBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::BUILDINGDRAW;
		SetSample("House");
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
	if (PtInRect(&_saveBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
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

	//if (_isLeftClick)
	//{
	//	SetMap_L();
	//}

	//렉트의 너비, 높이 값이 음수가 될 경우 렉트충돌이 되지않아서
	//상황마다 바꿔준다
	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
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
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
				_vtiles[index].rc.left, _vtiles[index].rc.top,
				_vtiles[index].terrainframeX, _vtiles[index].terrainframeY);

		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (_count % 20 == 0)
			{
				if ((_vtiles[index].terrainframeX == 6 || _vtiles[index].terrainframeX == 5) && _vtiles[index].terrainframeY == 2)
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

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;
			if (_vtiles[index].object == MAPOBJECT::WALL)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Wall"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY);
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;

			if ((_vtiles[index].object == MAPOBJECT::HOETILE )||
				 (_vtiles[index].object == MAPOBJECT::WEED )||
				 (_vtiles[index].object == MAPOBJECT::BRANCH )||
				 (_vtiles[index].object == MAPOBJECT::ROCK ))
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY);
			}
		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;

			if (_vtiles[index].object == MAPOBJECT::HOETILE_WET)
			{
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].wetframeX, _vtiles[index].wetframeY);
			}
		}
	}
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 26; j++)
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
		}
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;

			if ((_vtiles[index].object == MAPOBJECT::TREE1)||
				(_vtiles[index].object == MAPOBJECT::TREE2)||
				(_vtiles[index].object == MAPOBJECT::TREE3))
			{
				ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
					_vtiles[index].rc.left - TILESIZE, _vtiles[index].rc.top - TILESIZE * 5,
					_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom+1);
			}
		}
	}
	ZORDER->ZOrderRender();

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (_vtiles[index].collision && (KEYMANAGER->isToggleKey(VK_TAB)))
			{
				CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Collision"), _vtiles[index].rc.left, _vtiles[index].rc.top);
			}
			if (isCollision(_vtiles[index].rc,_draw))
			{
				CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"), _vtiles[index].rc.left, _vtiles[index].rc.top);
			}
		}
	}
	IMAGEMANAGER->render("Window", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth(), 0);

	switch (_crtSelect)
	{
	case CRTSELECT::TERRAINDRAW:
		IMAGEMANAGER->render("Terrain", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::WALLDRAW:
		IMAGEMANAGER->render("Wall", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::HOETILEDRAW:
		IMAGEMANAGER->render("HoeTile", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::TREEDRAW:
		IMAGEMANAGER->render("Tree", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::BUILDINGDRAW:
		IMAGEMANAGER->render("House", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	}

	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"),_Line.x,_Line.y);
	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Select"),_Ex.x,_Ex.y);
	//CAMERAMANAGER->frameRender(getMemDC(),_Mouse,_ptMouse.x,_ptMouse.y,0,0);
	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
}

void MapToolScene::SetUp()
{
	_crtSelect = CRTSELECT::TERRAINDRAW;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = 0;
			tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.wetframeX = 0;
			tile.wetframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
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
	case CRTSELECT::WALLDRAW:
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
			_currentTile.object = ObjectSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);

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

					if (_crtSelect == CRTSELECT::WALLDRAW)
					{
						_vtiles[index].objectframeX = _currentTile.terrainframeX;
						_vtiles[index].objectframeY = _currentTile.terrainframeY;

						_vtiles[index].object = MAPOBJECT::WALL;
					}

					if ((_vtiles[index].terrain != TERRAIN::WATER) && (!_vtiles[index].collision))
					{
						if (_crtSelect == CRTSELECT::HOETILEDRAW)
						{
							if (_currentTile.object == MAPOBJECT::HOETILE_WET)
							{
								_vtiles[index].wetframeX = _currentTile.terrainframeX;
								_vtiles[index].wetframeY = _currentTile.terrainframeY;
							}
							else
							{
								_vtiles[index].objectframeX = _currentTile.terrainframeX;
								_vtiles[index].objectframeY = _currentTile.terrainframeY;
								_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
							}

						}

						if (_crtSelect == CRTSELECT::TREEDRAW)
						{
							{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
							}
						}
						if (_crtSelect == CRTSELECT::BUILDINGDRAW)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeX;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
						}
					}
					if (_crtSelect == CRTSELECT::ERASER)
					{
						_vtiles[index].objectframeX = NULL;
						_vtiles[index].objectframeY = NULL;
						_vtiles[index].wetframeX = NULL;
						_vtiles[index].wetframeY = NULL;
						_vtiles[index].object = MAPOBJECT::NONE;
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

			if (isCollision(_vtiles[index].rc, _draw))
			{
				if (_ptMouse.x < WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth())
				{
					if (_crtSelect == CRTSELECT::TERRAINDRAW)
					{
						_vtiles[index].autoIndex = 0;

						if (_currentTile.terrain == TERRAIN::DIRT)
						{
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 7);
							_vtiles[index].terrainframeY = RND->getFromIntTo(0, 2);
							_vtiles[index].terrain = TERRAIN::DIRT;
						}
						else if (_currentTile.terrain == TERRAIN::GRASS)
						{
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 6);
							_vtiles[index].terrainframeY = 2;
							_vtiles[index].terrain = TERRAIN::GRASS;
						}
						else if (_currentTile.terrain == TERRAIN::WATER)
						{
							_vtiles[index].terrainframeX = 0;
							_vtiles[index].terrainframeY = 6;
							_vtiles[index].terrain = TERRAIN::WATER;
						}
						else
						{
							_vtiles[index].terrainframeX = _currentTile.terrainframeX;
							_vtiles[index].terrainframeY = _currentTile.terrainframeY;
							_vtiles[index].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
						}
						
					}
					if (_crtSelect == CRTSELECT::ERASER)
					{
						_vtiles[index].objectframeX = NULL;
						_vtiles[index].objectframeY = NULL;
						_vtiles[index].object = MAPOBJECT::NONE;
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
	Auto();
}

void MapToolScene::Save()
{
	tagTile saveTile[10001];
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
	tagTile saveTile[10001];
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

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
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

			cout << _vtiles[index].autoIndex << endl;

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
			case 100:
			case 110:
			case 126:
			case 238:
			case 254:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//아래
			case 145:
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
			case 174:
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
			case 222:
			case 236:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른아래
			case 137:
			case 169:
			case 153:
			case 171:
			case 201:
			case 217:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//왼위대각
			case 127:
				_vtiles[index].terrainframeX = 3;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른위대각
			case 239:
				_vtiles[index].terrainframeX = 2;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//왼아래대각
			case 191:
				_vtiles[index].terrainframeX = 1;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른아래 대각
			case 193:
			case 223:
				_vtiles[index].terrainframeX = 0;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//오른쪽대각 1칸
			case 95:
			case 220:
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
			case 111:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

				//가로
			case 10:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 4;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
				//세로
			case 5:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 3;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;

			case 1:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 5;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 2:
				_vtiles[index].terrainframeX = 5;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 4:
				_vtiles[index].terrainframeX = 6;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			case 8:
				_vtiles[index].terrainframeX = 4;
				_vtiles[index].terrainframeY = 6;
				_vtiles[index].terrain = TERRAIN::GRASS;
				break;
			}
		}
	}
}


TERRAIN MapToolScene::TerrainSelect(int frameX, int frameY)
{
	if (frameY == 0 || frameY == 1)					return TERRAIN::DIRT;
	if (frameY == 2 ||(frameX == 6 && frameY == 3))	return TERRAIN::GRASS;
	if (frameY == 3 || frameY == 4 || frameY == 5)	return TERRAIN::BOUNDARY;
	if (frameY == 6)								return TERRAIN::WATER;
	return TERRAIN();
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
