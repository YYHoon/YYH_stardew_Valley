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

	_tileRender = new TileRender;
	
	_Line.x = -100;
	_Line.y = -100;

	_saveimg = false;
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
	Button();

	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());

	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
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
			if (PtInRect(&_sampleTile[i * 8 + j].rc, _ptMouse)&&(_Window))
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
	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
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
				if ((_vtiles[index].terrainframeX == 1) && (_vtiles[index].terrainframeY == 1))
				{
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Terrain_InDoor"),
						_vtiles[index].rc.left, _vtiles[index].rc.top,
						2, 7, _vtiles[index].rc.bottom);
				}
			}

			if (_count % 40 == 0)
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

	for (int i = 0; i < ClIPPINGY+8; i++)
	{
		for (int j = 0; j < ClIPPINGX + 9; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			if (index > 50*50)continue;
			if (i > 0) index = index - 1;
			if (_vtiles[index].object == MAPOBJECT::NONE)continue;

			if (_inout == INOUT::OUTDOOR)
			{
				if (_vtiles[index].object == MAPOBJECT::BUILDING)
				{
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("House"),
						_vtiles[index].rc.left - TILESIZE * 8, _vtiles[index].rc.top - TILESIZE * 8,
						_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom - 128);
				}
				if ((_vtiles[index].object == MAPOBJECT::TREE1) ||
					(_vtiles[index].object == MAPOBJECT::TREE2) ||
					(_vtiles[index].object == MAPOBJECT::TREE3))
				{
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Tree"),
						_vtiles[index].rc.left - TILESIZE, _vtiles[index].rc.top - TILESIZE * 5,
						_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom);
				}
				if (_vtiles[index].object == MAPOBJECT::ROCK ||
					_vtiles[index].object == MAPOBJECT::WEED ||
					_vtiles[index].object == MAPOBJECT::BRANCH ||
					_vtiles[index].object == MAPOBJECT::HOETILE)
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
				if (_vtiles[index].wet && _vtiles[index].object == MAPOBJECT::HOETILE)
				{
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("HoeTile"),
						_vtiles[index].rc.left, _vtiles[index].rc.top,
						_vtiles[index].wetframeX, _vtiles[index].wetframeY);
				}
			}
			else
			{
				if (_vtiles[index].object == MAPOBJECT::BED)
				{
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("Bed"),
						_vtiles[index].rc.left- TILESIZE, _vtiles[index].rc.top- TILESIZE*2+32,
						_vtiles[index].objectframeX, _vtiles[index].objectframeY);
					ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, IMAGEMANAGER->findImage("Blanket"),
						_vtiles[index].rc.left - TILESIZE , _vtiles[index].rc.top-TILESIZE*2+32,
						_vtiles[index].objectframeX, _vtiles[index].objectframeY, _vtiles[index].rc.bottom+64);
				}
			}
		}
	}

	ZORDER->ZOrderRender();

	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				if (_vtiles[index].collision)
				{
					CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Collision"), _vtiles[index].rc.left, _vtiles[index].rc.top);
				}
				switch (_vtiles[index].pos)
				{
				case POS::PARM_TO_HOME:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 0, 1);
					break;
				case POS::PARM_TO_CAVE:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 1, 1);
					break;
				case POS::HOME_TO_PARM:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 2, 1);
					break;
				case POS::CAVE_TO_PARM:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 3, 1);
					break;
				case POS::ENEMY:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 1, 0);
					break;
				case POS::NPC:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 2, 0);
					break;
				case POS::BED:
					CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage("POS"), _vtiles[index].rc.left, _vtiles[index].rc.top, 3, 0);
					break;
				}
			}
			if (isCollision(_vtiles[index].rc, _draw))
			{
				CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"), _vtiles[index].rc.left, _vtiles[index].rc.top);
			}
		}
	}

	if (_Window)
	{
		IMAGEMANAGER->render("Window", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth(), 0);
		IMAGEMANAGER->render("F1", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("F1")->getWidth()-700, 100);
	}
	else
	{
		IMAGEMANAGER->render("F1", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("F1")->getWidth(), 100);
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
		if (_inout == INOUT::OUTDOOR) IMAGEMANAGER->render("Tree", getMemDC(), _sampleArea.left, _sampleArea.top);
		else IMAGEMANAGER->render("Bed", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::BUILDINGDRAW:
		IMAGEMANAGER->render("House", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	case CRTSELECT::COLLISION:
		IMAGEMANAGER->render("POS", getMemDC(), _sampleArea.left, _sampleArea.top);
		break;
	}

	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("Line"), _Line.x, _Line.y);

	if (_saveimg)
	{
		IMAGEMANAGER->render("Save", getMemDC(), WINSIZEX * 0.5 - 114, WINSIZEY * 0.5 - 26);
	}
	_Mouse->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
}

void MapToolScene::SetUp()
{
	_vtiles.clear();

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 50 * TILESIZE - WINSIZEX, 49 * TILESIZE - WINSIZEY);

	_currentTile.terrainframeX = 1;
	_currentTile.terrainframeY = 2;
	_currentTile.terrain = TERRAIN::GRASS;

	_inout = INOUT::OUTDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW;

	_vertical = 50;
	_horizontal = 50;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = RND->getFromIntTo(0, 6);
			if (RND->getInt(10) == 0) tile.terrainframeY = 1;
			else tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.wetframeX = 0;
			tile.wetframeY = 3;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.wet = false;
			tile.autoIndex = 0;
			tile.autoIndex_2 = 0;
			tile.hp = 0;
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
	case CRTSELECT::COLLISION:
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
		if (_inout == INOUT::OUTDOOR)
		{
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
		}
		else
		{
			_sampleTile[0].terrainframeX = 0;
			_sampleTile[0].terrainframeY = 0;

			_sampleTile[0].rc = RectMake(
				_sampleArea.left,
				_sampleArea.top,
				TILESIZE * 2,
				TILESIZE * 3);
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

	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZE * Horizontal - WINSIZEX, TILESIZE * (Vertical-13));

	_horizontal = Horizontal;
	_vertical = Vertical;

	for (int i = 0; i < _vertical; ++i)
	{
		for (int j = 0; j < _horizontal; ++j)
		{
			tagTile tile;
			tile.terrainframeX = RND->getFromIntTo(0, 6);
			if (RND->getInt(10) == 0) tile.terrainframeY = 1;
			else tile.terrainframeY = 0;
			tile.objectframeX = 0;
			tile.objectframeY = 0;
			tile.wetframeX = 0;
			tile.wetframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.wet = false;
			tile.hp = 0;
			tile.autoIndex = 0;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_vtiles.push_back(tile);
		}
	}
	_inout = INOUT::OUTDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW;


	_currentTile.terrainframeX = 1;
	_currentTile.terrainframeY = 2;
	_currentTile.terrain = TERRAIN::GRASS;
}

void MapToolScene::OutToIn(int Horizontal, int Vertical)
{
	_vtiles.clear();
	
	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZE * Horizontal - WINSIZEX, TILESIZE * (Vertical-23));

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
			tile.wetframeX = 0;
			tile.wetframeY = 0;
			tile.terrain = TERRAIN::DIRT;
			tile.object = MAPOBJECT::NONE;
			tile.pos = POS::NONE;
			tile.collision = false;
			tile.wet = false;
			tile.autoIndex = 0;
			tile.hp = 0;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);

			_vtiles.push_back(tile);
		}
	}
	_inout = INOUT::INDOOR;
	_crtSelect = CRTSELECT::TERRAINDRAW_INDOOR;

	_currentTile.terrainframeX = 0;
	_currentTile.terrainframeY = 5;
}

void MapToolScene::SetMap_L()
{
	POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());
	for (int i = 0; i < 15 * 8; ++i)
	{
		if (_Window)
		{
			if (PtInRect(&_sampleTile[i].rc, _ptMouse))
			{
				_currentTile.terrainframeX = _sampleTile[i].terrainframeX;
				_currentTile.terrainframeY = _sampleTile[i].terrainframeY;

				_currentTile.terrain = TerrainSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
				_currentTile.object = ObjectSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
				if (_crtSelect == CRTSELECT::COLLISION)
				{
					_currentTile.pos = PosSelect(_sampleTile[i].terrainframeX, _sampleTile[i].terrainframeY);
				}
				break;
			}
		}
	}
	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);

			if (PtInRect(&_vtiles[index].rc, _CameraMouse))
			{
				if ((_ptMouse.x > WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth()) && (_Window))continue;
				
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

					_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
					_vtiles[index].collision = true;
				}

				if ((_vtiles[index].terrain != TERRAIN::WATER) && (!_vtiles[index].collision))
				{
					if (_crtSelect == CRTSELECT::TREEDRAW)
					{
						if (_inout == INOUT::OUTDOOR)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
							_vtiles[index].collision = true;
							_vtiles[index].hp = 5;
						}
						else
						{
							_vtiles[index].objectframeX = 0;
							_vtiles[index].objectframeY = 0;
							_vtiles[index].object = MAPOBJECT::BED;
							_vtiles[index].pos = POS::BED;
						}
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
								if ((i == 0) && (j > 1 && j < 5) || (i == 1) && (j > 0 && j < 8))continue;
								_vtiles[index - _vertical * i - j].collision = true;
								_vtiles[index - _vertical * 2 - 3].pos = POS::PARM_TO_HOME;
							}
						}
					}

					if (_vtiles[index].terrain != TERRAIN::DIRT)return;

					if (_crtSelect == CRTSELECT::HOETILEDRAW)
					{
						if (_currentTile.object == MAPOBJECT::HOETILE)
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
						}
						if ((_currentTile.object != MAPOBJECT::HOETILE) && (_currentTile.object != MAPOBJECT::HOETILE_WET))
						{
							_vtiles[index].objectframeX = _currentTile.terrainframeX;
							_vtiles[index].objectframeY = _currentTile.terrainframeY;
							_vtiles[index].object = ObjectSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
							_vtiles[index].collision = true;
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
					switch (_currentTile.pos)
					{
					case POS::COLLISION:
						_vtiles[index].collision = false;
						break;
					case POS::PARM_TO_HOME:
						_vtiles[index].pos = POS::PARM_TO_HOME;
						break;
					case POS::PARM_TO_CAVE:
						_vtiles[index].pos = POS::PARM_TO_CAVE;
						break;
					case POS::HOME_TO_PARM:
						_vtiles[index].pos = POS::HOME_TO_PARM;
						break;
					case POS::CAVE_TO_PARM:
						_vtiles[index].pos = POS::CAVE_TO_PARM;
						break;
					case POS::BED:
						_vtiles[index].pos = POS::BED;
						break;
					case POS::NPC:
						_vtiles[index].pos = POS::NPC;
						break;
					case POS::ENEMY:
						_vtiles[index].pos = POS::ENEMY;
						break;
					case POS::NONE:
						_vtiles[index].pos = POS::NONE;
						break;
					}
				}
			}
		}
	}
}

void MapToolScene::SetMap_R()
{
	for (int i = 0; i < ClIPPINGY; i++)
	{
		for (int j = 0; j < ClIPPINGX; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;

			int index = (i + cullY) * _horizontal + (j + cullX);
			_vtiles[index].autoIndex = 0;

			if (isCollision(_vtiles[index].rc, _draw))
			{
				if ((_ptMouse.x > WINSIZEX - IMAGEMANAGER->findImage("Window")->getWidth()) && (_Window))continue;
				if (_crtSelect == CRTSELECT::TERRAINDRAW)
				{
					if (_inout == INOUT::OUTDOOR)
					{
						if (_currentTile.terrain == TERRAIN::DIRT)
						{
							if (_vtiles[index].collision)
							{
								_vtiles[index].collision = false;
							}
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 6);
							if (RND->getInt(10) == 0) _vtiles[index].terrainframeY = 1;
							else _vtiles[index].terrainframeY = 0;
							_vtiles[index].terrain = TERRAIN::DIRT;
						}
						else if (_currentTile.terrain == TERRAIN::GRASS)
						{
							if (_vtiles[index].terrain == TERRAIN::WATER)
							{
								_vtiles[index].object = MAPOBJECT::NONE;
								_vtiles[index].collision = false;
							}
							if (_vtiles[index].object == MAPOBJECT::HOETILE)
							{
								_vtiles[index].object = MAPOBJECT::NONE;
								_vtiles[index].objectframeX = NULL;
								_vtiles[index].objectframeY = NULL;
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
					else
					{
						_vtiles[index].terrainframeX = _currentTile.terrainframeX;
						_vtiles[index].terrainframeY = _currentTile.terrainframeY;
						_vtiles[index].terrain = TerrainSelect(_currentTile.terrainframeX, _currentTile.terrainframeY);
					}
				}
				if (_crtSelect == CRTSELECT::TREEDRAW)
				{
					if (_vtiles[index].object == MAPOBJECT::NONE &&
						RND->getInt(10) == 0)
					{
						_vtiles[index].objectframeX =RND->getInt(3) ;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::TREE1;
						_vtiles[index].collision = true;
					}
				}
				if (_crtSelect == CRTSELECT::HOETILEDRAW)
				{
					if (_currentTile.object != MAPOBJECT::HOETILE &&
						_currentTile.object != MAPOBJECT::HOETILE_WET)
					{
						if (_vtiles[index].terrain == TERRAIN::DIRT)
						{
							switch (RND->getInt(5))
							{
							case 0:
								_vtiles[index].objectframeX = RND->getFromIntTo(5, 7);
								_vtiles[index].objectframeY = 0;
								_vtiles[index].object = MAPOBJECT::ROCK;
								_vtiles[index].collision = true;
								break;
							case 1:
								_vtiles[index].objectframeX = RND->getFromIntTo(5, 7);
								_vtiles[index].objectframeY = 1;
								_vtiles[index].object = MAPOBJECT::BRANCH;
								_vtiles[index].collision = true;
								break;
							case 2:
								if (RND->getInt(2) == 0)
								{
									_vtiles[index].objectframeX = RND->getFromIntTo(5, 7);
									_vtiles[index].objectframeY = 2;
									_vtiles[index].object = MAPOBJECT::WEED;
									_vtiles[index].collision = true;
								}
								else
								{
									_vtiles[index].objectframeX = 6;
									_vtiles[index].objectframeY = 3;
									_vtiles[index].object = MAPOBJECT::WEED;
									_vtiles[index].collision = true;
								}
								break;
							}
						}
					}
					else
					{
						_vtiles[index].objectframeX = 0;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::HOETILE;
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
					if (_currentTile.pos == POS::COLLISION)
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


TERRAIN MapToolScene::TerrainSelect(int frameX, int frameY)
{
	if (_inout == INOUT::OUTDOOR)
	{
		if (frameY == 2)return TERRAIN::GRASS;

		if (frameY <= 2 && frameX <= 5)		return TERRAIN::DIRT;
		else if (frameY == 6 && frameX <= 3)return TERRAIN::WATER;
		else								return TERRAIN::GRASS;
	}
	else
	{
		TERRAIN::WOODEN;
	}
}

MAPOBJECT MapToolScene::ObjectSelect(int frameX, int frameY)
{
	if (_inout == INOUT::OUTDOOR)
	{
		switch (_crtSelect)
		{
		case CRTSELECT::WALLDRAW:
			if (frameX >= 4 && (frameY <= 2))return MAPOBJECT::WALL;
			else return MAPOBJECT::WALL;
			break;
		case CRTSELECT::HOETILEDRAW:
			if (frameX <= 4 && frameY <= 2)	 return MAPOBJECT::HOETILE;
			if (frameX == 5 && frameY == 3)	 return MAPOBJECT::HOETILE;
			if (frameX <= 4 && frameY >= 3)	 return MAPOBJECT::HOETILE_WET;
			if (frameX == 5 && frameY == 4)	 return MAPOBJECT::HOETILE_WET;
			if (frameX >= 5 && (frameY == 0))return MAPOBJECT::ROCK;
			if (frameX >= 5 && (frameY == 1))return MAPOBJECT::BRANCH;
			if (frameX >= 5 && (frameY == 2))return MAPOBJECT::WEED;
			if (frameX == 6 && (frameY == 3))return MAPOBJECT::WEED;
			break;
		case CRTSELECT::TREEDRAW:
			if (frameX == 0)return MAPOBJECT::TREE1;
			if (frameX == 1)return MAPOBJECT::TREE2;
			if (frameX == 2)return MAPOBJECT::TREE3;
			break;
		case CRTSELECT::BUILDINGDRAW:
			if (frameX == 0)return MAPOBJECT::BUILDING;
			break;
		case CRTSELECT::ENEMYDRAW:
			break;
		}
	}
	else
	{
		switch (_crtSelect)
		{
		case CRTSELECT::WALLDRAW:
			break;
		case CRTSELECT::HOETILEDRAW:
			break;
		case CRTSELECT::TREEDRAW:
			if (frameX == 0 && frameY == 0) MAPOBJECT::BED;
			break;
		case CRTSELECT::BUILDINGDRAW:
			if (frameX == 0)return MAPOBJECT::BUILDING;
			break;
		case CRTSELECT::ENEMYDRAW:
			break;
		}
	}
	return MAPOBJECT();
}

POS MapToolScene::PosSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)return POS::COLLISION;
	if (frameX == 1 && frameY == 0)return POS::ENEMY;
	if (frameX == 2 && frameY == 0)return POS::NPC;
	if (frameX == 3 && frameY == 0)return POS::BED;
	if (frameX == 0 && frameY == 1)return POS::PARM_TO_HOME;
	if (frameX == 1 && frameY == 1)return POS::PARM_TO_CAVE;
	if (frameX == 2 && frameY == 1)return POS::HOME_TO_PARM;
	if (frameX == 3 && frameY == 1)return POS::CAVE_TO_PARM;
}
