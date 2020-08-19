#pragma once
#include "ToolItem.h"

class Potato:public ToolItem
{
private:

public:
	Potato() {};
	virtual ~Potato() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};
/*
class Tool :public ToolItem
class Item :public ToolItem
*/

