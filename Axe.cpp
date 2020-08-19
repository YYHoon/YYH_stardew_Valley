#include "stdafx.h"
#include "Axe.h"
#include"AllMap.h"
#include"SpreadItem.h"
Axe::Axe()
{

}

void Axe::Init()
{
	_name = "Axe";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("Axe(64x64)");
	_dmage = 1;
	_enumName = TOOLS::AXE;
	
}

void Axe::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;
	//cout << _map->GetTiles(_tileIndex[0]).hp << endl;

	//큰나무 부술때
	if ((_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE1 ||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE2 ||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE3) &&
		(_map->GetTiles(_tileIndex[0]).hp == 0))
	{
		_spreadItem->Init("Wood(64x64)", _map, _spreadItem->IndexToVector(_map,_tileIndex[0]), RND->getFromIntTo(1,8));
		
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}
	else if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE1 ||
			 _map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE2 ||
			 _map->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE3)
	{
		_map->SetHp(_tileIndex[0], -1);
	}
	//나무가지부술때
	if(_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::BRANCH)
	{
		_spreadItem->Init("Wood(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}

	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::WEED)
	{
		_spreadItem->Init("Wood(64x64)", _map, _spreadItem->IndexToVector(_map, _tileIndex[0]), 1);
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}
}

void Axe::Update()
{
	_spreadItem->Update();
	
}

void Axe::ReAction()
{
}

