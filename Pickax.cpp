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
	/// <summary>
	_image = IMAGEMANAGER->findImage("Item_Pickaxe");
	/// </summary>
}

void Pickax::Action()
{
	_justSignal = true;
	_mapObject = MAPOBJECT::NONE;
	//�� �μ���
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::ROCK )
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}

	//������ ���ٶ�
	if (_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE||
		_map->GetTiles(_tileIndex[0]).object == MAPOBJECT::HOETILE_WET)
	{
		_map->SetMapObject(_tileIndex[0], MAPOBJECT::NONE);
		_map->SetColl(_tileIndex[0], false);
	}
}

void Pickax::ReAction()
{
}
