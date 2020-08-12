#include "stdafx.h"
#include "Player.h"
#include "State.h"
#include "DummyMap.h"

HRESULT Player::init()
{
	IMAGEMANAGER->addImage("playerShadow", "image/PlayerShadow.bmp", 60, 60, true, RGB(255, 0, 255));

	_info.name = "Dos";
	_info.shadowImg = IMAGEMANAGER->findImage("playerShadow");
	_info.position = Vector2(10, 10);
	_info.direction = PLAYER_DIRECTION::UP;
	_info.equipment = TOOLS::AXE;
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
	_info.velocity = 10.0f;
	_isKeyDown = false;

	_tool = new ToolItemManager;
	_test = new MiniGame;//미니게임 테스트용

	return S_OK;
}

void Player::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))ChangeEquipment(TOOLS::AXE);
	else if (KEYMANAGER->isOnceKeyDown('2'))ChangeEquipment(TOOLS::HOE);
	else if (KEYMANAGER->isOnceKeyDown('3'))ChangeEquipment(TOOLS::SICKLE);
	else if (KEYMANAGER->isOnceKeyDown('4'))ChangeEquipment(TOOLS::WATERING_CAN);
	else if (KEYMANAGER->isOnceKeyDown('5'))ChangeEquipment(TOOLS::ITEM);
	else if (KEYMANAGER->isOnceKeyDown('6'))ChangeEquipment(TOOLS::SWORD);
	else if (KEYMANAGER->isOnceKeyDown('7'))ChangeEquipment(TOOLS::PICK);

	CheckTiles();
	//===========미니게임 테스트용
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_test->InitKeyDown(_info.direction, _info.position);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))_test->InitKeyUp();
	//=========================

	_state->Update();
	Move();
	if (!_info.anim->isPlay())_info.anim->start();

	//_tool->Action("Pickax");

}

void Player::render()
{
	CAMERAMANAGER->rectangle(getMemDC(), _info.shadowCollision);

	_info.shadowImg->render(getMemDC(), _info.shadowCollision.left, _info.shadowCollision.top);
	_info.img->aniRender(getMemDC(), _info.collision.left, _info.collision.top, _info.anim);

}

void Player::release()
{
}


void Player::ChangeState(shared_ptr<State> state)
{
	_state->Release();
	_state.swap(state);
	_state->Init();
}

void Player::Move()
{
	if (_state->GetStateName() == "move" || _state->GetStateName() == "itemMove")
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
			_info.position.x += _info.velocity * 0.5;
			_info.position.y -= _info.velocity * 0.5;
			break;
		case PLAYER_DIRECTION::UP_LEFT:
			_info.position.x -= _info.velocity * 0.5;
			_info.position.y -= _info.velocity * 0.5;
			break;
		case PLAYER_DIRECTION::DOWN_RIGHT:
			_info.position.x += _info.velocity * 0.5;
			_info.position.y += _info.velocity * 0.5;
			break;
		case PLAYER_DIRECTION::DOWN_LEFT:
			_info.position.x -= _info.velocity * 0.5;
			_info.position.y += _info.velocity * 0.5;
			break;
		default:
			break;
		}
	}

	_info.shadowCollision.centerSet(_info.position.x, _info.position.y, _info.shadowImg->getWidth(), _info.shadowImg->getHeight());
	_info.collision.centerSet(_info.position.x, _info.position.y - 50, _info.img->getFrameWidth(), _info.img->getFrameHeight());
	_info.shadowCollision.left += 2;
	_info.shadowCollision.right -= 2;
	_info.shadowCollision.top += 2;
	_info.shadowCollision.bottom -= 2;
}

void Player::CheckTiles()
{
	int allTiles = _map->GetMapSize();
	_playerTileX = _info.position.x / 64;
	_playerTileY = _info.position.y / 64;



	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_mousePt.x = _ptMouse.x;
		_mousePt.y = _ptMouse.y;

		int playerTile = _playerTileX + _playerTileY * _map->GetHorizon();
		Vector2 playerTileCenter = Vector2((_map->GetTiles(playerTile).rc.right + _map->GetTiles(playerTile).rc.left) * 0.5, (_map->GetTiles(playerTile).rc.bottom + _map->GetTiles(playerTile).rc.top) * 0.5);
		cout << floor(Vector2( _mousePt- playerTileCenter).Nomalized().x + 0.5)<<" "<< floor(Vector2( _mousePt- playerTileCenter).Nomalized().y+0.5) << endl;
		/*float distance = _mousePt.Distance(_mousePt, Vector2((_map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.right - _map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.left) * 0.5,
			(_map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.top - _map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.bottom) * 0.5), true);*/
		float distance = getDistance(playerTileCenter.x, playerTileCenter.y, _mousePt.x, _mousePt.y);
		if (distance > sqrtf(TILESIZE * TILESIZE * 2))
		{
			cout << "왜 이것만 나오누?" << endl;
			// 보는방향 찍고
			switch (_info.direction)
			{
			case PLAYER_DIRECTION::UP:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				break;
			case PLAYER_DIRECTION::DOWN:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				break;
			case PLAYER_DIRECTION::RIGHT:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + 1;
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				break;
			case PLAYER_DIRECTION::LEFT:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - 1;
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				break;
			default:
				break;
			}

		}
		else if (distance < sqrtf(TILESIZE * TILESIZE * 2))
		{
			Vector2 chk =Vector2(floor(Vector2(_mousePt - playerTileCenter).Nomalized().x + 0.5), floor(Vector2(_mousePt - playerTileCenter).Nomalized().y + 0.5));
			
			if (chk == Vector2::upRight || chk == Vector2::up || chk == Vector2::upLeft)
			{
				_info.direction = PLAYER_DIRECTION::UP;
			}
			else if(chk == Vector2::downRight || chk == Vector2::down || chk == Vector2::downLeft)
			{
				_info.direction = PLAYER_DIRECTION::DOWN;
			}
			else if (chk == Vector2::right) 
			{
				_info.direction = PLAYER_DIRECTION::RIGHT;
			}
			else if (chk == Vector2::left)
			{
				_info.direction = PLAYER_DIRECTION::LEFT;
			}
			//_info.direction = PLAYER_DIRECTION::UP;
			//_info.direction = PLAYER_DIRECTION::DOWN;
			//_info.direction = PLAYER_DIRECTION::DOWN;
			_actTileIndex = (_mousePt.x + _mousePt.y * _map->GetHorizon());
			if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;

		}
		else
		{

		}
	}



	switch (_info.direction)
	{
	case PLAYER_DIRECTION::UP:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
		break;
	case PLAYER_DIRECTION::DOWN:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
		break;
	case PLAYER_DIRECTION::RIGHT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) + 1;
		_tileIndex[1] = (_playerTileX + (_playerTileY + 1) * _map->GetHorizon()) + 1;
		_tileIndex[2] = (_playerTileX + (_playerTileY - 1) * _map->GetHorizon()) + 1;
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
		break;
	case PLAYER_DIRECTION::LEFT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) - 1;
		_tileIndex[1] = (_playerTileX + (_playerTileY + 1) * _map->GetHorizon()) - 1;
		_tileIndex[2] = (_playerTileX + (_playerTileY - 1) * _map->GetHorizon()) - 1;
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
		break;
	case PLAYER_DIRECTION::UP_RIGHT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		_tileIndex[1] = ((_playerTileX + 1) + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		_tileIndex[2] = ((_playerTileX - 1) + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
		break;
	case PLAYER_DIRECTION::UP_LEFT:
		_tileIndex[0] = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		_tileIndex[1] = (_playerTileX + (_playerTileY + 1) * _map->GetHorizon()) - 1;
		_tileIndex[2] = (_playerTileX + (_playerTileY - 1) * _map->GetHorizon()) - 1;
		for (int i = 0; i < 3; ++i)
		{
			if (_tileIndex[i] <= 0 || _tileIndex[i] >= allTiles)_tileIndex[i] = 0;
		}
	default:
		break;
	}

	for (int i = 0; i < 3; ++i)
	{
		if ((_map->GetTiles(_tileIndex[i]).collision && isCollision(_map->GetTiles(_tileIndex[i]).rc, _info.shadowCollision)))
		{
			switch (_info.direction)
			{
			case PLAYER_DIRECTION::UP:
				_info.velocity = 0;
				_info.position.y += 1;
				break;
			case PLAYER_DIRECTION::DOWN:
				_info.velocity = 0;
				_info.position.y -= 1;
				break;
			case PLAYER_DIRECTION::RIGHT:
				_info.velocity = 0;
				_info.position.x -= 1;
				break;
			case PLAYER_DIRECTION::LEFT:
				_info.velocity = 0;
				_info.position.x += 1;
				break;
			case PLAYER_DIRECTION::UP_RIGHT:
				_info.velocity = 0;
				break;
			case PLAYER_DIRECTION::UP_LEFT:
				_info.velocity = 0;
				break;
			case PLAYER_DIRECTION::DOWN_RIGHT:
				_info.velocity = 0;
				break;
			case PLAYER_DIRECTION::DOWN_LEFT:
				_info.velocity = 0;
				break;
			case PLAYER_DIRECTION::END:
				break;
			default:
				break;
			}
		}
	}

}
