#pragma once
#include "ToolItem.h"

class KaleSeed : public ToolItem
{
private:

public:
	KaleSeed() {};
	virtual ~KaleSeed() {};

	void Init() override;
	void Action() override;
	void ReAction() override;

};