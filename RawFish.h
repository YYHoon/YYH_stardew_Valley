#pragma once
#include "ToolItem.h"

class RawFish : public ToolItem
{
private:

public:
	RawFish() {};
	virtual ~RawFish() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

