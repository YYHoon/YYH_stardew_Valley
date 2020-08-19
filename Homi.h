#pragma once
#include "ToolItem.h"


class Homi:public ToolItem
{
private:

public:
	Homi() {};
	virtual ~Homi() {};


	void Init() override;
	void Action() override;
	void Update() override;
	void ReAction() override;

};

