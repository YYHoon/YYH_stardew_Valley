#pragma once
#include "gameNode.h"
#include "AllPlants.h"
#include "MapMain.h"

class MAPMain;

class PlantsManager : public gameNode
{
private:
	ParsnipObject* _parsnip;
	vector<Plants*> _ActivePlantsList;
	MapMain* _map;
	

public:
	PlantsManager() {}
	~PlantsManager() {}

	void Init();
	void Update();
	void Planting(int index , string plantsName);
	void Growing();
	void Harvesting(int index);

	vector<Plants*> GetPlantsList() { return _ActivePlantsList; }

	void SetMapMemoryAddressLinked(MapMain* map) { _map = map; }
};

/// 현재 작물이 언제심었는지(3) = 3일에 심음
// 4  getDay() - 심은 날짜 =  1 
// 5 2