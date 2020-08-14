#pragma once
#include "ToolItem.h"

class Sap : public ToolItem

{
private:

public:
	Sap() {};
	virtual ~Sap() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};

