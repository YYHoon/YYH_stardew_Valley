#pragma once
#include "ToolItem.h" 

class PotatoSeed : public ToolItem
{
private:

public:
	PotatoSeed() {};
	virtual ~PotatoSeed() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};