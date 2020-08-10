#pragma once
#include "ToolItem.h"

class Axe : public ToolItem
{
private:


public:
	Axe();
	virtual ~Axe() { ; }

	void Action() override;
};

