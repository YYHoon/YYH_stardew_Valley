#include "stdafx.h"
#include "PlantsManager.h"
#include "AllPlants.h"

void PlantsManager::Init()
{
}

void PlantsManager::Update()
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
			_ActivePlantsList.push_back(_parsnip);
		}
	}
}

void PlantsManager::Growing()
{
	for (int i = 0; i < _ActivePlantsList.size(); ++i)
	{
		if (_map->GetTiles(_ActivePlantsList[i]->GetSaveIndex()).wet)
		{
			_ActivePlantsList[i]->ChangeIsWet(true);
		}
	}
}


void PlantsManager::Harvesting(int index)
{
	for (int i = 0; i < _ActivePlantsList.size(); ++i)
	{
		if (_ActivePlantsList[i]->GetCanHarvest())
		{
			//class item »Ñ¸®±â
		}
	}

}
