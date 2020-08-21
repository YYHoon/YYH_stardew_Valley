#include "stdafx.h"
#include "ScareCrow.h"
#include "AllMap.h"

void ScareCrow::Init()
{
	_name = "ScareCrow";
	_tag = "CraftItem";
	_imageC = IMAGEMANAGER->findImage("ScareCrow");
	_imageI = IMAGEMANAGER->findImage("ScareCrow(64x64)");
	_number = 0;
	_enumName = TOOLS::ACTIVEITEM;
}

void ScareCrow::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;

	if (_number > 0 &&
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE ||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE_WET)
	{


		_number--;
	}

	_justSignal = false;
}

void ScareCrow::ReAction()
{
}
