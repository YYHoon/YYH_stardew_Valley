#pragma once
#include "ToolItem.h"

class Wood : public ToolItem
{
private:

public:
	Wood() {};
	virtual ~Wood() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

