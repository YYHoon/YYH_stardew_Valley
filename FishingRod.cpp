#include "stdafx.h"
#include "FishingRod.h"

void FishingRod::Init()
{
	_name = "FishingRod";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("FishingRod(64x64)");
	_dmage = 0;
	_enumName = TOOLS::FISHINGROD;
	_game = new MiniGame;
}

void FishingRod::Action()
{

	if (!_game->GetNowFishing())
	{
		_game->Init(_playerCenter, _playerDir);
	}
	if (_game->GetNowFishing())_game->Update();
}

void FishingRod::ReAction()
{
	_game->Render();
}
