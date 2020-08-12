#include "stdafx.h"
#include "ToolItemManager.h"

ToolItemManager::ToolItemManager()
{
	if (_axe == nullptr)
	{
		_axe = new Axe;
		_axe->Init();
		_toolList.push_back(_axe);
	}
	if (_pickax == nullptr)
	{
		_pickax = new Pickax;
		_pickax->Init();
		_toolList.push_back(_pickax);
	}
	if (_fishingRod == nullptr)
	{
		_fishingRod = new FishingRod;
		_fishingRod->Init();
		_toolList.push_back(_fishingRod);
	}
	if (_homi == nullptr)
	{
		_homi = new Homi;
		_homi->Init();
		_toolList.push_back(_homi);
	}
	if (_waterSpray == nullptr)
	{
		_waterSpray = new WaterSpray;
		_waterSpray->Init();
		_toolList.push_back(_waterSpray);
	}
	if (_sickle == nullptr)
	{
		_sickle = new Sickle;
		_sickle->Init();
		_toolList.push_back(_sickle);
	}
	if (_sword == nullptr)
	{
		_sword = new Sword;
		_sword->Init();
		_toolList.push_back(_sword);
	}
	if (_miniGame == nullptr)
	{
		_miniGame = new MiniGame;
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

Vector2 ToolItemManager::GetImpactIndexCenter(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactIndexCenter();
		}

	}
	
}

Vector2 ToolItemManager::GetImpactIndexLeft(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		
		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactIndexLeft();
		}

	}
	
}

Vector2 ToolItemManager::GetImpactIndexRight(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImpactIndexRight();
		}

	}
	
}

inline void ToolItemManager::SetImpactIndex(string name, Vector2 index)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->SetImpactIndex(index);
		}

	}
	
}

inline void ToolItemManager::SetImpactIndex(string name, Vector2 Center, Vector2 left, Vector2 right)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->SetImpactIndex(Center,left,right);
		}

	}
}
