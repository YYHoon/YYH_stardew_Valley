#include "stdafx.h"
#include "State.h"
#include "Player.h"
#include "AllMap.h"

State::State(Player* pPlayer) :_player(pPlayer) {}

PlayerIdle::PlayerIdle(Player* pPlayer) : State(pPlayer) {}

void PlayerIdle::Init()
{
	_player->SetImg("player");
	_name = "none_Idle";
	_tagName = "idle";

	int rightIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Idle_Player", "player", rightIdle, 1, 6, false);
	int leftIdle[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Idle_Player", "player", leftIdle, 1, 6, false);
	int upIdle[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Idle_Player", "player", upIdle, 1, 6, false);
	int downIdle[] = { 23 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Idle_Player", "player", downIdle, 1, 6, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Idle_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Idle_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Idle_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Idle_Player");
		break;
	}

	_map = _player->GetMap();
}

void PlayerIdle::Update()
{
	if (_player->GetInfo().stamina <= 0)return;

	if (((int)_player->GetInfo().equipment >= (int)8
		&& (int)_player->GetInfo().equipment <= (int)10
		))
	{
		_player->ChangeState(make_shared<PlayerItemIdle>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_player->SetDirection(PLAYER_DIRECTION::UP);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_player->SetDirection(PLAYER_DIRECTION::DOWN);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->SetDirection(PLAYER_DIRECTION::LEFT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_player->SetDirection(PLAYER_DIRECTION::RIGHT);
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_map->GetPM()->GetPlantsList().size() > 0 && !_map->GetPM()->IsExist(_player->GetTileIndex()[0]))
		{
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "potatoObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Potato");
			}
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "kaleObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Kale");
			}
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "parsnipObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Pasnip");
			}
			_map->GetPM()->Harvesting(_player->GetTileIndex()[0]);
			
		}
		else
		{
			switch (_player->GetEquip())
			{
			case TOOLS::PICK:
				_player->ChangeState(make_shared<PlayerMining>(_player));
				return;
			case TOOLS::HOE:
				_player->ChangeState(make_shared<PlayerPlowing>(_player));
				return;
			case TOOLS::SICKLE:
				_player->ChangeState(make_shared<PlayerSwing>(_player));
				return;
			case TOOLS::AXE:
				_player->ChangeState(make_shared<PlayerFelling>(_player));
				return;
			case TOOLS::FISHINGROD:
				_player->ChangeState(make_shared<PlayerFishing>(_player));
				return;
			case TOOLS::SWORD:
				_player->ChangeState(make_shared<PlayerSwing>(_player));
				return;
			case TOOLS::ITEM:
				_player->ChangeState(make_shared<PlayerEating>(_player));
				return;
			case TOOLS::WATERING_CAN:
				_player->ChangeState(make_shared<PlayerWatering>(_player));
				return;
			case TOOLS::NONE:
				_player->ChangeState(make_shared<PlayerIdle>(_player));
			default:
				break;
			}
		}
	}
}

void PlayerIdle::Release()
{
}

PlayerItemIdle::PlayerItemIdle(Player* pPlayer) : State(pPlayer) {}

void PlayerItemIdle::Init()
{
	_tagName = "idle";
	_name = "item_Idle";

	int ItemDownIdle[] = { 116 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Item_Idle_Player", "player", ItemDownIdle, 1, 6, false);
	int ItemLeftIdle[] = { 120 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Item_Idle_Player", "player", ItemLeftIdle, 1, 6, false);
	int ItemRightIdle[] = { 125 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Item_Idle_Player", "player", ItemRightIdle, 1, 6, false);
	int ItemUpdle[] = { 134 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Item_Idle_Player", "player", ItemUpdle, 1, 6, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Item_Idle_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Item_Idle_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Item_Idle_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Item_Idle_Player");
		break;
	}

	_map = _player->GetMap();
}

void PlayerItemIdle::Update()
{
	if (_player->GetInfo().stamina <= 0)return;

	if (!((int)_player->GetInfo().equipment >= (int)8
		&& (int)_player->GetInfo().equipment <= (int)10
		))
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_player->SetDirection(PLAYER_DIRECTION::UP);
		_player->ChangeState(make_shared<PlayerItemMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_player->SetDirection(PLAYER_DIRECTION::DOWN);
		_player->ChangeState(make_shared<PlayerItemMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_player->SetDirection(PLAYER_DIRECTION::LEFT);
		_player->ChangeState(make_shared<PlayerItemMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_player->SetDirection(PLAYER_DIRECTION::RIGHT);
		_player->ChangeState(make_shared<PlayerItemMove>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_map->GetPM()->GetPlantsList().size() > 0 && !_map->GetPM()->IsExist(_player->GetTileIndex()[0]))
		{
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "potatoObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Potato");
			}
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "kaleObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Kale");
			}
			if (_map->GetPM()->GetPlantsName(_player->GetTileIndex()[0]) == "parsnipObject")
			{
				_player->GetPlayerInver()->PlayerLootItem("Pasnip");
			}
			_map->GetPM()->Harvesting(_player->GetTileIndex()[0]);

		}
		else if ((int)_player->GetInfo().equipment >= (int)8
			&& (int)_player->GetInfo().equipment <= (int)10)
		{
			_player->ChangeState(make_shared<PlayerPlanting>(_player));
		}
	}
}

void PlayerItemIdle::Release()
{
}

PlayerPlanting::PlayerPlanting(Player* pPlayer) : State(pPlayer) {}

void PlayerPlanting::Init()
{
	_tagName = "farming";
	_name = "planting";
	_map = _player->GetMap();
}

void PlayerPlanting::Update()
{
	
	if(_map->GetPM()->Planting(_player->GetTileIndex()[0], _player->GetHaveItem()->GetName()))
		_player->GetPlayerInver()->Decrease();
	cout << _map->GetPM()->Planting(_player->GetTileIndex()[0], _player->GetHaveItem()->GetName()) << endl;
	_player->ChangeState(make_shared<PlayerIdle>(_player));
	return;
}

void PlayerPlanting::Release()
{
}

PlayerMove::PlayerMove(Player* pPlayer) : State(pPlayer) {}

void PlayerMove::Init()
{
	_player->SetImg("player");
	_tagName = "move";
	_name = "none_Move";

	int RightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Move_Player", "player", RightMove, 5, 10, true);
	int LeftMove[] = { 7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Move_Player", "player", LeftMove, 5, 10, true);
	int UpMove[] = { 13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Move_Player", "player", UpMove, 7, 10, true);
	int DownMove[] = { 21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Move_Player", "player", DownMove, 6, 10, true);
	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Move_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Move_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Move_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Move_Player");
		break;
	}
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerMove::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if ((int)_player->GetInfo().equipment >= (int)8
		&& (int)_player->GetInfo().equipment <= (int)10
		)
	{
		_player->ChangeState(make_shared<PlayerItemMove>(_player));
		return;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player->SetAnim("up_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player->SetAnim("up_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_LEFT);
		}
		else
		{
			_player->SetAnim("up_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player->SetAnim("right_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player->SetAnim("right_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_RIGHT);
		}
		else
		{
			_player->SetAnim("right_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::RIGHT);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player->SetAnim("left_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player->SetAnim("left_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_LEFT);
		}
		else
		{
			_player->SetAnim("left_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::LEFT);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player->SetAnim("down_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player->SetAnim("down_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_LEFT);
		}
		else
		{
			_player->SetAnim("down_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN);
		}
	}
	else
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch (_player->GetEquip())
		{
		case TOOLS::PICK:
			_player->ChangeState(make_shared<PlayerMining>(_player));
			return;
		case TOOLS::HOE:
			_player->ChangeState(make_shared<PlayerPlowing>(_player));
			return;
		case TOOLS::SICKLE:
			_player->ChangeState(make_shared<PlayerSwing>(_player));
			return;
		case TOOLS::AXE:
			_player->ChangeState(make_shared<PlayerFelling>(_player));
			return;
		case TOOLS::FISHINGROD:
			_player->ChangeState(make_shared<PlayerFishing>(_player));
			return;
		case TOOLS::SWORD:
			_player->ChangeState(make_shared<PlayerSwing>(_player));
			return;
		case TOOLS::ITEM:
			_player->ChangeState(make_shared<PlayerEating>(_player));
			return;
		case TOOLS::WATERING_CAN:
			_player->ChangeState(make_shared<PlayerWatering>(_player));
			return;
		case TOOLS::NONE:
			_player->ChangeState(make_shared<PlayerIdle>(_player));
		default:
			break;
		}
	}
	switch (_player->GetSoundWalk())
	{
	case PLAYER_SOUND_TILES::GRASS:
		if (!SOUNDMANAGER->isPlaySound("onGrass"))
		{
			if (SOUNDMANAGER->isPlaySound("onSoil"))SOUNDMANAGER->stop("onSoil");
			else if (SOUNDMANAGER->isPlaySound("onRock"))SOUNDMANAGER->stop("onRock");
			SOUNDMANAGER->play("onGrass", 1.0f);
		}
		break;
	case PLAYER_SOUND_TILES::SOIL:
		if (!SOUNDMANAGER->isPlaySound("onSoil"))
		{
			if (SOUNDMANAGER->isPlaySound("onGrass"))SOUNDMANAGER->stop("onGrass");
			else if (SOUNDMANAGER->isPlaySound("onRock"))SOUNDMANAGER->stop("onRock");
			SOUNDMANAGER->play("onSoil", 1.0f);
		}
		break;
	}
}

void PlayerMove::Release()
{
	if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("up_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::UP);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("down_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::DOWN);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("right_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::RIGHT);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("left_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::LEFT);

	SOUNDMANAGER->stop("onGrass");
	SOUNDMANAGER->stop("onSoil");
	SOUNDMANAGER->stop("onRock");
}

PlayerItemMove::PlayerItemMove(Player* pPplayer) : State(pPplayer) {}

void PlayerItemMove::Init()
{
	cout << "µé¾î°¬´©?" << endl;
	_tagName = "move";
	_name = "item_Move";
	//133
	int leftItemMove[] = { 120,121,122,123 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Item_Move_Player", "player", leftItemMove, 4, 10, false);
	int rightItemMove[] = { 125,126,127,128 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Item_Move_Player", "player", rightItemMove, 4, 10, false);
	int upItemMove[] = { 132,133,134,135,136,137 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Item_Move_Player", "player", upItemMove, 6, 10, false);
	int downItmeMove[] = { 139,140,141,142 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Item_Move_Player", "player", downItmeMove, 4, 10, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Item_Move_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Item_Move_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Item_Move_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Item_Move_Player");
		break;
	}

	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerItemMove::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!((int)_player->GetInfo().equipment >= (int)8
		&& (int)_player->GetInfo().equipment <= (int)10
		))
	{
		_player->ChangeState(make_shared<PlayerMove>(_player));
		return;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player->SetAnim("up_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player->SetAnim("up_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_LEFT);
		}
		else
		{
			_player->SetAnim("up_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player->SetAnim("right_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player->SetAnim("right_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_RIGHT);
		}
		else
		{
			_player->SetAnim("right_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::RIGHT);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player->SetAnim("left_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::UP_LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player->SetAnim("left_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_LEFT);
		}
		else
		{
			_player->SetAnim("left_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::LEFT);
		}
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player->SetAnim("down_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player->SetAnim("down_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN_LEFT);
		}
		else
		{
			_player->SetAnim("down_Item_Move_Player");
			_player->SetDirection(PLAYER_DIRECTION::DOWN);
		}
	}
	else
	{
		_player->ChangeState(make_shared<PlayerItemIdle>(_player));
		return;
	}
	switch (_player->GetSoundWalk())
	{
	case PLAYER_SOUND_TILES::GRASS:
		if (!SOUNDMANAGER->isPlaySound("onGrass"))
		{
			if (SOUNDMANAGER->isPlaySound("onSoil"))SOUNDMANAGER->stop("onSoil");
			else if (SOUNDMANAGER->isPlaySound("onRock"))SOUNDMANAGER->stop("onRock");
			SOUNDMANAGER->play("onGrass", 1.0f);
		}
		break;
	case PLAYER_SOUND_TILES::SOIL:
		if (!SOUNDMANAGER->isPlaySound("onSoil"))
		{
			if (SOUNDMANAGER->isPlaySound("onGrass"))SOUNDMANAGER->stop("onGrass");
			else if (SOUNDMANAGER->isPlaySound("onRock"))SOUNDMANAGER->stop("onRock");
			SOUNDMANAGER->play("onSoil", 1.0f);
		}
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_player->GetEquip() == TOOLS::ITEM)
		{
			_player->ChangeState(make_shared<PlayerItemIdle>(_player));
			return;
		}
	}
}

void PlayerItemMove::Release()
{
	if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("up_Item_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::UP);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("down_Item_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::DOWN);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("right_Item_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::RIGHT);
	else if (_player->GetInfo().anim == KEYANIMANAGER->findAnimation("left_Item_Move_Player"))_player->SetDirection(PLAYER_DIRECTION::LEFT);

	SOUNDMANAGER->stop("onGrass");
	SOUNDMANAGER->stop("onSoil");
	SOUNDMANAGER->stop("onRock");
}

PlayerExhaust::PlayerExhaust(Player* pPlayer) : State(pPlayer) {}

void PlayerExhaust::Init()
{
}

void PlayerExhaust::Update()
{
}

void PlayerExhaust::Release()
{
}

PlayerFelling::PlayerFelling(Player* pPlayer) : State(pPlayer) {}

void PlayerFelling::Init()
{
	_tagName = "acting";
	_name = "felling";

	int rightFelling[] = { 33,34,35,36 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Felling_Player", "player", rightFelling, 4, 10, false);
	int leftFelling[] = { 38,39,40,41,42 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Felling_Player", "player", leftFelling, 4, 10, false);
	int upFelling[] = { 43,44,45,46 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Felling_Player", "player", upFelling, 4, 10, false);
	int downFelling[] = { 27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Felling_Player", "player", downFelling, 6, 10, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Felling_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Felling_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Felling_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Felling_Player");
		break;
	default:
		break;
	}

	_map = _player->GetMap();
	if (
		_map->GetTiles()[_player->GetTileIndex()[0]].object == MAPOBJECT::BRANCH ||
		_map->GetTiles()[_player->GetTileIndex()[0]].object == MAPOBJECT::TREE1 ||
		_map->GetTiles()[_player->GetTileIndex()[0]].object == MAPOBJECT::TREE2 ||
		_map->GetTiles()[_player->GetTileIndex()[0]].object == MAPOBJECT::TREE3)SOUNDMANAGER->play("actMining");

	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerFelling::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerFelling::Release()
{
	cout << _player->GetHp() << endl;
	_player->SetDecreaseStamina(5);
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
}

PlayerPlowing::PlayerPlowing(Player* pPlayer) : State(pPlayer) {}

void PlayerPlowing::Init()
{
	_name = "plowing";
	_tagName = "acting";

	int downPlowing[] = { 48,49,50 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Plowing_Player", "player", downPlowing, 3, 10, false);
	int upPlowing[] = { 51,52,53,54 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Plowing_Player", "player", upPlowing, 4, 10, false);
	int rightPlowing[] = { 55,56,57,58,59 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Plowing_Player", "player", rightPlowing, 4, 10, false);
	int leftPlowing[] = { 60,61,62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Plowing_Player", "player", leftPlowing, 5, 10, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Plowing_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Plowing_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Plowing_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Plowing_Player");
		break;
	default:
		break;
	}
	_map = _player->GetMap();
	if (_map->GetTiles()[_player->GetTileIndex()[0]].terrain == TERRAIN::DIRT)SOUNDMANAGER->play("actHoe");
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerPlowing::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerPlowing::Release()
{
	_player->SetDecreaseStamina(2);
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
}

PlayerMining::PlayerMining(Player* pPlayer) : State(pPlayer) {}


void PlayerMining::Init()
{
	_tagName = "acting";
	_name = "mining";

	int downMining[] = { 168,169,170, 171, 172,173,174 };
	KEYANIMANAGER->addArrayFrameAnimation("down_mining_Player", "player", downMining, 7, 10, false);
	int upMining[] = { 175,176,177,178,179 };
	KEYANIMANAGER->addArrayFrameAnimation("up_mining_Player", "player", upMining, 5, 10, false);
	int rightMining[] = { 180,181,182,183,184 };
	KEYANIMANAGER->addArrayFrameAnimation("right_mining_Player", "player", rightMining, 5, 10, false);
	int leftMining[] = { 189,188,187,186,185 };
	KEYANIMANAGER->addArrayFrameAnimation("left_mining_Player", "player", leftMining, 5, 10, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_mining_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_mining_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_mining_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_mining_Player");
		break;
	default:
		break;
	}
	_map = _player->GetMap();
	if (_map->GetTiles()[_player->GetTileIndex()[0]].object == MAPOBJECT::ROCK)SOUNDMANAGER->play("actMining");
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerMining::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerMining::Release()
{
	_player->SetDecreaseStamina(5);
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
}

PlayerSwing::PlayerSwing(Player* pPlayer) : State(pPlayer) {}

void PlayerSwing::Init()
{
	_tagName = "acting";
	_name = "swing";

	int downSickleSwing[] = { 65,66,67,68,69,70 };
	KEYANIMANAGER->addArrayFrameAnimation("down_SickleSwing_Player", "player", downSickleSwing, 6, 10, false);
	int rightSickleSwing[] = { 72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("right_SickleSwing_Player", "player", rightSickleSwing, 6, 10, false);
	int lefSickleSwing[] = { 78,79,80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("left_SickleSwing_Player", "player", lefSickleSwing, 5, 10, false);
	int upSickleSwing[] = { 84,85,86,87,88,89 };
	KEYANIMANAGER->addArrayFrameAnimation("up_SickleSwing_Player", "player", upSickleSwing, 6, 10, false);
	int downAttack[] = { 143,144,145,146,147,148, 149 };
	KEYANIMANAGER->addArrayFrameAnimation("down_SwordSwing_Player", "player", downAttack, 7, 10, false);
	int rightAttack[] = { 150,151,152,153,154,155 };
	KEYANIMANAGER->addArrayFrameAnimation("right_SwordSwing_Player", "player", rightAttack, 6, 10, false);
	int leftAttack[] = { 156,157,158,159,160,161 };
	KEYANIMANAGER->addArrayFrameAnimation("left_SwordSwing_Player", "player", leftAttack, 6, 10, false);
	int upAttack[] = { 162,163,164 };
	KEYANIMANAGER->addArrayFrameAnimation("up_SwordSwing_Player", "player", upAttack, 3, 10, false);

	if (_player->GetEquip() == TOOLS::SICKLE)
	{
		switch (_player->GetDirection())
		{
		case PLAYER_DIRECTION::UP:
			_player->SetAnim("up_SickleSwing_Player");
			break;
		case PLAYER_DIRECTION::DOWN:
			_player->SetAnim("down_SickleSwing_Player");
			break;
		case PLAYER_DIRECTION::RIGHT:
			_player->SetAnim("right_SickleSwing_Player");
			break;
		case PLAYER_DIRECTION::LEFT:
			_player->SetAnim("left_SickleSwing_Player");
			break;
		default:
			break;
		}
	}
	else if (_player->GetEquip() == TOOLS::SWORD)
	{
		switch (_player->GetDirection())
		{
		case PLAYER_DIRECTION::UP:
			_player->SetAnim("up_SwordSwing_Player");
			break;
		case PLAYER_DIRECTION::DOWN:
			_player->SetAnim("down_SwordSwing_Player");
			break;
		case PLAYER_DIRECTION::RIGHT:
			_player->SetAnim("right_SwordSwing_Player");
			break;
		case PLAYER_DIRECTION::LEFT:
			_player->SetAnim("left_SwordSwing_Player");
			break;
		default:
			break;
		}
	}
	_map = _player->GetMap();
	SOUNDMANAGER->play("actSwing");

	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerSwing::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerSwing::Release()
{
	_player->SetDecreaseStamina(2);
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0], _player->GetTileIndex()[2], _player->GetTileIndex()[1]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
}

PlayerFishing::PlayerFishing(Player* pPlayer) : State(pPlayer) {}

void PlayerFishing::Init()
{
}

void PlayerFishing::Update()
{
}

void PlayerFishing::Release()
{
}

PlayerEating::PlayerEating(Player* pPlayer) : State(pPlayer) {}

void PlayerEating::Init()
{
	_tagName = "acting";
	_name = "eating";

	int eating[] = { 192,193,194,195,196,197,198,199,200,201 };
	KEYANIMANAGER->addArrayFrameAnimation("eating_Player", "player", eating, 10, 10, false);
	_player->SetAnim("eating_Player");
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerEating::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())
	{
		_player->ChangeEquipment(TOOLS::END);
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
}

void PlayerEating::Release()
{
	if (_player->GetHaveItem()->GetName() == "Potato")
	{
		_player->SetIncreaseHp(20);
		_player->SetIncreaseStamina(30);
		//decrease
	}
	else if (_player->GetHaveItem()->GetName() == "Kale")
	{
		_player->SetIncreaseHp(15);
		_player->SetIncreaseStamina(20);
	}
	else if (_player->GetHaveItem()->GetName() == "Parsnip")
	{
		_player->SetIncreaseHp(10);
		_player->SetIncreaseStamina(10);
	}
}

PlayerWatering::PlayerWatering(Player* pPlayer) : State(pPlayer) {}

void PlayerWatering::Init()
{
	_tagName = "acting";
	_name = "watering";

	int rightWatering[] = { 90,91,92,93,94, 93, 94, 93, 94, 93, 94 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Watering_Player", "player", rightWatering, 11, 10, false);
	int downWatering[] = { 96,97,98,99,100,101,102,103,104,105,106, 107 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Watering_Player", "player", downWatering, 12, 10, false);
	int leftWatering[] = { 108,109,110,111,112 , 111, 112, 111, 112, 111, 112 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Watering_Player", "player", leftWatering, 11, 10, false);
	int upWatering[] = { 113,114, 115, 115, 115, 115, 115, 115, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Watering_Player", "player", upWatering, 9, 10, false);

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("up_Watering_Player");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("down_Watering_Player");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("right_Watering_Player");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("left_Watering_Player");
		break;
	default:
		break;
	}
	_map = _player->GetMap();
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerWatering::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerWatering::Release()
{
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0], _player->GetTileIndex()[2], _player->GetTileIndex()[1]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
}


