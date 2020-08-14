#pragma once
#include "ToolItem.h"

class Rock : public ToolItem
{
private:


public:
	Rock() {};
	virtual ~Rock() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

