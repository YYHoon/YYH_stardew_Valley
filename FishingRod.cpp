#include "stdafx.h"
#include "FishingRod.h"
#include"SpreadItem.h"
#include "Player.h"
#include "AllMap.h"

void FishingRod::Init()
{
	_name = "FishingRod";
	_tag = "ToolItem";
	_imageI = IMAGEMANAGER->findImage("FishingRod(64x64)");
	_dmage = 0;
	_enumName = TOOLS::FISHINGROD;
	_game = new MiniGame;
	_doing = FISHING::NONE;
}

void FishingRod::Action()
{

	_doing = _game->GetDoingFishing();

	if (_player->GetStateName() == "FishingStart")
	{
		_game->Init(_playerCenter, _playerDir);
		_game->Update();
	}
	else
	{
		_game->Update();
	}



}

void FishingRod::ReAction()
{
	_game->Render();
}
