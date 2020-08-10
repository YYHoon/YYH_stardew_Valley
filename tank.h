#pragma once
#include "gameNode.h"
#include "tileMap.h"

enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_UP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
	tileMap* _tileMap;
	image* _image;
	float _x, _y;
	float _speed;
	RECT _rc;
	TANKDIRECTION _direction;
	Vector2 _tileIndex;

public:
	tank();
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	void setTankPosition();

	void setTankMapMemoryAddressLink(tileMap* tm) { _tileMap = tm; }
	
	virtual Vector2 GetPlayerCenter() { return Vector2(_x, _y); }
	virtual Vector2 GetPlayerIndex() { return _tileIndex; }

};

