#include "stdafx.h"
#include "MiniGame.h"

void MiniGame::InitKeyDown(PLAYER_DIRECTION dir, Vector2 center)
{
	_dir = dir;
	_playerCenter = center;

	_fishfloat = _playerCenter;
	_fishfloat.y -= 200;
	_fishFloatMove = true;
	
	_clickTime++;

}


void MiniGame::InitKeyUp()
{
	_power = _clickTime;
	_clickTime = 0;
	if (_dir == PLAYER_DIRECTION::LEFT)
	{
		_fishingUI.x = _playerCenter.x += 200;
	}
	else
	{

	}
}

void MiniGame::FishFloatUpdate()
{
	if (_fishFloatMove)
	{
		if (_power >= 50)_power = 50;

		if (_dir == PLAYER_DIRECTION::DOWN)
		{

		}

		if (_dir == PLAYER_DIRECTION::LEFT)
		{

		}

		if (_dir == PLAYER_DIRECTION::RIGHT)
		{

		}

		if (_dir == PLAYER_DIRECTION::UP)
		{

		}
	}
}

void MiniGame::Update()
{
}

void MiniGame::Render()
{
}
