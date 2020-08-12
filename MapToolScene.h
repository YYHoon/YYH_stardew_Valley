#pragma once
#include "gameNode.h"

struct tagTile
{
	TERRAIN terrain;
	MAPOBJECT object;
	RECT rc;
	int terrainframeX;
	int terrainframeY;
	int objectframeX;
	int objectframeY;
	int wetframeX;
	int wetframeY;
	int autoIndex;
	bool collision;
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
	RECT rc;
	int terrainframeX;
	int terrainframeY;
};

class MapToolScene : public gameNode
{
private:
	image* _Mouse;
	CRTSELECT _crtSelect;

	tagSampleTile _sampleTile[15 * 8];
	tagCurrentTile _currentTile;

	Vector2 _Line;
	Vector2 _Ex;	// 마우스 드래그 시작 좌표

	RECT _draw;
	RECT _sampleArea;
	RECT _terrainBtn;
	RECT _treeBtn;
	RECT _buildingBtn;
	RECT _enemyBtn;
	RECT _collisionBtn;
	RECT _saveBtn;
	RECT _loadBtn;
	RECT _eraserBtn;
	RECT _exitBtn;

	int _count;
	int _horizontal;	//가로 타일
	int _vertical;		//세로 타일

	bool _drag;


	vector<tagTile>				_vtiles;
	vector<tagTile>::iterator	_vitiles;

public:
	MapToolScene();
	~MapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void SetUp();
	void SetSample(string img);

	void SetMap_L();
	void SetMap_R();
	void Save();
	void Load();
	void Auto();

	void Save(string fileName,int mapSizeX, int mapSizeY,vector<tagTile> tile);
	vector<tagTile> Load(string fileName, int mapSizeX, int mapSizeY);

	TERRAIN TerrainSelect(int frameX, int frameY);
	MAPOBJECT ObjectSelect(int frameX, int frameY);

	vector<tagTile> GetTile() { return _vtiles; }
	int GetVertical() { return _vertical; }
	int GetHorizontal() { return _horizontal; }
	void SetTileTerrain(int x, int y, TERRAIN terrain);
};