#pragma once
#include "ToolItem.h" 

class PasnipSeed : public ToolItem
{
private:

public:
	PasnipSeed() {};
	virtual ~PasnipSeed() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};