#pragma once
#include "Enemy.h"
#include "astar.h"
class Slime :  public Enemy
{
private:
	int count = 0;
public:
   virtual void Init();
   virtual void Release();
   virtual void Update();
   virtual void Render();
   void SetAstarStartNode(Vector2 start) { return _astar->SetStartNode(start); }
   void SetAstarEndNode(Vector2 end) { return _astar->SetEndNode(end); }
   
};

