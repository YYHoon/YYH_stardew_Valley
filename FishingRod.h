#pragma once
#include "ToolItem.h"


class FishingRod:public ToolItem
{
private:


public:
	FishingRod() {};
	virtual ~FishingRod() {};



	void Init()override;
	void Action()override;
	void ReAction()override;
	
};

