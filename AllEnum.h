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