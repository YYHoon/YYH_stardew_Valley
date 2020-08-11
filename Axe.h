#pragma once
#include "ToolItem.h"

class Axe : public ToolItem
{
private:


public:
	Axe();
	virtual ~Axe() { ; }


	void Init() override;
	void Action() override;
	void ReAction() override;

};

