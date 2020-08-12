#pragma once
#include "ToolItem.h"


class Pickax : public ToolItem
{
private:
	

public:
	Pickax();
	~Pickax() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};

