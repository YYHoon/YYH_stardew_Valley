#pragma once
#include "ToolItem.h"


class Pickax : public ToolItem
{
private:
	int _dmage;
	Vector2 _impactIndex;

public:
	Pickax();
	~Pickax() {};

	void Action() override;
	


};

