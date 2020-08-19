#include "stdafx.h"
#include "Sickle.h"
#include "AllMap.h"
#include"SpreadItem.h"
void Sickle::Init()
{
	_name = "Sickle";
	_tag = "name";
	_imageI = IMAGEMANAGER->findImage("Sickle(64x64)");
	_dmage = 1;
	_enumName = TOOLS::SICKLE;
}

void Sickle::Action()
{
	_slashSignal = true;
	_mapObject = MAPOBJECT::NONE;
	//낫으로 풀베기
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::WEED)
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}
	if (_map->GetTiles(_tileIndex[1]).object == MAPOBJECT::WEED )
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[1], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[1], false);
	}
	if (_map->GetTiles(_tileIndex[2]).object == MAPOBJECT::WEED )
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[2], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[2], false);
	}
}

void Sickle::Update()
{
	_spreadItem->Update();
}

void Sickle::ReAction()
{
}
