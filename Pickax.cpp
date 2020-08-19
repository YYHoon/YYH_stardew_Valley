#include"stdafx.h"
#include "Pickax.h"
#include"AllMap.h"

Pickax::Pickax()
{

}

void Pickax::Init()
{
	_name = "Pickax";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("Pickax(64x64)");
	_dmage = 1;
	_enumName = TOOLS::PICK;
}

void Pickax::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;
	//돌 부술때
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::ROCK )
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
		
		_map->GetTiles(_tileIndex[0]).rc.left;
		EFFECTMANAGER->play("RockDis", _map->GetTiles(_tileIndex[0]).rc.left+32, _map->GetTiles(_tileIndex[0]).rc.top+32);
	}
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::WEED)
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
		EFFECTMANAGER->play("WeedDis", _map->GetTiles(_tileIndex[0]).rc.left + 32, _map->GetTiles(_tileIndex[0]).rc.top + 32);
	}
	//경작지 없앨때
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE_WET)
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
		_map->SetWet(_tileIndex[0], false);
	}
}

void Pickax::ReAction()
{
}
