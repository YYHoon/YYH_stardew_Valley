#pragma once

/// MapTool

enum class INOUT
{
	INDOOR,
	OUTDOOR
};
/// /////////////// ��ǥ �̳�
enum class POS
{
	HOME,		//������ ��ǥ
	CAVE,		//�������� ��ǥ
	HTOPARM,	//������ ����
	CTOPARM,	//�������� ����
	BED,		//ħ��
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
	NONE
};
enum class MAPOBJECT
{
	TREE1,
	TREE2,
	TREE3,			//����
	HOETILE,		//��綥
	HOETILE_WET,	//��綥������
	WEED,			//Ǯ
	ROCK,			//��
	BRANCH,			//��������
	WALL,			//��
	BUILDING,		//�ǹ�
	ENEMY,			//���ʹ�
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
	NONE,
	END
};

enum class PLAYER_ACTION
{
	PLOWING,
	EATING,		//ó�Ա� (�Ҹ�ǰ : ���ķ�) Ÿ�ϰ˻� X
	MINING,		//������ (���� : ���) ��ȣ �ۿ��� Ÿ�� ���� && ������Ʈ; Ÿ�� �˻����� 1ĭ; 1. ���� : �����ȶ�; 2. ������Ʈ : ��, ����, �۹� ������, Ǯ;
	GATHERING,	//ä��	(ALL)	��ȣ�ۿ��� ������Ʈ : �۹�; ����; ���� : ���� ���� 1ĭ
	FELLING,	//����	(���� : ����) ��ȣ�ۿ��� ������Ʈ : ����, ����, �۹� ������, Ǯ; ���� : ���� ���� 1ĭ
	PLANTING,	//�ɱ�	(�Ҹ�ǰ : ���� || ���� || �ֹ��) �ͷ��� ��ȣ�ۿ�;  ��ȣ�ۿ��� �ͷ��� ���� && �۹� ������ : �����ȶ�; ���� : ����ٴ�, �ֹ�� : ���������� �ͷ���
	FISHING,	//������	(���� : ���˴�)
	SWING,		//�ֵθ��� (���� : ��, ��) ������Ʈ ��ȣ�ۿ�; ��ȣ�ۿ��� ������Ʈ : ����, �ܵ�; ���� : �ֵθ��� ���� 3ĭ;
	END
};

//////