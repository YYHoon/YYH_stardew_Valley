#include "stdafx.h"
#include "KaleSeed.h"
#include "AllMap.h"

void KaleSeed::Init()
{
	_name = "KaleSeed";
	_tag = "ActItem";
	_imageC = IMAGEMANAGER->findImage("Kale");
	_imageI = IMAGEMANAGER->findImage("Kale(64x64)");
	_number = 0;
	_enumName = TOOLS::ACTIVEITEM;
}

void KaleSeed::Action()
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

void KaleSeed::ReAction()
{
}
