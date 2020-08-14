#include "stdafx.h"
#include "ToolItemManager.h"
#include "MapMain.h"
ToolItemManager::ToolItemManager()
{
	
}

void ToolItemManager::Init()
{
	if (_axe == nullptr)
	{
		_axe = new Axe;
		//_axe->Init();
		_toolList.push_back(_axe);
	}
	if (_pickax == nullptr)
	{
		_pickax = new Pickax;
		//_pickax->Init();
		_toolList.push_back(_pickax);
	}
	if (_fishingRod == nullptr)
	{
		_fishingRod = new FishingRod;
		//_fishingRod->Init();
		_toolList.push_back(_fishingRod);
	}
	if (_homi == nullptr)
	{
		_homi = new Homi;
		//_homi->Init();
		_toolList.push_back(_homi);
	}
	if (_waterSpray == nullptr)
	{
		_waterSpray = new WaterSpray;
		//_waterSpray->Init();
		_toolList.push_back(_waterSpray);
	}
	if (_sickle == nullptr)
	{
		_sickle = new Sickle;
		//_sickle->Init();
		_toolList.push_back(_sickle);
	}
	if (_sword == nullptr)
	{
		_sword = new Sword;
		//_sword->Init();
		_toolList.push_back(_sword);
	}
	for (int i = 0; i < _toolList.size(); ++i)
	{
		_toolList[i]->SetNowMapMemoryAddressLink(_nowTileMap);
		_toolList[i]->Init();
	}
	for (int i = 0; i < _toolList.size(); ++i)
	{
		_toolList[i]->SetNowMapMemoryAddressLink(_nowTileMap);
		_toolList[i]->Init();
	}
}

void ToolItemManager::Action(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
	
		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->Action();
		}
	
	}
}

int ToolItemManager::GetImpactIndexCenter(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactTileIndexCenter();
		}

	}
	
}

int ToolItemManager::GetImpactIndexLeft(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		
		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactTileIndexLeft();
		}

	}
	
}

int ToolItemManager::GetImpactIndexRight(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactTileIndexRight();
		}

	}
	
}

inline void ToolItemManager::SetImpactIndex(string name, int index)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->SetImpactTileIndex(index);
		}

	}
	
}

inline void ToolItemManager::SetImpactIndex(string name, int Center, int left, int right)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->SetImpactTileIndex(Center,left,right);
		}

	}
}
