#pragma once
#include "ToolItem.h"


class WaterSpray:public ToolItem
{
private:


public:
	WaterSpray() {};
	virtual ~WaterSpray() {};


	void Init() override;
	void Action() override;
	void ReAction() override;

};

