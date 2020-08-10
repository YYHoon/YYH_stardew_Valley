#include "stdafx.h"
#include "tileMap.h"


tileMap::tileMap()
{
}


tileMap::~tileMap()
{
}

HRESULT tileMap::init()
{
	//Ÿ�� �ȷ�Ʈ�� ����� �̹��� ���
	IMAGEMANAGER->addFrameImage("mapTiles", "mapTiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	load();

	return S_OK;
}

void tileMap::release()
{

}

void tileMap::update()
{

}

void tileMap::render()
{

	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//���� �׸���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//������Ʈ �׸���
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//������Ʈ�� �ƴϸ� �׸��� ����
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void tileMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("tankmap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);

	//1. ���� �ǽ�(?)�� ���� �Ӽ��� �ο��غ��ô�.
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain == TR_WATER) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK1) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK3) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCKS) _attribute[i] |= ATTR_UNMOVE;
	}



	CloseHandle(file);
}
