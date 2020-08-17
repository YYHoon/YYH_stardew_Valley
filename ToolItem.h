#pragma once
#include "gameNode.h"
class MapMain;

//class DummyMap;//영향끼칠 맵

class ToolItem
{
protected:
	string _name="";		//이름
	string _tag="";		//태그 
	int _dmage=0;			//데미지
	int _tileIndex[3] = { 0, }; //상호작용할 타일의 인덱스 저장할곳
	bool _justSignal = false;//단일타일상호작용툴 체크
	bool _slashSignal = false;//범위타일상호작용 체크
	TOOLS _enumName = TOOLS::NONE;		//툴아이템의 이넘값
	int _number = 0;
	/// <summary>
	image* _imageI =nullptr;
	image* _imageC = nullptr;

	/// </summary>

	MAPOBJECT	_mapObject = MAPOBJECT::NONE;	//지형오브젝트의속성
	TERRAIN _mapTeeain = TERRAIN::NONE;			//지형타일의 속성
	MapMain* _map = nullptr;//영향줄맵

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

	//아이템개수
	virtual inline int GetNumber() { return _number;}
	virtual inline void SetNumber(int num) { _number = num; }

	//아이템이미지
	virtual inline image* GetImageInven() { return _imageI; }
	virtual inline image* GetImageChar() { return _imageC; }

	//툴아이템의 이넘값겟 
	virtual inline TOOLS GetToolEnum() { return _enumName; }
	virtual inline void SetToolEnum(TOOLS toolEnum) { _enumName = toolEnum; }

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

