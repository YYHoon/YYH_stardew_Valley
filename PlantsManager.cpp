#include "stdafx.h"
#include "PlantsManager.h"
#include "AllMap.h"

void PlantsManager::Init()
{
}

void PlantsManager::Update()
{
	//하루지나면
	if(KEYMANAGER->isOnceKeyDown(VK_F1))Growing();
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		_vActivePlantsList[i]->Update();
	}
}

void PlantsManager::render()
{
}

void PlantsManager::Planting(int index, string plantsName)
{
	int centerX = (_map->GetTiles(index).rc.left + _map->GetTiles(index).rc.right )* 0.5;
	int centerY = (_map->GetTiles(index).rc.top + _map->GetTiles(index).rc.bottom )* 0.5;
	Vector2 tileCenter(centerX, centerY);

	if (_map->GetTiles(index).terrain == TERRAIN::DIRT)
	{
		if (plantsName == "parsnipObject")
		{
			_parsnip = new ParsnipObject;
			_parsnip->Init();		
			_parsnip->SetPosition(tileCenter);
			_parsnip->SavePosIndex(index);
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
			_vActivePlantsList[i]->IncreaseGrowCount(+1);
		}
	}
}


void PlantsManager::Harvesting(int index)
{
	_viActivePlantsList[index] = _vActivePlantsList[index];
	if (_vActivePlantsList[index]->GetCanHarvest())
	{
		_vActivePlantsList[index]->release();
		_vActivePlantsList.erase(_viActivePlantsList);
		//아이탬매니저 아이탬생성
	}
}

void PlantsManager::SaveSize()
{
	size = _vActivePlantsList.size();
	HANDLE file;
	DWORD write;

	file = CreateFile(("mapsize.size"), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &size, sizeof(int), &write, NULL);

	CloseHandle(file);
}

void PlantsManager::LoadSize()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(("mapsize.size"), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &size, sizeof(int), &read, NULL);

	CloseHandle(file);
	cout << size << endl;
}
