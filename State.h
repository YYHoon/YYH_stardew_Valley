#pragma once
#include "gameNode.h"

class Player;
class MapMain;

class State : public enable_shared_from_this<State>
{
protected:
	Player* _player;
	MapMain* _map;
	string _name;
	string _tagName;

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;

	State(class Player* pPlayer);
	Player* GetPlayer() { return _player; }
	string GetStateName() { return _name; }
	string GetStateTagName() { return _tagName; }
	shared_ptr<State> GetState() { return shared_from_this(); }
};

class PlayerIdle final : public State
{
public:
	PlayerIdle(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;

};

class PlayerItemIdle final : public State
{
public:
	PlayerItemIdle(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerPlanting final : public State
{
public:
	PlayerPlanting(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerMove final : public State
{
public:
	PlayerMove(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerItemMove final : public State
{
public:
	PlayerItemMove(class Player* pPplayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerExhaust final : public State
{
public:
	PlayerExhaust(class Player* pPlayer);
	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerFelling final : public State
{
public:
	PlayerFelling(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerPlowing final : public State
{
public:
	PlayerPlowing(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerMining final : public State
{
public:
	PlayerMining(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerSwing final : public State
{
public:
	PlayerSwing(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerWatering final : public State
{
public:
	PlayerWatering(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerFishing final : public State
{
public:
	PlayerFishing(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};

class PlayerEating final : public State
{
public:
	PlayerEating(class Player* pPlayer);

	void Init()override;
	void Update()override;
	void Release()override;
};