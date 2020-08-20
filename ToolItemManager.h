#pragma once
#include "stdafx.h"
#include "AllToolItem.h"
#include "SpreadItem.h"
class SpreadItem;
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

	Vector2 _playerCenter;
	PLAYER_DIRECTION _playerDir;
	SpreadItem* _spreadItem;
	MapMain* _nowTileMap; //���ݻ���ϴ� ��
	ToolItemManager* tosstool;
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	void Init();
	void Action(string name);
	void Update();
	void Render(string name);



	vector<ToolItem*>GetItemList() { return _toolList; }//�����۸���� ���� ���� �������� �Լ�

	//�̸��� ���� ��ȣ�ۿ��� Ÿ���ε��� �������� �Լ�
	virtual	int GetImpactIndexCenter(string name);
	virtual	int GetImpactIndexLeft(string name);
	virtual int GetImpactIndexRight(string name);

	
	vector<ToolItem*> GetToolItem() { return _toolList; }
	
	//�÷��̾� ������ǥ ���� �˾ƿ����Լ� �����ϱ����� ���ʿ�
	virtual void GetFishingInfo(Vector2 c, PLAYER_DIRECTION d);
	
	//�̸������� �̹������������Լ�
	virtual image* GetImageInven(string name);
	virtual image* GetImageChar(string name);

	virtual inline void SetImpactIndex(string name, int index);
	virtual inline void SetImpactIndex(string name, int Center, int left, int right);
	
	inline vector<tagSpread> GetSpreadList() { return _spreadItem->GetSpreadItemList(); }
	void SetIsActive(bool isAc, int idx) { _spreadItem->SetIsActive(isAc, idx); }
	//void SetThisMemoryAddressLink(ToolItemManager* t) { tosstool = t; }

	inline void SetNowTileMapMemoyrAddressLink(MapMain* scene) { _nowTileMap = scene; }
	inline MapMain* GetNowTileMapMemoryAddressLink() { return _nowTileMap; }
	bool GetNowFishing();
};

