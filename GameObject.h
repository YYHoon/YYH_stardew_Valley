#pragma once
#include"gameNode.h"
class GameObject : public gameNode
{
protected:
	Synthesize(string, _name, Name)
	Synthesize(string, _type, Type)
	Synthesize(Vector2, _position, Position)
	Synthesize(Vector2, _size, Size)
	Synthesize(TTYONE_UTIL::MYRECT, _rect, Rect)
	Synthesize(RECT, _rc, Rc)
	Synthesize(bool, _active, Active)
	Synthesize(image*,_img,Image);

public:
	GameObject() {};
	~GameObject() {};
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() {};
	virtual void Render() {};
};

