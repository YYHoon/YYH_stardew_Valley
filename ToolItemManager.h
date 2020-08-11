#pragma once
#include "stdafx.h"
#include "ToolItem.h"
#include "Pickax.h"
#include "Axe.h"

//벡터는 한가지형태밖에담지못함 따라서 아이템을찍어낸 부모형태를담고 
//그부모형태중 이름에따라 기능을 다르게할필요가 있음


class ToolItemManager
{
private:
	vector<ToolItem*> _toolList;
	Pickax* _pickax;
	Axe* _axe;
public:
	ToolItemManager();
	virtual ~ToolItemManager() {};


	
	//bool SearchToolList(string name);
	 
	void Action(string name);

};

