#pragma once
#include "ToolItem.h"
class ScareCrow : public ToolItem
{
private:
public:
	ScareCrow() {};
	~ScareCrow() {};

	void Init() override;
	void Action() override;
	void ReAction() override;
};

