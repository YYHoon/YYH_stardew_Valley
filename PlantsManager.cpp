#include "stdafx.h"
#include "PlantsManager.h"
#include "AllMap.h"
#include "AllPlants.h"

void PlantsManager::Init()
{
	


}

void PlantsManager::Update()
{
	if (_vActivePlantsList.size() == 0)return;
	if (ENVIRONMENT->GetIsDayIncrease())Growing();
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (_vActivePlantsList[i]->GetName() == "parsnipObject")
		{
			if (_vActivePlantsList[i]->GetGrowCount() >= 4)_vActivePlantsList[i]->SetGrowCount(4);
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("parsnipObject"));
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 4)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x - 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetGrowCount(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
		else if (_vActivePlantsList[i]->GetName() == "kaleObject")
		{
			if(_vActivePlantsList[i]->GetGrowCount() >= 4)_vActivePlantsList[i]->SetGrowCount(4);
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("kaleObject"));
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 4)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x - 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetGrowCount(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
		else if (_vActivePlantsList[i]->GetName() == "potatoObject")
		{
			if (_vActivePlantsList[i]->GetGrowCount() >= 4)_vActivePlantsList[i]->SetGrowCount(5);
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("potatoObject"));
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 5)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x - 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetGrowCount(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
		if (_map->GetTiles()[_vActivePlantsList[i]->GetSaveIndex()].object != MAPOBJECT::HOETILE)
		{
			_viActivePlantsList = _vActivePlantsList.begin() + i;
			_vActivePlantsList.erase(_viActivePlantsList);
		}
	}
}

void PlantsManager::render()
{
}

bool PlantsManager::Planting(int index, string plantsName)
{
	int centerX = (_map->GetTiles(index).rc.left + _map->GetTiles(index).rc.right) * 0.5;
	int centerY = (_map->GetTiles(index).rc.top + _map->GetTiles(index).rc.bottom) * 0.5;
	Vector2 tileCenter(centerX, centerY);

	if (_map->GetTiles(index).object == MAPOBJECT::HOETILE)
	{
		for (int i = 0; i < _vActivePlantsList.size(); ++i)
		{
			if (_vActivePlantsList[i]->GetSaveIndex() == index)return false;
		}
		if (plantsName == "PasnipSeed")
		{
			_parsnip = new ParsnipObject;
			_parsnip->Init();
			_parsnip->SetPosition(tileCenter);
			_parsnip->SavePosIndex(index);
			_vActivePlantsList.push_back(_parsnip);
			return true;
		}
		else if (plantsName == "KaleSeed")
		{
			_kale = new KaleObject;
			_kale->Init();
			_kale->SetPosition(tileCenter);
			_kale->SavePosIndex(index);
			_vActivePlantsList.push_back(_kale);
			return true;
		}
		else if (plantsName == "PotatoSeed")
		{
			_potato = new PotatoObject;
			_potato->Init();
			_potato->SetPosition(tileCenter);
			_potato->SavePosIndex(index);
			_vActivePlantsList.push_back(_potato);
			return true;
		}
	}
	return false;
}

void PlantsManager::Growing()
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (!_map->GetTiles()[_vActivePlantsList[i]->GetSaveIndex()].wet)continue;
		_vActivePlantsList[i]->IncreaseGrowCount(+1);
	}
}


void PlantsManager::Harvesting(int index)
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (_vActivePlantsList[i]->GetCanHarvest() && _vActivePlantsList[i]->GetSaveIndex() == index)
		{
			_vActivePlantsList.erase(_vActivePlantsList.begin() + i);
			return;
		}
	}
}

bool PlantsManager::IsExist(int index)
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (index == _vActivePlantsList[i]->GetSaveIndex() && _vActivePlantsList[i]->GetCanHarvest())return false;
		else true;
	}
}

string PlantsManager::GetPlantsName(int idx)
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (idx == _vActivePlantsList[i]->GetSaveIndex())
		{
			return _vActivePlantsList[i]->GetName();
		}
	}
}

