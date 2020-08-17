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

/// ���� �۹��� �����ɾ�����(3) = 3�Ͽ� ����
// 4  getDay() - ���� ��¥ =  1 
// 5 2