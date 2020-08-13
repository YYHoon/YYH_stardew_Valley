#pragma once
#include "gameNode.h"
#include "Vector2.h"
#include "ToolItemManager.h"

class State;
class DummyMap;



class Player : public gameNode
{
private:
	struct NecessaryInfo
	{
		string name;
		image* img;
		image* shadowImg;
		animation* anim;
		Vector2 position;
		MYRECT collision;
		MYRECT shadowCollision;
		PLAYER_DIRECTION direction;
		TOOLS equipment;
		int maxHP;
		int maxStamina;
		int HP;
		int stamina;
		int money;
		float velocity;
		//class* inven;
	};

private:

	/// <summary>
	ToolItemManager* _tool;

	/// </summary>
	DummyMap* _map;
	NecessaryInfo _info;
	PLAYER_ACTION _action;
	shared_ptr<State> _state;
	Vector2 _mousePt;
	string _mapName;
	int _tileIndex[3];
	int _actTileIndex[3];
	int _playerTileX, _playerTileY;
	

	bool _isKeyDown;
	
	//class inven;

public:
	Player() {}
	~Player() {}

	HRESULT init();
	void update();
	void render();
	void release();

	NecessaryInfo GetInfo() { return _info; }
	shared_ptr<State> GetState() { return _state; }
	PLAYER_ACTION GetAction() { return _action; }
	PLAYER_DIRECTION GetDirection() { return _info.direction; }
	TOOLS GetEquip() { return _info.equipment; }
	int* GetTileIndex() { return _actTileIndex; }
	void SetName(string Name) { _info.name = Name; }
	void SetImg(string imgName) { _info.img = IMAGEMANAGER->findImage(imgName); }
	void SetAnim(string stringName) { _info.anim = KEYANIMANAGER->findAnimation(stringName); }
	void SetPosition(Vector2 Pos) { _info.position = Pos; }
	void SetDirection(PLAYER_DIRECTION Direction) { _info.direction = Direction; }
	void SetDecreaseHp(int Hp) { _info.HP -= Hp; }
	void SetIncreaseHp(int Hp) { _info.HP += Hp; }
	void SetHp(int Hp) { _info.HP = Hp; }
	void SetDecreaseStamina(int Stamina) { _info.stamina -= Stamina; }
	void SetIncreaseStamina(int Stamina) { _info.stamina += Stamina; }
	void SetStamina(int Stamina) { _info.stamina = Stamina; }
	void SetDecreaseMoney(int Money) { _info.money -= Money; }
	void SetIncreaseMoney(int Money) { _info.money += Money; }
	void SetMoney(int Money) { _info.money = Money; }
	void SetDecreaseVelocity(float Velocity) { _info.velocity -= Velocity; }
	void SetIncreaseVelocity(float Velocity) { _info.velocity += Velocity; }
	void SetVelocity(float Velocity) { _info.velocity = Velocity; }
	//void SetMapMemoryAddressLink()

public:
	void ChangeState(shared_ptr<State> state);
	void ChangeEquipment(TOOLS equip) { _info.equipment = equip; }
	void Move();
	void CheckTiles();
	void SetMapMemoryAddressLink(DummyMap* map) { _map = map; }

	void SavePlayerInfo();
	void LoadPlayerInfo();
};

