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
		
		if (_map->GetPM() != nullptr&&_map->GetPM()->GetPlantsList().size() > 0 && !_map->GetPM()->IsExist(_player->GetTileIndex()[0]))
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
				_player->ChangeState(make_shared<PlayerFishingStart>(_player));
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
		&& (int)_player->GetInfo().equipment <= (int)11
		))
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
	cout << (int)_player->GetInfo().equipment << endl;
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
		if (_map->GetPM() != nullptr && _map->GetPM()->GetPlantsList().size() > 0 && !_map->GetPM()->IsExist(_player->GetTileIndex()[0]))
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
		else if (_map->GetPM() != nullptr && (int)_player->GetInfo().equipment == (int)8)
		{
			_player->ChangeState(make_shared<PlayerPlanting>(_player));
			return;
		}
		else if (_player->GetHaveItem()->GetToolEnum() == TOOLS::EATITEM)
		{
			_player->ChangeState(make_shared<PlayerEating>(_player));
			return;
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
			_player->ChangeState(make_shared<PlayerFishingStart>(_player));
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
			return;
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
	_tagName = "move";
	_name = "item_Move";
	//133

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
			_atkCollision.centerSet(_player->GetInfo().position.x, _player->GetInfo().position.y - 75, 192, 128);
			break;
		case PLAYER_DIRECTION::DOWN:
			_player->SetAnim("down_SwordSwing_Player");
			_atkCollision.centerSet(_player->GetInfo().position.x, _player->GetInfo().position.y + 35, 192, 128);
			break;
		case PLAYER_DIRECTION::RIGHT:
			_player->SetAnim("right_SwordSwing_Player");
			_atkCollision.centerSet(_player->GetInfo().position.x + 40, _player->GetInfo().position.y - 52, 128, 192);
			break;
		case PLAYER_DIRECTION::LEFT:
			_player->SetAnim("left_SwordSwing_Player");
			_atkCollision.centerSet(_player->GetInfo().position.x - 40, _player->GetInfo().position.y - 52, 128, 192);
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
	_atkCollision.centerSet(0, 0, 0, 0);
}

PlayerEating::PlayerEating(Player* pPlayer) : State(pPlayer) {}

void PlayerEating::Init()
{
	_tagName = "acting";
	_name = "eating";
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
		_player->GetPlayerInver()->Decrease();
	}
	else if (_player->GetHaveItem()->GetName() == "Kale")
	{
		_player->SetIncreaseHp(15);
		_player->SetIncreaseStamina(20);
		_player->GetPlayerInver()->Decrease();
	}
	else if (_player->GetHaveItem()->GetName() == "Pasnip")
	{
		_player->SetIncreaseHp(10);
		_player->SetIncreaseStamina(10);
		_player->GetPlayerInver()->Decrease();
	}
	else if (_player->GetHaveItem()->GetName() == "Salad")
	{
		_player->SetIncreaseHp(10);
		_player->SetIncreaseStamina(70);
		_player->GetPlayerInver()->Decrease();
	}
	else if (_player->GetHaveItem()->GetName() == "RawFish")
	{
		_player->SetIncreaseHp(20);
		_player->SetIncreaseStamina(30);
		_player->GetPlayerInver()->Decrease();
	}
	else if (_player->GetHaveItem()->GetName() == "GrilledFish")
	{
		_player->SetIncreaseHp(40);
		_player->SetIncreaseStamina(50);
		_player->GetPlayerInver()->Decrease();
	}
	_atkCollision.centerSet(0,0,0,0);
}

PlayerWatering::PlayerWatering(Player* pPlayer) : State(pPlayer) {}

void PlayerWatering::Init()
{
	_tagName = "acting";
	_name = "watering";

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
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0], _player->GetTileIndex()[2], _player->GetTileIndex()[1]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
}

void PlayerWatering::Update()
{
	if (_player->GetInfo().stamina <= 0)return;
	if (!_player->GetInfo().anim->isPlay())_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerWatering::Release()
{
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlayerFishingStart::PlayerFishingStart(Player* pPlayer) : State(pPlayer) {}

void PlayerFishingStart::Init()
{
	//_player->GetInfo().anim->stop();
	_tagName = "acting";
	_name = "FishingStart";

	if (_player->GetDirection() == PLAYER_DIRECTION::LEFT || _player->GetDirection() == PLAYER_DIRECTION::RIGHT)
	{
		_player->SetImg("Fishing_LR");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::UP)
	{
		_player->SetImg("Fishing_UP");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::DOWN)
	{
		_player->SetImg("Fishing_DOWN");
	}

	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:

		_player->SetAnim("Up_Fishing_Charge");

		break;
	case PLAYER_DIRECTION::DOWN:

		_player->SetAnim("Down_Fishing_Charge");

		break;
	case PLAYER_DIRECTION::RIGHT:

		_player->SetAnim("Right_Fishing_Charge");

		break;
	case PLAYER_DIRECTION::LEFT:

		_player->SetAnim("Left_Fishing_Charge");

		break;
	default:
		break;
	}

	//_player->GetInfo().anim->start();
	_map = _player->GetMap();
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());


	//낚시대 휘두르기애니메이션
}

void PlayerFishingStart::Update()
{
	cout << "1" << endl;
	if (_player->GetInfo().stamina <= 0)return;
	//_player->GetTM()->Action(_player->GetHaveItem()->GetName());
	if (!_player->GetInfo().anim->isPlay())
	{
		_player->ChangeState(make_shared<PlayerFishingProceeding>(_player));
		return;
	}
	//낚시대휘두르고나서 미니게임시작해야하니상태 전환

	if (_player->GetDoingFishing() == FISHING::NONE)_player->ChangeState(make_shared<PlayerFishingToIdle>(_player));
}

void PlayerFishingStart::Release()
{

}

////////////////////////

PlayerFishingProceeding::PlayerFishingProceeding(Player* pPlayer) : State(pPlayer) {}

void PlayerFishingProceeding::Init()
{
	//_player->GetInfo().anim->stop();
	_tagName = "acting";
	_name = "Fishing";

	if (_player->GetDirection() == PLAYER_DIRECTION::LEFT || _player->GetDirection() == PLAYER_DIRECTION::RIGHT)
	{
		_player->SetImg("Fishing_LR");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::UP)
	{
		_player->SetImg("Fishing_UP");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::DOWN)
	{
		_player->SetImg("Fishing_DOWN");
	}
	


	_map = _player->GetMap();
	//cout << (int)_player->GetDirection() << endl;
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
	if (_map->GetTiles(_player->GetTileIndex()[0]).terrain != TERRAIN::WATER)
	{
		_player->ChangeState(make_shared<PlayerIdle>(_player));
		return;
	}
}

void PlayerFishingProceeding::Update()
{

	cout << "2" << endl;
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

		switch (_player->GetDirection())
		{
		case PLAYER_DIRECTION::UP:

			_player->SetAnim("Up_Fishing_Shot");

			break;
		case PLAYER_DIRECTION::DOWN:

			_player->SetAnim("Down_Fishing_Shot");

			break;
		case PLAYER_DIRECTION::RIGHT:

			_player->SetAnim("Right_Fishing_Shot");

			break;
		case PLAYER_DIRECTION::LEFT:

			_player->SetAnim("Left_Fishing_Shot");

			break;
		default:
			break;
		}
		_player->GetInfo().anim->stop();
		_player->GetInfo().anim->start();
	}
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());

	if (_player->GetInfo().stamina <= 0)return;
	if (_player->GetDoingFishing() == FISHING::DOINGMINIGAME)
	{
		_player->ChangeState(make_shared<PlayerFishingProceedingSec>(_player));
		return;
	}
	if (_player->GetDoingFishing() == FISHING::NONE)_player->ChangeState(make_shared<PlayerFishingToIdle>(_player));
}

void PlayerFishingProceeding::Release()
{

}

/// <returns></returns>//////////////////////
PlayerFishingProceedingSec::PlayerFishingProceedingSec(Player* pPlayer) : State(pPlayer) {}

void PlayerFishingProceedingSec::Init()
{
	//_player->GetInfo().anim->stop();
	_tagName = "acting";
	_name = "Fishing";

	if (_player->GetDirection() == PLAYER_DIRECTION::LEFT || _player->GetDirection() == PLAYER_DIRECTION::RIGHT)
	{
		_player->SetImg("Fishing_LR");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::UP)
	{
		_player->SetImg("Fishing_UP");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::DOWN)
	{
		_player->SetImg("Fishing_DOWN");
	}
	
	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:

		_player->SetAnim("Up_Fishing_Doing");

		break;
	case PLAYER_DIRECTION::DOWN:

		_player->SetAnim("Down_Fishing_Doing");

		break;
	case PLAYER_DIRECTION::RIGHT:

		_player->SetAnim("Right_Fishing_Doing");

		break;
	case PLAYER_DIRECTION::LEFT:

		_player->SetAnim("Left_Fishing_Doing");

		break;
	default:
		break;
	}

	_player->GetInfo().anim->start();

	//_map = _player->GetMap();
	//cout << (int)_player->GetDirection() << endl;
	//_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	//_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);

}

void PlayerFishingProceedingSec::Update()
{
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
	if (!_player->GetInfo().anim->isPlay())_player->GetInfo().anim->start();
	if (_player->GetDoingFishing() == FISHING::SUCCESS)
	{
		int rnd = RND->getInt(2);
		if(rnd==0)_player->GetPlayerInver()->PlayerLootItem("NormalFish");
		if(rnd==1)_player->GetPlayerInver()->PlayerLootItem("RareFish");

		_player->ChangeState(make_shared<PlayerFishingEnd>(_player));
		return;
	}
	if(_player->GetDoingFishing() == FISHING::MISS)
	{
		_player->ChangeState(make_shared<PlayerFishingToIdle>(_player));
		return;
	}
	if (_player->GetDoingFishing() == FISHING::NONE)_player->ChangeState(make_shared<PlayerFishingToIdle>(_player));
}

void PlayerFishingProceedingSec::Release()
{
}

/// ////////////////////////

PlayerFishingEnd::PlayerFishingEnd(Player* pPlayer) : State(pPlayer) {}

void PlayerFishingEnd::Init()
{
	_player->GetInfo().anim->stop();
	_tagName = "acting";
	_name = "Fishing";
	if (_player->GetDirection() == PLAYER_DIRECTION::LEFT || _player->GetDirection() == PLAYER_DIRECTION::RIGHT)
	{
		_player->SetImg("Fishing_LR");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::UP)
	{
		_player->SetImg("Fishing_UP");
	}
	if (_player->GetDirection() == PLAYER_DIRECTION::DOWN)
	{
		_player->SetImg("Fishing_DOWN");
	}
	
	switch (_player->GetDirection())
	{
	case PLAYER_DIRECTION::UP:
		_player->SetAnim("Up_Fishing_Suc");
		break;
	case PLAYER_DIRECTION::DOWN:
		_player->SetAnim("Down_Fishing_Suc");
		break;
	case PLAYER_DIRECTION::RIGHT:
		_player->SetAnim("Right_Fishing_Suc");
		break;
	case PLAYER_DIRECTION::LEFT:
		_player->SetAnim("Left_Fishing_Sus");
		break;
	default:
		break;
	}
	_map = _player->GetMap();
	//_player->GetInfo().anim->start();
	_player->GetTM()->SetNowTileMapMemoyrAddressLink(_map);
	_player->GetTM()->SetImpactIndex(_player->GetHaveItem()->GetName(), _player->GetTileIndex()[0]);
}

void PlayerFishingEnd::Update()
{
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
	cout << "3" << endl;
	if (_player->GetDoingFishing() == FISHING::NONE)
	{
		_player->ChangeState(make_shared<PlayerFishingToIdle>(_player));
		return;
	}
}

void PlayerFishingEnd::Release()
{

}



PlayerFishingToIdle::PlayerFishingToIdle(Player* pPlayer) : State(pPlayer) {}


void PlayerFishingToIdle::Init()
{
}

void PlayerFishingToIdle::Update()
{
	cout << "4" << endl;
	_player->GetTM()->Action(_player->GetHaveItem()->GetName());
	_player->ChangeState(make_shared<PlayerIdle>(_player));
}

void PlayerFishingToIdle::Release()
{
}

