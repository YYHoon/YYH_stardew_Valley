#include "stdafx.h"
#include "ToolItemManager.h"
#include "MapMain.h"
#include "SpreadItem.h"
ToolItemManager::ToolItemManager()
{
	
}
//매니저 item 매니저 tools 매니저 seed 
void ToolItemManager::Init()

{
	//ToolItem=================================ㄱ
	if (_axe == nullptr)
	{
		_axe = new Axe;
		_toolList.push_back(_axe);
	}
	if (_pickax == nullptr)
	{
		_pickax = new Pickax;
		_toolList.push_back(_pickax);
	}
	if (_fishingRod == nullptr)
	{
		_fishingRod = new FishingRod;
		_toolList.push_back(_fishingRod);
	}
	if (_homi == nullptr)
	{
		_homi = new Homi;
		_toolList.push_back(_homi);
	}
	if (_waterSpray == nullptr)
	{
		_waterSpray = new WaterSpray;
		_toolList.push_back(_waterSpray);
	}
	if (_sickle == nullptr)
	{
		_sickle = new Sickle;
		_toolList.push_back(_sickle);
	}
	if (_sword == nullptr)
	{
		_sword = new Sword;
		_toolList.push_back(_sword);
	}
	//ToolItem=================================

	//EatItem====================================
	if (_pasnip == nullptr)
	{
		_pasnip = new Pasnip;
		_toolList.push_back(_pasnip);
	}
	if (_potato == nullptr)
	{
		_potato = new Potato;
		_toolList.push_back(_potato);
	}
	if (_kale == nullptr)
	{
		_kale = new Kale;
		_toolList.push_back(_kale);
	}
	if (_normalFish == nullptr)
	{
		_normalFish = new NormalFish;
		_toolList.push_back(_normalFish);
	}
	if (_rareFish == nullptr)
	{
		_rareFish = new RareFish;
		_toolList.push_back(_rareFish);
	}
	if (_sap == nullptr)
	{
		_sap = new Sap;
		_toolList.push_back(_sap);
	}
	//EatItem====================================

	//ActItem====================================
	if (_pasnipSeed == nullptr)
	{
		_pasnipSeed = new PasnipSeed;
		_toolList.push_back(_pasnipSeed);
	}
	if (_potatoSeed == nullptr)
	{
		_potatoSeed = new PotatoSeed;
		_toolList.push_back(_potatoSeed);
	}
	if (_kaleSeed == nullptr)
	{
		_kaleSeed = new KaleSeed;
		_toolList.push_back(_kaleSeed);
	}
	if (_scareCrow == nullptr)
	{
		_scareCrow = new ScareCrow;
		_toolList.push_back(_scareCrow);
	}
	//ActItem====================================


	//ResoureceItem================================
	if (_rock == nullptr)
	{
		_rock = new Rock;
		_toolList.push_back(_rock);
	}
	if (_weed == nullptr)
	{
		_weed = new Weed;
		_toolList.push_back(_weed);
	}
	if (_wood == nullptr)
	{
		_wood = new Wood;
		_toolList.push_back(_wood);
	}
	//ResoureceItem================================

	_spreadItem = new SpreadItem;
	for (int i = 0; i < _toolList.size(); ++i)
	{
		_toolList[i]->SetNowMapMemoryAddressLink(_nowTileMap);
		_toolList[i]->SetSpreadItem(_spreadItem);
		_toolList[i]->SetPlayerAddress(_player);
		//_toolList[i]->SetSpreadInToolMemory(tosstool);
		_toolList[i]->Init();
	}

}

void ToolItemManager::Action(string name)
{
	//_spreadList = _spreadItem->GetSpreadItemList();
	for (int i = 0; i < _toolList.size(); ++i)
	{
		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->Action();
		}
	}
}

void ToolItemManager::Update()
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		_toolList[i]->Update();
	}
}

void ToolItemManager::Render(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		if (_toolList[i]->GetName() == name)
		{
			_toolList[i]->ReAction();
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

void ToolItemManager::SetFishingInfo(Vector2 c, PLAYER_DIRECTION d)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == "FishingRod")
		{
			_toolList[i]->SetPlayerCenterNDir(c, d);
		}

	}
	
}

image* ToolItemManager::GetImageInven(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImageInven();
		}

	}
}

image* ToolItemManager::GetImageChar(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == name)
		{
			return _toolList[i]->GetImageChar();
		}

	}
}

FISHING ToolItemManager::GetDoingFishing()
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == "FishingRod")
		{
			return _toolList[i]->GetDoingFishing();
		}

	}
}

void ToolItemManager::SetDoingFishing(FISHING tf)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == "FishingRod")
		{
			return _toolList[i]->SetDoingFishing(tf);
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

bool ToolItemManager::GetNowFishing()
{
	for (int i = 0; i < _toolList.size(); ++i)
	{

		if (_toolList[i]->GetName() == "FishingRod")
		{
			return _toolList[i]->GetTileChangeSignalJust();
		}

	}
}
