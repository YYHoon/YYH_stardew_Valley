#pragma once
#include "Enemy.h"
#include "astar.h"
class Slime :  public Enemy
{
private:
	int count = 0;
	Synthesize(Vector2, _currentIdx,CurrentIdx)
	Vector2 _NextIdx;
	int idx = 0;
public:
   virtual void Init();
   virtual void Release();
   virtual void Update();
   virtual void Render();
   void SetAstarStartNode(Vector2 start) { return _astar->SetStartNode(start); }
   void SetAstarEndNode(Vector2 end) { return _astar->SetEndNode(end); }
   void AstarSetMap() { _astar->SetMap(); }
   void AstarPath() { _astar->PathFind(); }
   
};

