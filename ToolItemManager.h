#pragma once
#include "stdafx.h"
#include "ToolItem.h"
#include "Pickax.h"
#include "Axe.h"

//���ʹ� �Ѱ������¹ۿ��������� ���� ���������� �θ����¸���� 
//�׺θ������� �̸������� ����� �ٸ������ʿ䰡 ����


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

