#pragma once
class GameObject
{
protected:
	Synthesize(string, mName, Name)
	Synthesize(POINT_FLOAT, mPosition, Position)
	Synthesize(POINT_FLOAT, mSize, Size)
	Synthesize(MYRECT, mRect, Rect)
	Synthesize(bool, mActive, Active)


public:

	GameObject() {};
	~GameObject() {};
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

