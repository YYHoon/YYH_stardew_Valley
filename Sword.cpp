#include "stdafx.h"
#include "Sword.h"
#include "AllMap.h"
#include"SpreadItem.h"
void Sword::Init()
{
	_name = "Sword";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("Sword(64x64)");
	_dmage = 3;
	_enumName = TOOLS::SWORD;
}

void Sword::Action()
{
	//if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::ENEMY)
	//	_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
	//if (_map->GetTiles(_tileIndex[1]).object == MAPOBJECT::ENEMY)
	//	_map->SetMapObject(_tileIndex[1], MAPOBJECT::NONE);
	//if (_map->GetTiles(_tileIndex[2]).object == MAPOBJECT::ENEMY)
	//	_map->SetMapObject(_tileIndex[2], MAPOBJECT::NONE);
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::WEED)
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}
	if (_map->GetTiles(_tileIndex[1]).object == MAPOBJECT::WEED)
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[1], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[1], false);
	}
	if (_map->GetTiles(_tileIndex[2]).object == MAPOBJECT::WEED)
	{
		_spreadItem->Init("Weed(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);

		_map->SetMapObject(_tileIndex[2], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[2], false);
	}
}

void Sword::Update()
{
	_spreadItem->Update();
}

void Sword::ReAction()
{
}
