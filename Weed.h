#pragma once
#include "ToolItem.h" 

class Weed : public ToolItem 

{
private:

public:

	Weed() {};
	virtual ~Weed() {};

	void Init() override;
	void Action() override;
	void ReAction() override;


};

