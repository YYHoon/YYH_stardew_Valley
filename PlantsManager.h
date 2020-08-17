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
	void Save();
	void Load();
	void SaveSize();
	void LoadSize();
	vector<Plants*> GetPlantsList() { return _vActivePlantsList; }

	void SetMapMemoryAddressLinked(MapMain* map) { _map = map; }
};

/// ���� �۹��� �����ɾ�����(3) = 3�Ͽ� ����
// 4  getDay() - ���� ��¥ =  1 
// 5 2