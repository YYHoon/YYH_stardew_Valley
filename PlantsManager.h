#pragma once
#include "gameNode.h"
#include "AllPlants.h"

class MapMain;
class Plants;

class PlantsManager : public gameNode
{
private:
	ParsnipObject* _parsnip;
	PotatoObject* _potato;
	KaleObject* _kale;
	vector<Plants*>				_vActivePlantsList;
	vector<Plants*>::iterator	_viActivePlantsList;
	MapMain* _map;
	int size;

public:
	PlantsManager() {}
	~PlantsManager() {}

	void Init();
	void Update();
	void render();
	void Planting(int index , string plantsName);
	void Growing();
	void Harvesting(int index);
	void SaveSize();
	void LoadSize();
	vector<Plants*> GetPlantsList() { return _vActivePlantsList; }

	void SetMapMemoryAddressLinked(MapMain* map) { _map = map; }
};

/// 현재 작물이 언제심었는지(3) = 3일에 심음
// 4  getDay() - 심은 날짜 =  1 
// 5 2