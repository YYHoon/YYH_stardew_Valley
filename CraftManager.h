#pragma once
#include "gameNode.h"

class MapMain;
class CraftObject;

class CraftManager : public gameNode
{
private:
	CraftObject* _scareCrow;
	MapMain* _map;

	vector<CraftObject*>			_vActiveCraftList;
	vector<CraftObject*>::iterator	_viActiveCraftList;
public:
	CraftManager() {};
	~CraftManager() {};

	void Init();
	void Update();
	void render();
	bool Planting(int index, string CraftName);
	void Retrieve(int index);
	bool IsExist(int index);
	string GetCraftName(int idx);
	void Save();
	vector<CraftObject*> Load();
	void SaveSize();
	void LoadSize();
	vector<CraftObject*> GetPCraftObjectList() { return _vActiveCraftList; }
	void SetPlantsList(vector<CraftObject*> vP) { _vActiveCraftList = vP; }

	void SetMapMemoryAddressLinked(MapMain* map) { _map = map; }
};

