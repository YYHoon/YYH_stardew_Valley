#include "stdafx.h"
#include "Player.h"
#include "State.h"
#include "AllMap.h"
#include "HpStaminaBar.h"
#include "SpreadItem.h"

HRESULT Player::init()
{
	IMAGEMANAGER->addImage("playerShadow", "image/PlayerShadow.bmp", 60, 60, true, RGB(255, 0, 255));

	_info.name = "Dos";
	_info.shadowImg = IMAGEMANAGER->findImage("playerShadow");
	_info.position = Vector2(1180, 720);
	_info.direction = PLAYER_DIRECTION::DOWN;
	_info.equipment = TOOLS::NONE;
	_state = make_shared<PlayerIdle>(this);
	_state->Init();
	_info.position = Vector2(WINSIZEX / 2 + 100, WINSIZEY / 2);
	_info.shadowCollision.centerSet(_info.position.x, _info.position.y, _info.img->getFrameWidth(), _info.img->getFrameHeight());
	_info.collision.centerSet(_info.position.x, _info.position.y + 150, _info.img->getFrameWidth(), _info.img->getFrameHeight());

	_info.maxHP = 100;
	_info.maxStamina = 100;
	_info.HP = 100;
	_info.stamina = 100;
	_info.money = 500;
	_info.velocity = 7.0f;
	_info.exMapName = "HOME";

	_tool = new ToolItemManager;
	_tool->SetNowTileMapMemoyrAddressLink(_Map);
	_tool->SetPlayerAddressLink(this);
	_tool->Init();
	_inven = new Inventory;
	//_inven->SetMemoryLinkedTool(_tool);
	_inven->init();


	_gauge = new HpStaminaBar;
	
	_gauge->setPlayerLink(this);
	_gauge->init();
	
	_inven->setPlayer(this);
	_haveItem = _inven->GetInvenItem(0);
	ChangeEquipment(_haveItem->GetToolEnum());
	
	return S_OK;
}

void Player::update()
{
	_info.doing = _tool->GetDoingFishing();
	_tool->SetFishingInfo(_info.position, _info.direction);
	//cout << "여기" << endl;

	if (KEYMANAGER->isOnceKeyDown('1')) 
	{
		_haveItem = _inven->GetInvenItem(0);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_haveItem = _inven->GetInvenItem(1);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('3')) 
	{
		_haveItem = _inven->GetInvenItem(2);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_haveItem = _inven->GetInvenItem(3);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_haveItem = _inven->GetInvenItem(4);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_haveItem = _inven->GetInvenItem(5);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_haveItem = _inven->GetInvenItem(6);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_haveItem = _inven->GetInvenItem(7);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_haveItem = _inven->GetInvenItem(8);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_haveItem = _inven->GetInvenItem(9);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS))
	{
		_haveItem = _inven->GetInvenItem(10);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS))
	{
		_haveItem = _inven->GetInvenItem(11);
		ChangeEquipment(_haveItem->GetToolEnum());
	}
	CheckTiles();
	if (_state->GetStateName() == "eating" )
	{
		_inven->Decrease();
	}
	_state->Update();
	_inven->update();
	_gauge->update();
	////////////////////////////////////
	//*********** 구현 테스트때만 풀도록/////
	//_inven->PlayerLootItem(_getItem);
	////////////////////////////////////
	
	Move();
	if (!_info.anim->isPlay())_info.anim->start();
	_tool->Update();
	// 아이템 줍는거
	for (int i = 0; i < _tool->GetSpreadList().size(); ++i)
	{
		if (isCollision(_info.shadowCollision, _tool->GetSpreadList()[i].col))
		{
			_tool->SetIsActive(false, i);
			_inven->PlayerLootItem(_tool->GetSpreadList()[i].name);
		}
	}
	if (_info.equipment == TOOLS::ACTIVEITEM || _info.equipment == TOOLS::EATITEM || _info.equipment == TOOLS::RESOURCEITEM)
	{
		ZORDER->ZOrderPush(getMemDC(), RenderType::RENDER, _haveItem->GetImageInven(), _info.shadowCollision.left - 20, _info.shadowCollision.top - 130, _info.shadowCollision.bottom);
	}
	ZORDER->ZOrderPush(getMemDC(), RenderType::KEYANIRENDER, _info.img ,_info.collision.left, _info.collision.top, _info.anim, _info.shadowCollision.bottom);
	
}

void Player::render()
{
	_inven->render();
	_gauge->hpBarRender();
	_gauge->staminaBarRender();
	_tool->Render("FishingRod");
	
}

void Player::release()
{
}



string Player::GetStateName()
{
	return _state->GetStateName(); 
}

void Player::ChangeState(shared_ptr<State> state)
{
	_state->Release();
	_state.swap(state);
	_state->Init();
}

void Player::Move()
{
	if (_state->GetStateTagName() == "move")
	{
		switch (_info.direction)
		{
		case PLAYER_DIRECTION::UP:
			_info.position.y -= _info.velocity;
			break;
		case PLAYER_DIRECTION::DOWN:
			_info.position.y += _info.velocity;
			break;
		case PLAYER_DIRECTION::RIGHT:
			_info.position.x += _info.velocity;
			break;
		case PLAYER_DIRECTION::LEFT:
			_info.position.x -= _info.velocity;
			break;
		case PLAYER_DIRECTION::UP_RIGHT:
			_info.position.x += _info.velocity * 0.6;
			_info.position.y -= _info.velocity * 0.6;
			break;
		case PLAYER_DIRECTION::UP_LEFT:
			_info.position.x -= _info.velocity * 0.6;
			_info.position.y -= _info.velocity * 0.6;
			break;
		case PLAYER_DIRECTION::DOWN_RIGHT:
			_info.position.x += _info.velocity * 0.6;
			_info.position.y += _info.velocity * 0.6;
			break;
		case PLAYER_DIRECTION::DOWN_LEFT:
			_info.position.x -= _info.velocity * 0.6;
			_info.position.y += _info.velocity * 0.6;
			break;
		default:
			break;
		}
	}
	_info.shadowCollision.centerSet(_info.position.x, _info.position.y, _info.shadowImg->getWidth() - 30, _info.shadowImg->getHeight() - 30);
	_info.collision.centerSet(_info.position.x, _info.position.y - 50, _info.img->getFrameWidth(), _info.img->getFrameHeight());
}

void Player::CheckTiles()
{
	int allTiles = _Map->GetMapSize();
	_playerTileX = _info.position.x / 64;
	_playerTileY = _info.position.y / 64;
	int playerTile = _playerTileX + _playerTileY * _Map->GetHorizon();
	_playerOnTileIndex = playerTile;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _state->GetStateTagName() != "acting")
	{
		_mousePt.x = _ptMouse.x + CAMERAMANAGER->getL();
		_mousePt.y = _ptMouse.y + CAMERAMANAGER->getT();

		Vector2 playerTileCenter = Vector2((_Map->GetTiles(playerTile).rc.right + _Map->GetTiles(playerTile).rc.left) * 0.5, (_Map->GetTiles(playerTile).rc.bottom + _Map->GetTiles(playerTile).rc.top) * 0.5);
		float distance = getDistance(playerTileCenter.x, playerTileCenter.y, _mousePt.x, _mousePt.y);
		if (distance > sqrtf(TILESIZE * TILESIZE * 10))
		{
			if(_state->GetStateName() != "swing")
			switch (_info.direction)
			{
			case PLAYER_DIRECTION::UP:
				_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				break;
			case PLAYER_DIRECTION::DOWN:
				_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				break;
			case PLAYER_DIRECTION::RIGHT:
				_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + 1;
				break;
			case PLAYER_DIRECTION::LEFT:
				_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - 1;
				break;
			default:
				break;
			}
			else
			{
				switch (_info.direction)
				{
				case PLAYER_DIRECTION::UP:
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					break;
				case PLAYER_DIRECTION::DOWN:
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					break;
				case PLAYER_DIRECTION::RIGHT:
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + 1;
					_actTileIndex[1] = (_playerTileX + _playerTileY + 1 * _Map->GetHorizon()) + 1;
					_actTileIndex[2] = (_playerTileX + _playerTileY  - 1* _Map->GetHorizon()) + 1;
					break;
				case PLAYER_DIRECTION::LEFT:
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - 1;
					_actTileIndex[1] = (_playerTileX + _playerTileY + 1 * _Map->GetHorizon()) - 1;
					_actTileIndex[1] = (_playerTileX + _playerTileY - 1 * _Map->GetHorizon()) - 1;
					break;
				default:
					break;
				}
			}
			for (int i = 0; i < 3; ++i)
			{
				if (_actTileIndex[i] <= 0 || _actTileIndex[i] >= allTiles)_actTileIndex[i] = 0;
			}
		}
		else if (distance < sqrtf(TILESIZE * TILESIZE * 5))
		{
			Vector2 chk =Vector2(floor(Vector2(_mousePt - playerTileCenter).Nomalized().x + 0.5), floor(Vector2(_mousePt - playerTileCenter).Nomalized().y + 0.5));
			if (_state->GetStateName() != "swing")
			{
				if (chk == Vector2::upRight)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::up)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::upLeft)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::downRight)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::down)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::downLeft)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::right)
				{
					_info.direction = PLAYER_DIRECTION::RIGHT;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + 1;
				}
				else if (chk == Vector2::left)
				{
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - 1;
					_info.direction = PLAYER_DIRECTION::LEFT;
				}
				if (_actTileIndex[0] <= 0 || _actTileIndex[0] >= allTiles)_actTileIndex[0] = 0;
			}
			else
			{
				if (chk == Vector2::upRight)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::up)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::upLeft)
				{
					_info.direction = PLAYER_DIRECTION::UP;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
				}
				else if (chk == Vector2::downRight)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::down)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::downLeft)
				{
					_info.direction = PLAYER_DIRECTION::DOWN;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[1] = (_playerTileX + 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
					_actTileIndex[2] = (_playerTileX - 1 + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
				}
				else if (chk == Vector2::right)
				{
					_info.direction = PLAYER_DIRECTION::RIGHT;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + 1;
					_actTileIndex[1] = (_playerTileX + (_playerTileY + 1) * _Map->GetHorizon()) + 1;
					_actTileIndex[2] = (_playerTileX + (_playerTileY - 1)* _Map->GetHorizon()) + 1;
				}
				else if (chk == Vector2::left)
				{
					_info.direction = PLAYER_DIRECTION::LEFT;
					_actTileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - 1;
					_actTileIndex[1] = (_playerTileX + (_playerTileY + 1) * _Map->GetHorizon()) - 1;
					_actTileIndex[2] = (_playerTileX + (_playerTileY - 1) * _Map->GetHorizon()) - 1;
				}
				if (_actTileIndex[0] <= 0 || _actTileIndex[0] >= allTiles)_actTileIndex[0] = 0;
			}
		}
	}

	switch (_info.direction)
	{
	case PLAYER_DIRECTION::UP:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		break;
	case PLAYER_DIRECTION::DOWN:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		break;
	case PLAYER_DIRECTION::RIGHT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + 1;
		_tileIndex[1] = (_playerTileX + (_playerTileY + 1) * _Map->GetHorizon()) + 1;
		_tileIndex[2] = (_playerTileX + (_playerTileY - 1) * _Map->GetHorizon()) + 1;
		break;
	case PLAYER_DIRECTION::LEFT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - 1;
		_tileIndex[1] = (_playerTileX + (_playerTileY + 1) * _Map->GetHorizon()) - 1;
		_tileIndex[2] = (_playerTileX + (_playerTileY - 1) * _Map->GetHorizon()) - 1;
		break;
	case PLAYER_DIRECTION::UP_RIGHT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX + 1) + _playerTileY * _Map->GetHorizon());
		break;
	case PLAYER_DIRECTION::UP_LEFT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon()) - _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon());
		break;
	case PLAYER_DIRECTION::DOWN_RIGHT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX + 1)  + _playerTileY * _Map->GetHorizon());
		break;
	case PLAYER_DIRECTION::DOWN_LEFT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[1] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon()) + _Map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _Map->GetHorizon());
		break;
	default:
		break;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		if ((_Map->GetTiles(_tileIndex[i]).collision && isCollision(_Map->GetTiles(_tileIndex[i]).rc, _info.shadowCollision)))
		{
			switch (_info.direction)
			{
			case PLAYER_DIRECTION::UP:
				_info.position.y += _info.velocity;
				break;
			case PLAYER_DIRECTION::DOWN:
				_info.position.y -= _info.velocity;
				break;
			case PLAYER_DIRECTION::RIGHT:
				_info.position.x -= _info.velocity;
				break;
			case PLAYER_DIRECTION::LEFT:
				_info.position.x += _info.velocity;
				break;
			case PLAYER_DIRECTION::UP_RIGHT:
				_info.position.y += _info.velocity;
				_info.position.x -= _info.velocity;
				break;
			case PLAYER_DIRECTION::UP_LEFT:
				_info.position.y += _info.velocity;
				_info.position.x += _info.velocity;
				break;
			case PLAYER_DIRECTION::DOWN_RIGHT:
				_info.position.y -= _info.velocity;
				_info.position.x -= _info.velocity;
				break;
			case PLAYER_DIRECTION::DOWN_LEFT:
				_info.position.y -= _info.velocity;
				_info.position.x += _info.velocity;
				break;
			default:
				break;
			}
		}
	}
	if (_Map->GetTiles()[_playerOnTileIndex].terrain == TERRAIN::GRASS && (_Map->GetTiles()[_playerOnTileIndex].object != MAPOBJECT::BUILDING))_playerSound = PLAYER_SOUND_TILES::GRASS;
	else if (_Map->GetTiles()[_playerOnTileIndex].terrain == TERRAIN::DIRT)_playerSound = PLAYER_SOUND_TILES::SOIL;
	else if (_Map->GetTiles()[_playerOnTileIndex].object == MAPOBJECT::BUILDING)_playerSound = PLAYER_SOUND_TILES::ROCK;
}

void Player::SavePlayerInfo(string fileName)
{
	HANDLE file;
	DWORD write;
	file = CreateFile(fileName.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &_info, sizeof(NecessaryInfo), &write, NULL);
	
	CloseHandle(file);
}

void Player::LoadPlayerInfo(string fileName)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(fileName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_info, sizeof(NecessaryInfo), &read, NULL);

	CloseHandle(file);
	_info.img = IMAGEMANAGER->findImage("player");
	this->SetImg("player");
	this->SetAnim("down_Idle_Player");
	this->SetShadowImg("playerShadow");
}