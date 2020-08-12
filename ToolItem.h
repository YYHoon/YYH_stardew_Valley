#pragma once
#include "gameNode.h"

class ToolItem
{
protected:
	string _name;
	string _tag;
	int _dmage;
	Vector2 _impactIndex[3];


public:
	ToolItem() { ; }
	virtual ~ToolItem() { ; }

	//네임
	virtual inline string GetName() { return _name; }
	virtual inline void SetName(string name) { _name = name; }
	
	//태그
	virtual inline string GetTag() { return _tag; }
	virtual inline void SetTag(string tag) { _tag = tag; }
	
	//데미지
	virtual inline int GetDmage() { return _dmage; }
	virtual inline void SetDmage(int dmg) { _dmage = dmg; }

	//효과위치 좌표
	virtual inline Vector2 GetImpactIndexCenter() { return _impactIndex[0]; }
	virtual inline Vector2 GetImpactIndexLeft() { return _impactIndex[1]; }
	virtual inline Vector2 GetImpactIndexRight() { return _impactIndex[2]; }
	virtual inline void SetImpactIndex(Vector2 index) { _impactIndex[0] = index; }
	virtual inline void SetImpactIndex(Vector2 Center, Vector2 left, Vector2 right) {
		_impactIndex[0] = Center;
		_impactIndex[1] = left;
		_impactIndex[2] = right;
	}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void ReAction() = 0;
};