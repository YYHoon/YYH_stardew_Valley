#include "stdafx.h"
#include "Sickle.h"
#include "AllMap.h"

void Sickle::Init()
{
	_name = "Sickle";
	_tag = "name";
	_dmage = 1;
	_enumName = TOOLS::SICKLE;
}

void Sickle::Action()
{
	_slashSignal = true;
	_mapObject = MAPOBJECT::NONE;
	//낫으로 풀베기
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::WEED )
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
	if (_map->GetTiles(_tileIndex[1]).object == MAPOBJECT::WEED )
		_map->SetMapObject(_tileIndex[1], MAPOBJECT::NONE);
	if (_map->GetTiles(_tileIndex[2]).object == MAPOBJECT::WEED )
		_map->SetMapObject(_tileIndex[2], MAPOBJECT::NONE);
	
}

void Sickle::ReAction()
{
}
