#pragma once
#include "gameNode.h"


class SaveLoad : public gameNode
{
	SaveLoad();
	~SaveLoad();

	void update();

	void Save();
	void Load();

};

