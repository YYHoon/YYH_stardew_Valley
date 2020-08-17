#pragma once
#include "gameNode.h"
#include "TileRender.h"

class MapToolScene : public gameNode
{
private:
	TileRender* _tileRender;

	image* _Mouse;
	CRTSELECT _crtSelect;
	INOUT _inout;

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
	RECT _saveBtn[3];
	RECT _loadBtn;
	RECT _eraserBtn;
	RECT _inBtn;
	RECT _outBtn;
	RECT _upBtn;
	RECT _downBtn;
	RECT _exitBtn;
	RECT _f1Btn;

	int _count;
	int _terrainPage;
	int _horizontal;	//가로 타일
	int _vertical;		//세로 타일

	bool _drag;
	bool _Window;
	bool _saveimg;

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

	void InToOut(int Horizontal, int Vertical);
	void OutToIn(int Horizontal, int Vertical);
	void SetMap_L();
	void SetMap_R();

	void Auto();
	void Button();

	void Save(string fileName,int mapSizeX, int mapSizeY,vector<tagTile> tile);
	vector<tagTile> Load(string fileName, int mapSizeX, int mapSizeY);

	TERRAIN TerrainSelect(int frameX, int frameY);
	MAPOBJECT ObjectSelect(int frameX, int frameY);
	POS PosSelect(int frameX, int frameY);

	vector<tagTile> GetTile() { return _vtiles; }
	int GetVertical() { return _vertical; }
	int GetHorizontal() { return _horizontal; }
	void SetTileTerrain(int x, int y, TERRAIN terrain);
};