#include "stdafx.h"
#include "Player.h"
#include "State.h"

HRESULT Player::init()
{
	_info.name = "Dos";
	_info.position = Vector2(10, 10);
	_info.direction = PLAYER_DIRECTION::UP;
	_info.equipment = TOOLS::AXE;
	_state = make_shared<PlayerIdle>(this);
	_state->Init();
	_info.position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	_info.collision.centerSet(_info.position.x, _info.position.y, _info.img->getFrameWidth(), _info.img->getFrameHeight());
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
	
	_state->Update();
	Move();
	if (!_info.anim->isPlay())_info.anim->start();
	KEYANIMANAGER->update();

}

void Player::render()
{
	_info.collision.render(getMemDC());
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
	if ( _state->GetStateName() == "move" || _state->GetStateName() == "itemMove")
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
	_info.collision.centerSet(_info.position.x, _info.position.y, _info.img->getFrameWidth(), _info.img->getFrameHeight());
}
