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
	//타일 팔렛트로 사용할 이미지 등록
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

	//지형 그리자
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//오브젝트 그리자
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//오브젝트가 아니면 그리지 마라
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

	//1. 오늘 실습(?)을 위해 속성을 부여해봅시다.
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain == TR_WATER) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK1) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK3) _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCKS) _attribute[i] |= ATTR_UNMOVE;
	}



	CloseHandle(file);
}
