#pragma once
#include "ToolItemManager.h"

class SpreadItem
{
private:
	ToolItemManager* _toolItemManager;	//������������ ����ִ�Ŭ����
	vector<ToolItem*> _itemList;		//����������
	MapMain* _nowMap;					//�����
	Spread _type;						//�Ѹ����
protected:
	SpreadItem() {};
	virtual ~SpreadItem() {};
	
	void Init();
	void Update();

	inline void SetToolMemoryAddressLink(ToolItemManager* t) { _toolItemManager = t; }
};

