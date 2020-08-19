#pragma once
#include "ToolItemManager.h"

struct tagSpread
{
	Spread type=Spread::NONE;					//뿌릴방식
	SpreadState state = SpreadState::NONE;		//뿌려지는 상황
	vector<ToolItem*> itemList;					//아이템정보
	MapMain* nowMap;							//현재맵
};

class SpreadItem
{

private:
	ToolItemManager* _toolItemManager;	//아이템정보를 들고있는클래스
	tagSpread _spreadItemDefault;
	vector<tagSpread> _spreadItemList;

protected:
	SpreadItem() {};
	virtual ~SpreadItem() {};
	
	void Init();
	void InfoUpdate();
	void SpreadUpdate();
	void AlwaysUpdate();

	inline void SetToolMemoryAddressLink(ToolItemManager* t) { _toolItemManager = t; }
};

