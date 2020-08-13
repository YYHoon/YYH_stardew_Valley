#pragma once
#include "gameNode.h"
#include"DummyMap.h"
class MapMain;

//class DummyMap;//영향끼칠 맵

class ToolItem
{
protected:
	string _name;
	string _tag;
	int _dmage;
	Vector2 _impactIndex[3];
	int _tileIndex[3]; //상호작용할 타일의 인덱스 저장할곳
	bool _justSignal = false;
	bool _slashSignal = false;

	MAPOBJECT	_mapObject = MAPOBJECT::NONE;	//지형오브젝트의속성
	MapMain* _map;//영향줄맵

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
	//virtual inline Vector2 GetImpactIndexCenter() { return _impactIndex[0]; }
	//virtual inline Vector2 GetImpactIndexLeft() { return _impactIndex[1]; }
	//virtual inline Vector2 GetImpactIndexRight() { return _impactIndex[2]; }
	//virtual inline void SetImpactIndex(Vector2 index) { _impactIndex[0] = index; }
	//virtual inline void SetImpactIndex(Vector2 Center, Vector2 left, Vector2 right) {
	//	_impactIndex[0] = Center;
	//	_impactIndex[1] = left;
	//	_impactIndex[2] = right;
	//}
	virtual inline int GetImpactTileIndexCenter() { return _tileIndex[0]; }
	virtual inline int GetImpactTileIndexLeft() { return _tileIndex[1]; }
	virtual inline int GetImpactTileIndexRight() { return _tileIndex[2]; }
	virtual inline void SetImpactTileIndex(int center){_tileIndex[0] = center;}
	virtual inline void SetImpactTileIndex(int center, int left, int right)
	{
		_tileIndex[0] = center;
		_tileIndex[1] = left;
		_tileIndex[2] = right;
	}
	//타일변경 신호주는곳
	virtual inline bool GetTileChangeSignalJust() { return _justSignal; }
	virtual inline bool GetTileChangeSignalSlash() { return _slashSignal; }

	//타일속성 주고받는곳
	
	virtual inline MAPOBJECT GetMapObject() { return _mapObject; }
	virtual inline void SetMapObject(MAPOBJECT mapobj) { _mapObject = mapobj; }
	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void ReAction() = 0;
	inline void SetNowMapMemoryAddressLink(MapMain* dmap) { _map = dmap; }
};

