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
	if (_axe == nullptr)				//0
	{
		_axe = new Axe;
		_toolList.push_back(_axe);
	}
	if (_pickax == nullptr)				//1
	{
		_pickax = new Pickax;
		_toolList.push_back(_pickax);
	}
	if (_fishingRod == nullptr)			//2
	{
		_fishingRod = new FishingRod;
		_toolList.push_back(_fishingRod);
	}
	if (_homi == nullptr)				//3
	{
		_homi = new Homi;
		_toolList.push_back(_homi);
	}
	if (_waterSpray == nullptr)			//4
	{
		_waterSpray = new WaterSpray;
		_toolList.push_back(_waterSpray);
	}
	if (_sickle == nullptr)				//5
	{
		_sickle = new Sickle;
		_toolList.push_back(_sickle);
	}
	if (_sword == nullptr)				//6
	{
		_sword = new Sword;
		_toolList.push_back(_sword);
	}
	//ToolItem==================================

	//EatItem===================================
	if (_pasnip == nullptr)				//7
	{
		_pasnip = new Pasnip;
		_toolList.push_back(_pasnip);
	}
	if (_potato == nullptr)				//8
	{
		_potato = new Potato;
		_toolList.push_back(_potato);
	}
	if (_kale == nullptr)				//9
	{
		_kale = new Kale;
		_toolList.push_back(_kale);
	}
	if (_normalFish == nullptr)			//10
	{
		_normalFish = new NormalFish;
		_toolList.push_back(_normalFish);
	}
	if (_rareFish == nullptr)			//11
	{
		_rareFish = new RareFish;
		_toolList.push_back(_rareFish);
	}
	if (_sap == nullptr)				//12
	{
		_sap = new Sap;
		_toolList.push_back(_sap);
	}
	if (_grilledFish == nullptr)		//13
	{
		_grilledFish = new GrilledFish;
		_toolList.push_back(_grilledFish);
	}
	if (_rawFish == nullptr)			//14
	{
		_rawFish = new RawFish;
		_toolList.push_back(_rawFish);
	}
	if (_salad == nullptr)				//15
	{
		_salad = new Salad;
		_toolList.push_back(_salad);
	}
	//EatItem====================================

	//ActItem====================================
	if (_pasnipSeed == nullptr)			//16
	{
		_pasnipSeed = new PasnipSeed;
		_toolList.push_back(_pasnipSeed);
	}
	if (_potatoSeed == nullptr)			//17
	{
		_potatoSeed = new PotatoSeed;
		_toolList.push_back(_potatoSeed);
	}
	if (_kaleSeed == nullptr)			//18
	{
		_kaleSeed = new KaleSeed;
		_toolList.push_back(_kaleSeed);
	}
	//ActItem====================================


	//ResoureceItem================================
	if (_rock == nullptr)				//19
	{
		_rock = new Rock;
		_toolList.push_back(_rock);
	}
	if (_weed == nullptr)				//20
	{
		_weed = new Weed;
		_toolList.push_back(_weed);
	}
	if (_wood == nullptr)				//21
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
