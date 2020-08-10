#pragma once
//#include "stdafx.h"

//�� Ÿ���� ������� 32�� �д� 32 x 32
#define TILESIZE 32

//Ÿ�� ������ ���� 20�� ���� 20��
#define TILEX 20
#define TILEY 20

//Ÿ�� �� ������� 640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ�(Ÿ�� �ȷ�Ʈ) ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//Ÿ�Ͽ� �Ӽ��� �Űܺ���
//��� enum���� �ص� �ǰ� int ������ �ص� ��.

//��Ʈ�ʵ� -> ���� �޸� �Ʋ��Ʋ� ����Ѵٰ� ���̽���.
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISION	0x00000004
#define ATTR_FROZEN		0x00000008

//���� �Ӽ�
//�ø�Ʈ, ��, �ܵ�, ��
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ �Ӽ�
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//��ġ(������, �ƴ� ó���� ���� ��ġ ��)
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//����
	OBJECT obj;				//������Ʈ
	RECT rc;				//��Ʈ
	int terrainFrameX;		//Ÿ�� ��ȣ (�ִϸ��̼� �����Ӱ� ����)
	int terrainFrameY;
	int objFrameX;			//������Ʈ ��ȣ (���ϵ���)
	int objFrameY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
