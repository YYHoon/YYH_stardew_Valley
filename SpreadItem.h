#pragma once
#include "ToolItemManager.h"

class SpreadItem
{
private:
	ToolItemManager* _toolItemManager;	//아이템정보를 들고있는클래스
	vector<ToolItem*> _itemList;		//아이템정보
	MapMain* _nowMap;					//현재맵
	Spread _type;						//뿌릴방식
protected:
	SpreadItem() {};
	virtual ~SpreadItem() {};
	
	void Init();
	void Update();

	inline void SetToolMemoryAddressLink(ToolItemManager* t) { _toolItemManager = t; }
};

