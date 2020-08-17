#pragma once
#include "ToolItem.h"

class Kale : public ToolItem
{
private:

public:
	Kale() {};
	virtual ~Kale() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};