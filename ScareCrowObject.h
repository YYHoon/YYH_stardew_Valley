#pragma once
#include "CraftObject.h"
class ScareCrowObject : public CraftObject
{
public:
	void Init()override;
	void Update()override;
	void Release()override;
};

