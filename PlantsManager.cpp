#include "stdafx.h"
#include "PlantsManager.h"
#include "AllPlants.h"

void PlantsManager::Init()
{
}

void PlantsManager::Update()
{
	

}

void PlantsManager::render()
{
}

void PlantsManager::Planting(int index, string plantsName)
{
	int centerX = (_map->GetTiles(index).rc.left + _map->GetTiles(index).rc.right )* 0.5;
	int centerY = (_map->GetTiles(index).rc.top + _map->GetTiles(index).rc.bottom )* 0.5;
	Vector2 tileCenter(centerX, centerY);

	if (_map->GetTiles(index).object == MAPOBJECT::HOETILE)
	{
		if (plantsName == "parsnip")
		{
			_parsnip = new ParsnipObject;
			_parsnip->Init();		
			_parsnip->SetPosition(tileCenter);
			_parsnip->SetPosIndex(index);
			_vActivePlantsList.push_back(_parsnip);
		}
	}
}

void PlantsManager::Growing()
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (_map->GetTiles(_vActivePlantsList[i]->GetSaveIndex()).wet)
		{
			_vActivePlantsList[i]->ChangeIsWet(true);
		}
	}
}


void PlantsManager::Harvesting(int index)
{
	_viActivePlantsList[index] = _vActivePlantsList[index];
	if (_vActivePlantsList[index]->GetCanHarvest())
	{
		//¾ÆÀÌÅÛ ¾¾»Ñ¸®±â
		_vActivePlantsList[index]->release();
		_vActivePlantsList.erase(_viActivePlantsList);
	}
}
