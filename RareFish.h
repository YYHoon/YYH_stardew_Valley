#pragma once
#include "ToolItem.h"

class RareFish : public ToolItem
{
private:

public:
	RareFish() {};
	virtual ~RareFish() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};

