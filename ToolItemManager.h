#pragma once
#include "stdafx.h"
#include "AllToolItem.h"

class MapMain;
class DummyMap;

class ToolItemManager
{
private:
	vector<ToolItem*> _toolList;//������ ��������� ��������
	
	//ToolItem �Ҵ�
	Pickax* _pickax;
	Axe* _axe;
	FishingRod* _fishingRod;
	Homi* _homi;
	WaterSpray* _waterSpray;
	Sickle* _sickle;
	Sword* _sword;
	//==============

	//ActItem�Ҵ�
	KaleSeed* _kaleSeed;
	PotatoSeed* _potatoSeed;
	PasnipSeed* _pasnipSeed;
	//===========

	//EatItem�Ҵ�
	Potato* _potato;
	Pasnip* _pasnip;
	Kale* _kale;
	Sap* _sap;
	NormalFish* _normalFish;
	RareFish* _rareFish;
	//==============

	//ResoureceItem�Ҵ�
	Rock* _rock;
	Weed* _weed;
	Wood* _wood;
	//================



	MapMain* _nowTileMap; //���ݻ���ϴ� ��
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	void Init();
	void Action(string name);

	vector<ToolItem*>GetItemList() { return _toolList; }//�����۸���� ���� ���� �������� �Լ�

	//�̸��� ���� ��ȣ�ۿ��� Ÿ���ε��� �������� �Լ�
	virtual	int GetImpactIndexCenter(string name);
	virtual	int GetImpactIndexLeft(string name);
	virtual int GetImpactIndexRight(string name);

	
	vector<ToolItem*> GetToolItem() { return _toolList; }
	
	
	//�̸������� �̹������������Լ�
	virtual image* GetImageInven(string name);
	virtual image* GetImageChar(string name);

	virtual inline void SetImpactIndex(string name, int index);
	virtual inline void SetImpactIndex(string name, int Center, int left, int right);
	
	inline void GetNowTileMapMemoyrAddressLink(MapMain* scene) { _nowTileMap = scene; }
	
};

