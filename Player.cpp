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
	_state->Update();
	Move();
	if (!_info.anim->isPlay())_info.anim->start();
	KEYANIMANAGER->update();

}

void Player::render()
{
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
		cout << isCollision(_map->GetTiles(_tileIndex).rc, _info.shadowCollision) << endl;
		if (!_map->GetTiles(_tileIndex).collision || !isCollision(_map->GetTiles(_tileIndex).rc, _info.shadowCollision))
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
			default:
				break;
			}
		}
	}

	_info.shadowCollision.centerSet(_info.position.x, _info.position.y, _info.shadowImg->getWidth(), _info.shadowImg->getHeight());
	_info.collision.centerSet(_info.position.x, _info.position.y - 50, _info.img->getFrameWidth(), _info.img->getFrameHeight());
}

void Player::CheckTiles()
{
	int allTiles = _map->GetHorizon() * _map->GetVertical();
	_playerTileX = _info.position.x / 64;
	_playerTileY = _info.position.y / 64;
	
		
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_mousePt.x = _ptMouse.x;
		_mousePt.y = _ptMouse.y;

		float distance = _mousePt.Distance(_mousePt, Vector2((_map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.right - _map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.left) * 0.5,
			(_map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.top - _map->GetTiles(_playerTileX + _playerTileY * _map->GetHorizon()).rc.bottom) * 0.5), true);
		if (distance > sqrtf(TILESIZE * TILESIZE * 2))
		{
			// 보는방향 찍고
			switch (_info.direction)
			{
			case PLAYER_DIRECTION::UP:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				cout << _actTileIndex << endl;
				break;
			case PLAYER_DIRECTION::DOWN:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				cout << _actTileIndex << endl;
				break;
			case PLAYER_DIRECTION::RIGHT:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + 1;
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				cout << _actTileIndex << endl;
				break;
			case PLAYER_DIRECTION::LEFT:
				_actTileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - 1;
				if (_actTileIndex <= 0 || _actTileIndex >= allTiles)_actTileIndex = 0;
				cout << _actTileIndex << endl;
				break;
			default:
				break;
			}

		}
		else if (distance == sqrtf(TILESIZE * TILESIZE * 2 ))
		{
			Vector2 vDistance(_mousePt - _info.position);
			if (vDistance.Nomalized() == Vector2::up)
			{

			}
			// 79 13
			// 니가 원하는위치 찍는다 ㅋㅋ
			// 789  위보고 4 왼 6 우  123 아래보기
		}
		else
		{

		}
		
	}



	switch (_info.direction)
	{
	case PLAYER_DIRECTION::UP:
		_tileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - _map->GetHorizon();
		if (_tileIndex <= 0 || _tileIndex >= allTiles)_tileIndex = 0;
		break;
	case PLAYER_DIRECTION::DOWN:
		_tileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + _map->GetHorizon();
		if (_tileIndex <= 0 || _tileIndex >= allTiles)_tileIndex = 0;
		break;
	case PLAYER_DIRECTION::RIGHT:
		_tileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) + 1;
		if (_tileIndex <= 0 || _tileIndex >= allTiles)_tileIndex = 0;
		break;
	case PLAYER_DIRECTION::LEFT:
		_tileIndex = (_playerTileX + _playerTileY * _map->GetHorizon()) - 1;
		if (_tileIndex <= 0 || _tileIndex >= allTiles)_tileIndex = 0;
		break;
	default:
		break;
	}
}
