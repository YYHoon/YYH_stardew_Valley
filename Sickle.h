#pragma once
#include "ToolItem.h"

class Sickle:public ToolItem
{
private:


public:

	Sickle() {};
	virtual ~Sickle() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};

