#pragma once
#include "ToolItem.h"

class Salad : public ToolItem
{
private:

public:
	Salad() {};
	virtual ~Salad() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

