#pragma once
#include "ToolItem.h"

class Sword:public ToolItem
{
private:


public:
	Sword() {};
	virtual ~Sword() {};


	void Init() override;
	void Action() override;
	void Update() override;
	void ReAction() override;

};

