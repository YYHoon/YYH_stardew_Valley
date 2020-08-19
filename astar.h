#pragma once
#include "gameNode.h"
#include"MapMain.h"
class node
{
public:
	RECT _rc;
	Vector2 _idx;
	Vector2 _center;
	float _totalCost; // F = G + H
	float _costFromStart; // G = 시작부터 현재까지의 값
	float _costToGoal; // H = 현재부터 마지막까지의 값
	ATTRIBUTE _attribute;
	bool _isopen;
	node* _parentNode;
	node();
	node(int x, int y)
	{
		_idx = Vector2(x, y);
		_center = Vector2(_idx.x * TILESIZE + (TILESIZE * 0.5), _idx.y * TILESIZE + (TILESIZE * 0.5));
		_rc = RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);
		_totalCost = _costFromStart = _costToGoal = 0;
		_isopen = false;
		_parentNode = nullptr;
		_attribute = ATTRIBUTE::NONE;
	}
};
class astar : public gameNode
{
private:
	vector<node*> _vtotalList; // 타일 전체
	vector<node*> _vopenList;  // 갈 수 있는 타일
	vector<node*> _vcloseList;
	vector<node*> _vpathList;  // 현재부터 도착까지의 타일 
	
	node* _startNode;
	node* _currentNode;
	node* _endNode;

	MapMain* _map;
	int _mapSize;
	// 우 , 하, 상, 좌, 
	int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	//우하, 좌하, 좌상, 우상
	int diagonal[4][2] = { {1,1},{-1,1},{-1,-1},{1,-1} };
	bool _isFind;      // 찾았는지
public:
	HRESULT init();
	void release();
	void update();
	void render();


	void PathFind();
	void AddOpenList(Vector2 idx);
	void AddOpenListDiagonal(Vector2 idx);
	void SetMap()
	{
		_mapSize = _map->GetVertical() * _map->GetHorizon();
		for (int i = 0; i < _map->GetVertical(); ++i)
		{
			for (int j = 0; j < _map->GetHorizon(); ++j)
			{
				_vtotalList.push_back(new node(j, i));
				if (_map->GetTiles(i * _map->GetHorizon() + j).collision)
					_vtotalList[i * _map->GetHorizon() + j]->_attribute = ATTRIBUTE::WALL;
			}
		}
	}
	void SetStartNode(Vector2 startIndex);
	void SetEndNode(Vector2 endIndex);
	void SetNodeColor(node* node, COLORREF color);
	void SetAttributeNode(Vector2 nowIdx, Vector2 moveIdx ,ATTRIBUTE att);
	void SetMapMemoryLink(MapMain* map) { _map = map; }
};

