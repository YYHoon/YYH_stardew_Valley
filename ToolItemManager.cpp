#include "stdafx.h"
#include "ToolItemManager.h"

ToolItemManager::ToolItemManager()
{
	if (_axe == nullptr)
	{
		_axe = new Axe;
		_toolList.push_back(_axe);
	}
	if (_pickax == nullptr)
	{
		_pickax = new Pickax;
		_toolList.push_back(_pickax);
	}

}

void ToolItemManager::Action(string name)
{
	for (int i = 0; i < _toolList.size(); ++i)
	{
		if (_toolList[i]->GetName() == "Pickax")
		{
			_toolList[i]->Action();
		}
	
	}
}

