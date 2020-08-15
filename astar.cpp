#include "stdafx.h"
#include "astar.h"

HRESULT astar::init()
{

	return S_OK;
}

void astar::release()
{
}

void astar::update()
{
}

void astar::render()
{
	if (_startNode != nullptr) { SetNodeColor(_startNode, RGB(255, 0, 0)); }
	if (_endNode != nullptr) { SetNodeColor(_endNode, RGB(0, 0, 255)); }
	//길찾았을때 보여주기
	if (_isFind)
	{
		for (int i = 0; i < _vpathList.size(); i++)
		{
			SetNodeColor(_vpathList[i], RGB(255, 255, 0));
			
		}
	}
}

void astar::PathFind()
{
	if (!_startNode || !_endNode) return;
	_vopenList.clear();
	_vcloseList.clear();
	_vpathList.clear();

	_currentNode = _startNode;
	_vcloseList.push_back(_startNode);
	while (true)
	{
		if (_currentNode == _endNode)
		{
			node* tmp = _endNode;
			while (tmp->_parentNode != nullptr)
			{
				_vpathList.push_back(tmp);
				tmp = tmp->_parentNode;
			}
			reverse(_vpathList.begin(), _vpathList.end());
			_isFind = true;
			return;
		}
		
		for (int i = 0;i < 4;i++)
		{
			AddOpenList(Vector2(_currentNode->_idx.x+dir[i][0], _currentNode->_idx.y+dir[i][1]));
			AddOpenListDiagonal(Vector2(diagonal[i][0], diagonal[i][1]));
		}

		if (_vopenList.empty()) return;
		
		int cost = 9999999;
		int index = 0;
		for (int i = 0; i < _vopenList.size(); ++i)
		{
			if (_vopenList[i]->_totalCost < cost)
			{
				cost = _vopenList[i]->_totalCost;
				index = i;
			}
		}
		_currentNode = _vopenList[index];
		_vcloseList.push_back(_vopenList[index]);
		_vopenList.erase(_vopenList.begin() + index);
	}
}

void astar::AddOpenList(Vector2 idx)
{
	if (idx.x<0 || idx.x>=_map->GetHorizon() || idx.y < 0 || idx.y >= _map->GetVertical()) return;

	if (_vtotalList[idx.y * _map->GetHorizon() + idx.x]->_attribute == ATTRIBUTE::WALL) return;

	for (int i = 0; i < _vcloseList.size(); ++i)
	{
		if (_vtotalList[idx.y * _map->GetHorizon() + idx.x] == _vcloseList[i]) return;
	}
	
	node* tempNode = _vtotalList[idx.y * _map->GetHorizon() + idx.x]; 

	int gCost = _currentNode->_costFromStart + ((_currentNode->_idx.x  - idx.x == 0 || _currentNode->_idx.y - idx.y == 0) ? 10 : 14);

	for (int i = 0; i < _vopenList.size(); ++i)
	{
		if (_vopenList[i] == tempNode) return;
	}
	
	tempNode->_costFromStart = gCost;
	tempNode->_costToGoal = (abs(tempNode->_idx.x - _endNode->_idx.x) + abs(tempNode->_idx.y - _endNode->_idx.y)) * 10;
	tempNode->_totalCost = tempNode->_costFromStart + tempNode->_costToGoal;
	tempNode->_parentNode = _currentNode;
	_vopenList.push_back(tempNode);
}

void astar::AddOpenListDiagonal(Vector2 idx)
{
	if (!_map->GetTiles()[_currentNode->_idx.x + idx.x + _currentNode->_idx.y * _map->GetHorizon()].collision &&
		!_map->GetTiles()[_currentNode->_idx.x + (_currentNode->_idx.y + idx.y) * _map->GetHorizon()].collision &&
		!_map->GetTiles()[_currentNode->_idx.x + idx.x + (_currentNode->_idx.y + idx.y) * _map->GetHorizon()].collision)
		AddOpenList(Vector2(_currentNode->_idx.x + idx.x, _currentNode->_idx.y + idx.y));
}

void astar::SetStartNode(Vector2 startIndex)
{
	int index = _map->GetHorizon() * startIndex.y + startIndex.x;
	if (_startNode)
	{
		_vtotalList[_startNode->_idx.y * _map->GetHorizon() + _startNode->_idx.x]->_attribute = ATTRIBUTE::NONE;
	}
	_startNode = _vtotalList[index];
	_startNode->_attribute = ATTRIBUTE::START;
}

void astar::SetEndNode(Vector2 endIndex)
{
	int index = _map->GetHorizon() * endIndex.y + endIndex.x;
	
	if (_endNode)
	{
		_vtotalList[_endNode->_idx.y * _map->GetHorizon() + _endNode->_idx.x]->_attribute = ATTRIBUTE::NONE;
	}
	_endNode = _vtotalList[index];
	_endNode->_attribute = ATTRIBUTE::END;
}

void astar::SetNodeColor(node* node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->_rc, brush);
	DeleteObject(brush);
	//FrameRect(getMemDC(), &node->_rc, RGB(0, 0, 0));
}

void astar::SetAttributeNode(Vector2 nowIdx, Vector2 moveIdx, ATTRIBUTE att)
{
	if (_vtotalList[nowIdx.x + nowIdx.y * _map->GetHorizon()]->_attribute == att)
	{
		_vtotalList[nowIdx.x + nowIdx.y * _map->GetHorizon()]->_attribute = ATTRIBUTE::NONE;
	}
	_vtotalList[moveIdx.x + moveIdx.y * _map->GetHorizon()]->_attribute = att;
}
