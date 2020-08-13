#include "stdafx.h"
#include "MapToolScene.h"

void MapToolScene::Save(string fileName, int mapSizeX, int mapSizeY, vector<tagTile> tile)
{
	tagTile *saveTile = new tagTile[mapSizeX * mapSizeY+1];
	for (int i = 0; i < tile.size(); i++)
	{
		saveTile[i] = tile[i];
	}
	HANDLE file;
	DWORD write;

	file = CreateFile(fileName.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveTile, sizeof(tagTile) * tile.size(), &write, NULL);


	CloseHandle(file);
}

vector<tagTile> MapToolScene::Load(string fileName, int mapSizeX, int mapSizeY)
{
	tagTile* saveTile = new tagTile[mapSizeX * mapSizeY+1];
	HANDLE file;
	DWORD read;
	vector<tagTile> tmp;
	file = CreateFile(fileName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(tagTile) * mapSizeX * mapSizeY, &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < mapSizeX * mapSizeY; i++)
	{
		tmp.push_back( saveTile[i]);
	}
	return tmp;
}
