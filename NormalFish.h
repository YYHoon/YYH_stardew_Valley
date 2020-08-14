#pragma once
#include "ToolItem.h"

class NormalFish : public ToolItem
{
private:

public:
	NormalFish() {};
	virtual ~NormalFish() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

