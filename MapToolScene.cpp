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

	SetUp();
	SetSample("Terrain");

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	if (PtInRect(&_terrainBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_crtSelect = CRTSELECT::TERRAINDRAW;
		_currentTile.object = MAPOBJECT::NONE;
		SetSample("Terrain");
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
	if (PtInRect(&_eraserBtn, _ptMouse) && (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
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

	for (int i = 0; i < _vtiles.size(); ++i)
	{
		if (PtInRect(&_vtiles[i].rc, _ptMouse))
		{
			_Line.x = _vtiles[i].rc.left;
			_Line.y = _vtiles[i].rc.top;
		}
	}

	for (int i = 0; i < 15 * 5; ++i)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_Line.x = _sampleTile[i].rc.left;
			_Line.y = _sampleTile[i].rc.top;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SetMap_L();
		_isLeftClick = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isLeftClick = false;
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

	if (_isLeftClick)
	{
		SetMap_L();
	}

	//렉트의 너비, 높이 값이 음수가 될 경우 렉트충돌이 되지않아서
	//상황마다 바꿔준다
	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());
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
}

void MapToolScene::render()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (i < _vtiles.size() && j < _vtiles.size())
			{
				int cullX = CAMERAMANAGER->getL() / TILESIZE;
				int cullY = CAMERAMANAGER->getT() / TILESIZE;

				int index = (i + cullY) * _horizontal + (j + cullX);
				CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Terrain"),
					_vtiles[index].rc.left, _vtiles[index].rc.top,
					_vtiles[index].terrainframeX, _vtiles[index].terrainframeY);
			}
		}
	}

	for (int i = 0; i < _vtiles.size(); ++i)
	{
		if (_vtiles[i].object == MAPOBJECT::NONE)continue;

		int cullyX = _vtiles[i].rc.left / TILESIZE;
		int cullyY = _vtiles[i].rc.top / TILESIZE;

		if (_vtiles[i].object == MAPOBJECT::BUILDING)
		{
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"), _vtiles[i].rc.left - TILESIZE * 8, _vtiles[i].rc.top - TILESIZE * 8, _vtiles[i].objectframeX, _vtiles[i].objectframeY, _vtiles[i].rc.bottom);
		}
	}
	for (int i = 0; i < _vtiles.size(); ++i)
	{
		if (_vtiles[i].object == MAPOBJECT::NONE)continue;

		int cullyX = _vtiles[i].rc.left / TILESIZE;
		int cullyY = _vtiles[i].rc.top / TILESIZE;

		if (_vtiles[i].object != MAPOBJECT::BUILDING)
		{
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"), _vtiles[i].rc.left - TILESIZE, _vtiles[i].rc.top - TILESIZE * 5, _vtiles[i].objectframeX, _vtiles[i].objectframeY, _vtiles[i].rc.bottom);
		}
	}
	ZORDER->ZOrderRender();
	for (int i = 0; i < _vtiles.size(); i++)
	{
		if (_vtiles[i].collision && (KEYMANAGER->isToggleKey(VK_TAB)))
		{
			IMAGEMANAGER->render("Collision", getMemDC(), _vtiles[i].rc.left, _vtiles[i].rc.top);
		}
	}
	IMAGEMANAGER->render("Window", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth(), 0);

	switch (_crtSelect)
	{
	case CRTSELECT::TERRAINDRAW:
		IMAGEMANAGER->render("Terrain", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::TREEDRAW:
		IMAGEMANAGER->render("Tree", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::BUILDINGDRAW:
		IMAGEMANAGER->render("House", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	}

	IMAGEMANAGER->render("Line", getMemDC(), _Line.x, _Line.y);

	Rectangle(getMemDC(), _draw);
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
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.collision = false;

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
		for (int i = 0; i < SampleX; ++i)
		{
			for (int j = 0; j < SampleY; ++j)
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
	for (int i = 0; i < 15 * 5; ++i)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_currentTile.terrainframeX = _sampleTile[i].terrainframeX;
			_currentTile.terrainframeY = _sampleTile[i].terrainframeY;

			_currentTile.terrain = TerrainSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
			_currentTile.object = ObjectSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
			if (_crtSelect == CRTSELECT::BUILDINGDRAW)
			{
				_currentTile.object = MAPOBJECT::BUILDING;
			}

			break;
		}
	}
	for (int i = 0; i < _vtiles.size(); ++i)
	{
		if (PtInRect(&_vtiles[i].rc, _CameraMouse))
		{
			if (_ptMouse.x < WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth())
			{
				if (_crtSelect == CRTSELECT::TERRAINDRAW)
				{
					_vtiles[i].terrainframeX = _currentTile.terrainframeX;
					_vtiles[i].terrainframeY = _currentTile.terrainframeY;

					_vtiles[i].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
				}
				if ((_vtiles[i].terrain != TERRAIN::WATER) && (_vtiles[i].terrain != TERRAIN::WALL) && (!_vtiles[i].collision))
				{
					if (_crtSelect == CRTSELECT::TREEDRAW)
					{
						if (_currentTile.object == MAPOBJECT::TREE1)
						{
							_vtiles[i].objectframeX = 0;
							_vtiles[i].objectframeY = 0;
							_vtiles[i].object = MAPOBJECT::TREE1;
						}
						if (_currentTile.object == MAPOBJECT::TREE2)
						{
							_vtiles[i].objectframeX = 1;
							_vtiles[i].objectframeY = 0;
							_vtiles[i].object = MAPOBJECT::TREE2;
						}
						if (_currentTile.object == MAPOBJECT::TREE3)
						{
							_vtiles[i].objectframeX = 2;
							_vtiles[i].objectframeY = 0;
							_vtiles[i].object = MAPOBJECT::TREE3;
						}
					}
					if (_crtSelect == CRTSELECT::BUILDINGDRAW)
					{
						if (_currentTile.object == MAPOBJECT::BUILDING)
						{
							_vtiles[i].objectframeX = 0;
							_vtiles[i].objectframeY = 0;
							_vtiles[i].object = MAPOBJECT::BUILDING;

						}
					}
				}
				if (_crtSelect == CRTSELECT::ERASER)
				{
					_vtiles[i].objectframeX = NULL;
					_vtiles[i].objectframeY = NULL;

					_vtiles[i].object = MAPOBJECT::NONE;
				}
				if (_crtSelect == CRTSELECT::COLLISION)
				{
					_vtiles[i].collision = false;
				}
			}
		}
	}
}

void MapToolScene::SetMap_R()
{
	for (int i = 0; i < _vtiles.size(); ++i)
	{
		if (isCollision(_vtiles[i].rc, _draw))
		{
			if (_ptMouse.x < WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth())
			{
				if (_crtSelect == CRTSELECT::TERRAINDRAW)
				{
					if (_currentTile.terrain == TERRAIN::DIRT)
					{
						_vtiles[i].terrainframeX = RND->getFromIntTo(0, 7);
						_vtiles[i].terrainframeY = RND->getFromIntTo(0, 2);
						_vtiles[i].terrain = TERRAIN::DIRT;
					}
					else if (_currentTile.terrain == TERRAIN::GRASS)
					{
						_vtiles[i].terrainframeX = RND->getFromIntTo(0, 7);
						_vtiles[i].terrainframeY = 2;
						_vtiles[i].terrain = TERRAIN::GRASS;
					}
					else if (_currentTile.terrain == TERRAIN::WATER)
					{
						_vtiles[i].terrainframeX = RND->getFromIntTo(0, 4);
						_vtiles[i].terrainframeY = 6;
						_vtiles[i].terrain = TERRAIN::WATER;
					}
					else
					{
						_vtiles[i].terrainframeX = _currentTile.terrainframeX;
						_vtiles[i].terrainframeY = _currentTile.terrainframeY;
						_vtiles[i].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);

					}
					//Auto(i);
				}
				if (_crtSelect == CRTSELECT::ERASER)
				{
					_vtiles[i].objectframeX = NULL;
					_vtiles[i].objectframeY = NULL;

					_vtiles[i].object = MAPOBJECT::NONE;
				}

				if (_crtSelect == CRTSELECT::COLLISION)
				{
					_vtiles[i].collision = true;
				}
			}
		}
	}
	_draw = RectMake(0, 0, -1, -1);
}

void MapToolScene::Save()
{
	tagTile saveTile[401];
	for (int i = 0; i < 400; i++)
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
	tagTile saveTile[401];
	HANDLE file;
	DWORD read;

	file = CreateFile("map.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(tagTile) * 400, &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < 400; i++)
	{
		_vtiles[i] = saveTile[i];
	}
}

TERRAIN MapToolScene::TerrainSelect(int frameX, int frameY)
{
	if (frameY == 0 || frameY == 1)return TERRAIN::DIRT;
	if (frameY == 2)return TERRAIN::GRASS;
	if (frameY == 3 || frameY == 4 || frameY == 5)return TERRAIN::BOUNDARY;
	if (frameY == 6)return TERRAIN::WATER;
	return TERRAIN();
}

MAPOBJECT MapToolScene::ObjectSelect(int frameX, int frameY)
{
	if (frameX == 0)return MAPOBJECT::TREE1;
	if (frameX == 1)return MAPOBJECT::TREE2;
	if (frameX == 2)return MAPOBJECT::TREE3;
	if (frameX == 4)return MAPOBJECT::BUILDING;
	return MAPOBJECT();
}
