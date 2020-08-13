#include "stdafx.h"
#include "Axe.h"
#include"AllMap.h"
Axe::Axe()
{

}

void Axe::Init()
{
	_name = "Axe";
	_tag = "ToolItem";
	_dmage = 1;

}

void Axe::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE1 ||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE2 ||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE3)
	{
		cout << (int)_map->GetTiles(_tileIndex[0]).object << endl;
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		cout << (int)_map->GetTiles(_tileIndex[0]).object << endl;
	}
}

void Axe::ReAction()
{
}

