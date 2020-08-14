#include "stdafx.h"
#include "FishingRod.h"

void FishingRod::Init()
{
	_name = "FishingRod";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("FishingRod(64x64)");
	_dmage = 0;
	_enumName = TOOLS::FISHINGROD;
}

void FishingRod::Action()
{
}

void FishingRod::ReAction()
{
}
