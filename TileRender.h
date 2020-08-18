#pragma once
#include "gameNode.h"

struct tagTile
{
	TERRAIN terrain;
	MAPOBJECT object;
	POS pos;
	RECT rc;
	int terrainframeX;
	int terrainframeY;
	int objectframeX;
	int objectframeY;
	int wetframeX;
	int wetframeY;
	int autoIndex;
	int autoIndex_2;
	int hp;
	bool collision;
	bool wet;
};
struct tagSampleTile
{
	RECT rc;
	int terrainframeX;
	int terrainframeY;
};
struct tagCurrentTile
{
	TERRAIN terrain;
	MAPOBJECT object;
	POS pos;
	RECT rc;
	int terrainframeX;
	int terrainframeY;
};

class TileRender : public gameNode
{
private:
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(int horizontal, int vertical, INOUT inout, vector<tagTile> tile);
	virtual void render(int horizontal, int vertical, INOUT inout, vector<tagTile> tile);

	void AutoHoe(int horizontal, int vertical, INOUT inout, vector<tagTile> tile);
};

