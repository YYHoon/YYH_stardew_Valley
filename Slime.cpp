#include "stdafx.h"
#include "Slime.h"

void Slime::Init()
{
	_name = "Slime";
	_type = "ENEMY";
	_active = true;
	_size = Vector2(64, 64);
	_rect = { 0,0,64,64 };
	_hp = 50;
	_damage = 5;
	_speed = 1;
	_position = Vector2(704, 448);
	_currentIdx = Vector2((int)(_position.x / 64), (int)(_position.y / 64));
	_img = IMAGEMANAGER->findImage("SLIME");
	_astar = new astar;
	_astar->SetMapMemoryLink(_map);
	_astar->SetMap();
	_astar->SetStartNode(_currentIdx);
	_astar->SetEndNode(Vector2(_player->GetPlayerOnTileIndex() % _map->GetHorizon(),
		_player->GetPlayerOnTileIndex() / _map->GetHorizon()));
	_astar->PathFind();
}

void Slime::Release()
{
}

void Slime::Update()
{
	_currentIdx = Vector2((int)((_position.x+1) / 64), (int)((_position.y+1) / 64));
	
	_astar->SetEndNode(Vector2(_player->GetPlayerOnTileIndex() % _map->GetHorizon(),
		_player->GetPlayerOnTileIndex() / _map->GetHorizon()));

	if (!_astar->GetPathList().empty())
	{
		if (idx == _astar->GetPathList().size())
		{
			return;
		}
		//if (_astar->GetPathList()[idx]->_idx == _currentIdx)
		//{
		//	_astar->SetMap();
		//	_astar->SetStartNode(_currentIdx);
		//	//_astar->SetEndNode(Vector2(_player->GetPlayerOnTileIndex() % _map->GetHorizon(),
		//	//	_player->GetPlayerOnTileIndex() / _map->GetHorizon()));
		//	//_astar->PathFind();
		//	//if (_astar->GetPathList().empty()) return;
		//	idx = 0;
		//}
		_angle = Vector2::GetAngle(_position + Vector2(32, 32),_astar->GetPathList()[idx]->_idx * 64 + Vector2(32, 32));
		SetPosition(_position + Vector2(cosf(_angle) * _speed, -sinf(_angle) * _speed));
	}
	_rect = { _position.x,_position.y,_position.x + 64 ,_position.y + 64 };
	if (isCollision(_player->GetAttackRect(), _rect))
	{
		_hp -= 50;
	}
	count++;
	
	ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _img, _position.x, _position.y,0,0, _rect.bottom);
}

void Slime::Render()
{
	_astar->render();
	//_rect.render(getMemDC());
}
