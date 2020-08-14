#pragma once
#include "ToolItem.h"

class Pasnip : public ToolItem
{
private:

public:
	Pasnip() {};
	virtual ~Pasnip() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

