#pragma once
#include "ToolItem.h"

class Axe : public ToolItem
{
private:
	bool _isWork;

public:
	Axe();
	virtual ~Axe() { ; }


	void Init() override;
	void Action() override;
	void Update() override;
	void ReAction() override;

	void SetIsWork(bool isWork) { _isWork = isWork; }
};

