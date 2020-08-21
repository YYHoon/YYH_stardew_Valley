#pragma once
#include "ToolItem.h"

class GrilledFish : public ToolItem
{
private:

public:
	GrilledFish() {};
	virtual ~GrilledFish() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

