#include "stdafx.h"
#include "Axe.h"

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
	if (_dummy->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE1 ||
		_dummy->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE2 ||
		_dummy->GetTiles(_tileIndex[0]).object == MAPOBJECT::TREE3)
	{
		cout << (int)_dummy->GetTiles(_tileIndex[0]).object << endl;
		cout << (int)_dummy->GetTiles(_tileIndex[0]).object << endl;
	}
}

void Axe::ReAction()
{
}

