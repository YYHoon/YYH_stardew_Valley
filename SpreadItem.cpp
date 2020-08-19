#include "stdafx.h"
#include "SpreadItem.h"
#include "MapMain.h"
#include "Player.h"


SpreadItem::SpreadItem()
{
}

void SpreadItem::Init( string name, MapMain* map, int index, int num)
{

	for (int i = 0; i < num; ++i)
	{
		_spread.nowMap = map;
		_spread.name = name;
		_spread.pos.x = ((_spread.nowMap->GetTiles(index).rc.left + _spread.nowMap->GetTiles(index).rc.right) * 0.5)*64;
		_spread.pos.y = ((_spread.nowMap->GetTiles(index).rc.top + _spread.nowMap->GetTiles(index).rc.bottom) * 0.5)*64;
		_spread.lastPos.x = RND->getFromFloatTo(_spread.pos.x - 100, _spread.pos.x + 100);
		_spread.lastPos.y = RND->getFromFloatTo(_spread.pos.y - 100, _spread.pos.y + 100);
		_spread.speed = 1.0f;

		_spread.img = IMAGEMANAGER->findImage(_spread.name);
		_spread.render = false;
		_spread.move = false;
		_spread.isActive = true;
		if (_spread.pos.x < _spread.lastPos.x)_spread.left = false;
		if (_spread.pos.x > _spread.lastPos.x)_spread.left = true;
		if (_spread.pos.y < _spread.lastPos.y)_spread.up = false;
		if (_spread.pos.y > _spread.lastPos.y)_spread.up = true;
		_spreadItemList.push_back(_spread);
	}
}

void SpreadItem::Init( string name, MapMain* map, Vector2 index, int num)
{

	for (int i = 0; i < num; ++i)
	{
		_spread.nowMap = map;
		_spread.name = name;
		_spread.pos.x = index.x*64;
		_spread.pos.y = index.y*64;
		_spread.lastPos.x = RND->getFromFloatTo(_spread.pos.x - 100, _spread.pos.x + 100);
		_spread.lastPos.y = RND->getFromFloatTo(_spread.pos.y - 100, _spread.pos.y + 100);
		_spread.speed = 7.0f;
		_spread.img = IMAGEMANAGER->findImage(_spread.name);
		_spread.render = false;
		_spread.move = false;
		_spread.isActive = true;
		if (_spread.pos.x < _spread.lastPos.x)_spread.left = false;
		if (_spread.pos.x > _spread.lastPos.x)_spread.left = true;
		if (_spread.pos.y < _spread.lastPos.y)_spread.up = false;
		if (_spread.pos.y > _spread.lastPos.y)_spread.up = true;
		_spreadItemList.push_back(_spread);
	}
}

void SpreadItem::Update()
{
	for (int i = 0; i < _spreadItemList.size(); ++i)
	{
		if (_spreadItemList[i].isActive)
		{
			if (_spreadItemList[i].state == SpreadState::NONE)
				_spreadItemList[i].state = SpreadState::BEFORE_SPREAD;

			SpreadUpdate(_spreadItemList[i]);

			if (_spreadItemList[i].render)
			{
				//cout << "render" << endl;
				ZORDER->ZOrderPush(getMemDC(), RenderType::RENDER, _spreadItemList[i].img, _spreadItemList[i].pos.x - 24, _spreadItemList[i].pos.y - 24, _spreadItemList[i].pos.y + 24);
				//CAMERAMANAGER->render(getMemDC(), _spreadItemList[i].img, _spreadItemList[i].pos.x - 24, _spreadItemList[i].pos.y - 24);
			}
		}
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
		spread.render = true;
		spread.state = SpreadState::DOING_SPREAD;
		break;
	case SpreadState::DOING_SPREAD:
		if (spread.left)
		{
			if (spread.pos.x > spread.lastPos.x)spread.pos.x -= spread.speed;
		}
		if (!spread.left)
		{
			if (spread.pos.x < spread.lastPos.x)spread.pos.x += spread.speed;
		}

		if (spread.up)
		{
			if (spread.pos.y > spread.lastPos.y)spread.pos.y -= spread.speed;
		}
		if (!spread.up)
		{
			if (spread.pos.y < spread.lastPos.y)spread.pos.y += spread.speed;
		}


		//if(spread.pos.x)


		break;
	case SpreadState::AFTER_SPREAD:

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

Vector2 SpreadItem::IndexToVector(MapMain* map, int i)
{
	int x = 0, y = 0;
	y = i / (map->GetHorizon());
	x = i % (map->GetHorizon());
	return Vector2(x,y);
}


