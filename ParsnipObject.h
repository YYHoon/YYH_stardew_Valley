#pragma once
#include "Plants.h"
class ParsnipObject : public Plants
{
public:
	void Init()override;
	void Release()override;
	void Update()override;

};

