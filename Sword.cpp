#include "stdafx.h"
#include "Sword.h"
#include "AllMap.h"

void Sword::Init()
{
	_name = "Sword";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("Sword(64x64)");
	_dmage = 3;
	_enumName = TOOLS::SWORD;
	/// <summary>
	_image = IMAGEMANAGER->findImage("Item_Knife");
	/// </summary>
}

void Sword::Action()
{
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::ENEMY)
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
	if (_map->GetTiles(_tileIndex[1]).object == MAPOBJECT::ENEMY)
		_map->SetMapObject(_tileIndex[1], MAPOBJECT::NONE);
	if (_map->GetTiles(_tileIndex[2]).object == MAPOBJECT::ENEMY)
		_map->SetMapObject(_tileIndex[2], MAPOBJECT::NONE);
}

void Sword::ReAction()
{
}
