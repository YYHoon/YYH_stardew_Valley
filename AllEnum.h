#pragma once

/// MapTool

enum class INOUT
{
	INDOOR,
	OUTDOOR
};
/// /////////////// 좌표 이넘
enum class POS
{
	COLLISION,
	PARM_TO_HOME,	//집들어가는 좌표
	PARM_TO_CAVE,	//동굴들어가는 좌표
	HOME_TO_PARM,	//집에서 농장
	CAVE_TO_PARM,	//동굴에서 농장
	BED,			//침대
	NPC,			//NPC
	ENEMY,			//몹
	NONE
};

enum class CRTSELECT
{
	TERRAINDRAW,
	TERRAINDRAW_INDOOR,
	TERRAINDRAW_CAVE,
	WALLDRAW,
	HOETILEDRAW,
	TREEDRAW,
	BUILDINGDRAW,
	ENEMYDRAW,
	ERASER,
	COLLISION,
	SAVE,
	LOAD,
	NONE
};
enum class TERRAIN
{
	DIRT,	
	GRASS,
	WATER,
	WOODEN,
	WOODENWALL,
	NONE
};
enum class MAPOBJECT
{
	TREE1,
	TREE2,
	TREE3,			//나무
	HOETILE,		//농사땅
	HOETILE_WET,	//농사땅젖은거
	WEED,			//풀
	ROCK,			//돌
	BRANCH,			//나뭇가지
	WALL,			//벽
	BUILDING,		//건물
	BED,
	//ENEMY,			//에너미
	NONE
};
//--------------------------------------------------------------
// Player
enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	EXHAUST,
	ACTING,
	END
};

enum class PLAYER_DIRECTION
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
	END
};

enum class TOOLS
{
	PICK,
	HOE,
	SICKLE,
	AXE,
	FISHINGROD,
	SWORD,
	ITEM,
	WATERING_CAN,
	ACTIVEITEM,
	EATITEM,
	RESOURCEITEM,
	NONE,
	END
};

enum class PLAYER_ACTION
{
	PLOWING,
	EATING,		//처먹기 (소모품 : 음식류) 타일검색 X
	MINING,		//광물질 (도구 : 곡괭이) 상호 작용할 타일 지형 && 오브젝트; 타일 검색범위 1칸; 1. 지형 : 개간된땅; 2. 오브젝트 : 돌, 씨앗, 작물 지지대, 풀;
	GATHERING,	//채집	(ALL)	상호작용할 오브젝트 : 작물; 가구; 범위 : 전방 범위 1칸
	FELLING,	//벌목	(도구 : 도끼) 상호작용할 오브젝트 : 나무, 씨앗, 작물 지지대, 풀; 범위 : 전방 범위 1칸
	PLANTING,	//심기	(소모품 : 씨앗 || 가구 || 솔방울) 터레인 상호작용;  상호작용할 터레인 씨앗 && 작물 지지대 : 개간된땅; 가구 : 마루바닷, 솔방울 : 사유지내의 터레인
	FISHING,	//낚시질	(도구 : 낚싯대)
	SWING,		//휘두르기 (도구 : 낫, 검) 오브젝트 상호작용; 상호작용할 오브젝트 : 잡초, 잔디; 범위 : 휘두르는 방향 3칸;
	END
};

enum class FISHING
{
	FIRST,			//0.낚시 초기화
	CHARGE,			//1.낚시 기모으기
	SHOT,			//2.찌던지기
	WAIT,			//3.물고기낚일떄까지 기다리기
	MINiGAMEON,		//4.물고기 입질왔을때
	DOINGMINIGAME,	//5.낚시 게임도중
	MISS,			//6.물고기 놓쳤을때
	SUCCESS,		//7.물고기 잡는데 성공했을때
	NONE			//8.혹시 모를 아무상태도 아닐때
};

enum class Spread
{
	SPREAD,			//흩뿌릴때
	HARVEST,		//수확할때
	FISHING,			//낚시할때
	NONE
};
enum class SpreadState
{
	BEFORE_SPREAD,	//뿌리기직전
	DOING_SPREAD,	//뿌리는중
	AFTER_SPREAD,	//뿌리고나서
	NONE
};

enum class ATTRIBUTE
{
	NONE,
	START,
	WALL,
	PLAYER,
	ENEMY,
	NPC,
	END
};