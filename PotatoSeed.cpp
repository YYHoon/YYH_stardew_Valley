#include "stdafx.h"
#include "PotatoSeed.h"
#include "AllMap.h"

void PotatoSeed::Init()
{
	_name = "PotatoSeed";
	_tag = "ActItem";
	_imageI = IMAGEMANAGER->findImage("PotatoSeed(64x64)");
	_imageC = IMAGEMANAGER->findImage("PotatoSeed");
	_number = 0;
}

void PotatoSeed::Action()
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

void PotatoSeed::ReAction()
{
}
