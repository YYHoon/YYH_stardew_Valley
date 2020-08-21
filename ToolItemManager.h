#pragma once
#include "stdafx.h"
#include "AllToolItem.h"
#include "SpreadItem.h"
class SpreadItem;
class MapMain;

class Player;

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

	Player* _player;

	Vector2 _playerCenter;
	PLAYER_DIRECTION _playerDir;
	SpreadItem* _spreadItem;
	MapMain* _nowTileMap; //지금사용하는 맵
	ToolItemManager* tosstool;
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	void Init();
	void Action(string name);
	void Update();
	void Render(string name);



	vector<ToolItem*>GetItemList() { return _toolList; }//아이템목록을 담은 벡터 가져오는 함수

	//이름에 따라 상호작용할 타일인덱스 가져오는 함수
	virtual	int GetImpactIndexCenter(string name);
	virtual	int GetImpactIndexLeft(string name);
	virtual int GetImpactIndexRight(string name);

	
	vector<ToolItem*> GetToolItem() { return _toolList; }
	
	//플레이어 센터좌표 방향 알아오는함수 낚시하기전에 꼭필요
	virtual void SetFishingInfo(Vector2 c, PLAYER_DIRECTION d);
	
	//이름에따른 이미지가져오는함수
	virtual image* GetImageInven(string name);
	virtual image* GetImageChar(string name);

	virtual FISHING GetDoingFishing();
	virtual void SetDoingFishing(FISHING tf);


	virtual inline void SetImpactIndex(string name, int index);
	virtual inline void SetImpactIndex(string name, int Center, int left, int right);
	
	inline vector<tagSpread> GetSpreadList() { return _spreadItem->GetSpreadItemList(); }
	void SetIsActive(bool isAc, int idx) { _spreadItem->SetIsActive(isAc, idx); }
	//void SetThisMemoryAddressLink(ToolItemManager* t) { tosstool = t; }

	inline void SetPlayerAddressLink(Player* pla) { _player = pla; }

	inline void SetNowTileMapMemoyrAddressLink(MapMain* scene) { _nowTileMap = scene; }
	inline MapMain* GetNowTileMapMemoryAddressLink() { return _nowTileMap; }
	bool GetNowFishing();
};

