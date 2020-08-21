#pragma once
#include "GameObject.h"

class Player;
class astar;
class MapMain;
class Enemy : public GameObject
{
protected:
	Player* _player;
	astar* _astar;
	MapMain* _map;

	Synthesize(int, _damage, Damage)
	Synthesize(int, _hp, Hp)
	Synthesize(float, _speed, Speed)
public:

	virtual void Init() {};
	virtual void Release() {};
	virtual void Update() {};
	virtual void Render() {};

	virtual void SetAddressLinkPlayer(Player* player) { _player = player; }
	virtual void SetAddressLinkMap(MapMain* map) { _map = map; }
};
