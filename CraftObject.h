#pragma once
#include "GameObject.h"
class CraftObject : public GameObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
};

