#include "stdafx.h"
#include "PasnipSeed.h"
#include "AllMap.h"

void PasnipSeed::Init()
{
	_name = "PasnipSeed";
	_tag = "ActItem";
	_imageI = IMAGEMANAGER->findImage("PasnipSeed(64x64)");
	_imageC= IMAGEMANAGER->findImage("PasnipSeed");
	_number = 0;
}

void PasnipSeed::Action()
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

void PasnipSeed::ReAction()
{
}
