#include "stdafx.h"
#include "CraftManager.h"
#include "AllMap.h"
#include "AllCraft.h"

void CraftManager::Init()
{
}

void CraftManager::Update()
{
	if (_vActiveCraftList.size() == 0)return;

	for (int i = 0; i < _vActiveCraftList.size(); ++i)
	{
		if (_vActiveCraftList[i]->GetName() == "ScareCrowObject")
		{
			_vActiveCraftList[i]->SetImage(IMAGEMANAGER->findImage("ScareCrowObject"));

			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER,
				_vActiveCraftList[i]->GetImage(), 
				_vActiveCraftList[i]->GetPosition().x,
				_vActiveCraftList[i]->GetPosition().y,
				_vActiveCraftList[i]->GetRc().bottom);
		}
	}
}

void CraftManager::render()
{
}

bool CraftManager::Planting(int index, string CraftName)
{

	int centerX = (_map->GetTiles(index).rc.left + _map->GetTiles(index).rc.right) * 0.5;
	int centerY = (_map->GetTiles(index).rc.top + _map->GetTiles(index).rc.bottom) * 0.5;
	Vector2 tileCenter(centerX, centerY);

	if (_map->GetTiles(index).object == MAPOBJECT::HOETILE)
	{
		for (int i = 0; i < _vActiveCraftList.size(); ++i)
		{
			if (_vActiveCraftList[i]->GetSaveIndex() == index)return false;
		}
		if (CraftName == "PasnipSeed")
		{
			_scareCrow = new ScareCrowObject;
			_scareCrow->Init();
			_scareCrow->SetPosition(tileCenter);
			_scareCrow->SavePosIndex(index);
			_vActiveCraftList.push_back(_scareCrow);
			return true;
		}
	}
	return false;
}

void CraftManager::Retrieve(int index)
{
	for (int i = 0; i < _vActiveCraftList.size(); ++i)
	{
		if (_vActiveCraftList[i]->GetSaveIndex() == index)
		{
			//아이템 생성 어캐함?
			_vActiveCraftList.erase(_vActiveCraftList.begin() + i);
			return;
		}
	}
}

bool CraftManager::IsExist(int index)
{
	for (int i = 0; i < _vActiveCraftList.size(); ++i)
	{
		if (index == _vActiveCraftList[i]->GetSaveIndex() && _vActiveCraftList[i]->GetCanHarvest())return false;
		else true;
	}
	return false;
}

string CraftManager::GetCraftName(int idx)
{
	for (int i = 0; i < _vActiveCraftList.size(); ++i)
	{
		if (idx == _vActiveCraftList[i]->GetSaveIndex())
		{
			return _vActiveCraftList[i]->GetName();
		}
	}
	return string();
}

void CraftManager::Save()
{
}

vector<CraftObject*> CraftManager::Load()
{
	return vector<CraftObject*>();
}

void CraftManager::SaveSize()
{
}

void CraftManager::LoadSize()
{
}
