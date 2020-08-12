#pragma once
#include "stdafx.h"
#include "ToolItem.h"
#include "Pickax.h"
#include "Axe.h"
#include "FishingRod.h"
#include "MiniGame.h"
#include "Homi.h"
#include "WaterSpray.h"
#include "Sickle.h"
#include "Sword.h"


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
	MiniGame* _miniGame;

public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	 
	void Action(string name);
	Vector2 GetImpactIndexCenter(string name);
	Vector2 GetImpactIndexLeft(string name);
	Vector2 GetImpactIndexRight(string name);

	virtual inline void SetImpactIndex(string name, Vector2 index);
	virtual inline void SetImpactIndex(string name, Vector2 Center, Vector2 left, Vector2 right);
	
};

