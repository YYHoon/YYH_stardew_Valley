#pragma once
#include "ToolItem.h"
#include "MiniGame.h"

class FishingRod:public ToolItem
{
private:
	MiniGame* _game;


public:
	FishingRod() {};
	virtual ~FishingRod() {};



	void Init()override;
	void Action()override;
	void ReAction()override; 
	
};

