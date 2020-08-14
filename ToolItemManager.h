#pragma once
#include "stdafx.h"
#include "AllToolItem.h"

class MapMain;
class DummyMap;

class ToolItemManager
{
private:
	vector<ToolItem*> _toolList;//아이템 모든정보를 담은벡터
	
	//ToolItem 할당
	Pickax* _pickax;
	Axe* _axe;
	FishingRod* _fishingRod;
	Homi* _homi;
	WaterSpray* _waterSpray;
	Sickle* _sickle;
	Sword* _sword;
	//==============

	//ActItem할당
	KaleSeed* _kaleSeed;
	PotatoSeed* _potatoSeed;
	PasnipSeed* _pasnipSeed;
	//===========

	//EatItem할당
	Potato* _potato;
	Pasnip* _pasnip;
	Kale* _kale;
	Sap* _sap;
	NormalFish* _normalFish;
	RareFish* _rareFish;
	//==============

	//ResoureceItem할당
	Rock* _rock;
	Weed* _weed;
	Wood* _wood;
	//================



	MapMain* _nowTileMap; //지금사용하는 맵
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	void Init();
	void Action(string name);

	vector<ToolItem*>GetItemList() { return _toolList; }//아이템목록을 담은 벡터 가져오는 함수

	//이름에 따라 상호작용할 타일인덱스 가져오는 함수
	virtual	int GetImpactIndexCenter(string name);
	virtual	int GetImpactIndexLeft(string name);
	virtual int GetImpactIndexRight(string name);

	
	vector<ToolItem*> GetToolItem() { return _toolList; }
	
	
	//이름에따른 이미지가져오는함수
	virtual image* GetImageInven(string name);
	virtual image* GetImageChar(string name);

	virtual inline void SetImpactIndex(string name, int index);
	virtual inline void SetImpactIndex(string name, int Center, int left, int right);
	
	inline void GetNowTileMapMemoyrAddressLink(MapMain* scene) { _nowTileMap = scene; }
	
};

