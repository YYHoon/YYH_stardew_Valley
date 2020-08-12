#pragma once

/// MapTool
enum class CRTSELECT
{
	TERRAINDRAW,
	WALLDRAW,
	HOETILEDRAW,
	TREEDRAW,
	BUILDINGDRAW,
	ENEMYDRAW,
	ERASER,
	COLLISION,
	SAVE,
	LOAD
};
enum class TERRAIN
{
	DIRT,
	GRASS,
	BOUNDARY,
	WATER,
	END
};
enum class MAPOBJECT
{
	TREE1,
	TREE2,
	TREE3,
	HOETILE,
	HOETILE_WET,
	WEED,
	ROCK,
	BRANCH,
	WALL,
	BUILDING,
	ENEMY,
	NONE
};

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

//////