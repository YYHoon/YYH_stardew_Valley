#include "stdafx.h"
#include "WaterSpray.h"
#include "AllMap.h"

void WaterSpray::Init()
{
	_name = "WaterSpray";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("WaterSpray(56x56)");
	_dmage = 0;
	_enumName = TOOLS::WATERING_CAN;
}

void WaterSpray::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;
	_mapTeeain = TERRAIN::NONE;
	//돌 부술때
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE)
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::HOETILE_WET);
	}

}

void WaterSpray::ReAction()
{
}
