#pragma once
#include "ToolItemManager.h"

struct tagSpread
{
	Spread type=Spread::NONE;					//�Ѹ����
	SpreadState state = SpreadState::NONE;		//�ѷ����� ��Ȳ
	vector<ToolItem*> itemList;					//����������
	MapMain* nowMap;							//�����
};

class SpreadItem
{

private:
	ToolItemManager* _toolItemManager;	//������������ ����ִ�Ŭ����
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

