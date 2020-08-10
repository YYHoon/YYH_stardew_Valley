#pragma once
//#include "stdafx.h"

//한 타일의 사이즈는 32로 둔다 32 x 32
#define TILESIZE 32

//타일 갯수는 가로 20개 세로 20개
#define TILEX 20
#define TILEY 20

//타일 총 사이즈는 640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋(타일 팔레트) 범위
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//타일에 속성을 매겨보자
//사실 enum으로 해도 되고 int 값으로 해도 됨.

//비트필드 -> 과거 메모리 아껴아껴 사용한다고 많이썼음.
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISION	0x00000004
#define ATTR_FROZEN		0x00000008

//지형 속성
//시멘트, 모래, 잔디, 물
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트 속성
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//위치(리스폰, 아님 처음에 생성 위치 등)
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//지형
	OBJECT obj;				//오브젝트
	RECT rc;				//렉트
	int terrainFrameX;		//타일 번호 (애니메이션 프레임과 동일)
	int terrainFrameY;
	int objFrameX;			//오브젝트 번호 (이하동문)
	int objFrameY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
