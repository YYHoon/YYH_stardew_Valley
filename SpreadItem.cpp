#include "stdafx.h"
#include "SpreadItem.h"
#include "MapMain.h"


SpreadItem::SpreadItem()
{
}

void SpreadItem::Init(Spread ty, string name, int index, int num)
{

	for (int i = 0; i < num; ++i)
	{
		_spread.nowMap = _toolItemManager->GetNowTileMapMemoryAddressLink();
		_spread.type = ty;
		_spread.name = name;
		_spread.pos.x = (_spread.nowMap->GetTiles(index).rc.left + _spread.nowMap->GetTiles(index).rc.right) * 0.5;
		_spread.pos.y = (_spread.nowMap->GetTiles(index).rc.top + _spread.nowMap->GetTiles(index).rc.bottom) * 0.5;
		_spread.lastPos.x = RND->getFromFloatTo(_spread.pos.x - 30, _spread.pos.x + 30);
		_spread.lastPos.y = RND->getFromFloatTo(_spread.pos.y - 15, _spread.pos.y + 15);
		_spread.speed = 1.0f;
		_spread.renge.set(_spread.pos.x - 48, _spread.pos.y - 48, _spread.pos.x + 48, _spread.pos.y + 48);
		_spread.isActive = false;
		_spread.getPlayer = false;
		_spread.move = false;
		if (_spread.pos.x < _spread.lastPos.x)_spread.left = true;
		if (_spread.pos.y > _spread.lastPos.y)_spread.up = true;
		_spreadItemList.push_back(_spread);
	}
}

void SpreadItem::Init(Spread ty, string name, Vector2 index, int num)
{

	for (int i = 0; i < num; ++i)
	{
		_spread.nowMap = _toolItemManager->GetNowTileMapMemoryAddressLink();
		_spread.type = ty;
		_spread.name = name;
		_spread.pos = index;
		_spread.lastPos.x = RND->getFromFloatTo(_spread.pos.x - 30, _spread.pos.x + 30);
		_spread.lastPos.y = RND->getFromFloatTo(_spread.pos.y - 15, _spread.pos.y + 15);
		_spread.speed = 1.0f;
		_spread.renge.set(_spread.pos.x - 48, _spread.pos.y - 48, _spread.pos.x + 48, _spread.pos.y + 48);
		_spread.isActive = false;
		_spread.getPlayer = false;
		_spread.move = false;
		if (_spread.pos.x < _spread.lastPos.x)_spread.left = true;
		if (_spread.pos.y > _spread.lastPos.y)_spread.up = true;
		_spreadItemList.push_back(_spread);
	}
}

void SpreadItem::Update(string name)
{
	for (int i = 0; i < _spreadItemList.size(); ++i)
	{
		if (_spreadItemList[i].name == name && !_spread.isActive)
		{
			switch (_spreadItemList[i].type)
			{
			case Spread::SPREAD:
				if(_spreadItemList[i].state==SpreadState::NONE)
				_spreadItemList[i].state = SpreadState::BEFORE_SPREAD;

				SpreadUpdate(_spreadItemList[i]);
				break;
			case Spread::HARVEST:

				break;
			case Spread::FISHING:
				
				break;
			}
		}


		_spread.renge.set(_spread.pos.x - 48, _spread.pos.y - 48, _spread.pos.x + 48, _spread.pos.y + 48);
	}
}

void SpreadItem::SpreadUpdate(tagSpread &spread)
{
	switch (spread.state)
	{
	case SpreadState::BEFORE_SPREAD:
		if (spread.nowMap->GetTiles(VectorToIndex(spread, spread.lastPos)).collision)
		{
			spread.speed = 0;
		}
		spread.move = true;
		spread.state = SpreadState::DOING_SPREAD;
		break;
	case SpreadState::DOING_SPREAD:
		if (spread.left)
		{
			if (spread.pos.x > spread.lastPos.x)spread.pos.x -= spread.speed;
			else spread.state = SpreadState::AFTER_SPREAD;
		}
		else if (!spread.left)
		{
			if (spread.pos.x < spread.lastPos.x)spread.pos.x += spread.speed;
			else spread.state = SpreadState::AFTER_SPREAD;
		}

		if (spread.up)
		{
			if (spread.pos.y > spread.lastPos.y)spread.pos.y -= spread.speed;
			else spread.state = SpreadState::AFTER_SPREAD;
		}
		else if (!spread.up)
		{
			if (spread.pos.y < spread.lastPos.y)spread.pos.y += spread.speed;
			else spread.state = SpreadState::AFTER_SPREAD;
		}


		break;
	case SpreadState::AFTER_SPREAD:
		spread.move = false;
		spread.isActive = true;
		break;
	}
}

int SpreadItem::VectorToIndex(tagSpread s, Vector2 v)
{
	int i = 0;
	int x = 0, y = 0;
	x = v.x / 64;
	y = v.y / 64;
	i = x + y * (s.nowMap->GetHorizon());
	return i;
}


