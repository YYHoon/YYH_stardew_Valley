#pragma once
#include "stdafx.h"
#include "ToolItem.h"
#include "Pickax.h"
#include "Axe.h"
#include "FishingRod.h"
#include "Homi.h"
#include "WaterSpray.h"
#include "Sickle.h"
#include "Sword.h"
class MapMain;
class DummyMap;

class ToolItemManager
{
private:
	vector<ToolItem*> _toolList;
	Pickax* _pickax;
	Axe* _axe;
	FishingRod* _fishingRod;
	Homi* _homi;
	WaterSpray* _waterSpray;
	Sickle* _sickle;
	Sword* _sword;

	MapMain* _nowTileMap;
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	void Init();
	void Action(string name);
	virtual	int GetImpactIndexCenter(string name);
	virtual	int GetImpactIndexLeft(string name);
	virtual int GetImpactIndexRight(string name);

	
	vector<ToolItem*> GetToolItem() { return _toolList; }
	
	
	virtual inline void SetImpactIndex(string name, int index);
	virtual inline void SetImpactIndex(string name, int Center, int left, int right);
	
	inline void GetNowTileMapMemoyrAddressLink(MapMain* scene) { _nowTileMap = scene; }
	
};

