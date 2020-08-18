#pragma once
#include"ToolItemManager.h"


struct tagSpread
{
	Spread type=Spread::NONE;					//뿌릴방식
	SpreadState state = SpreadState::NONE;		//뿌려지는 상황
	MapMain* nowMap;							//현재맵
	MYRECT renge;								//아이템이 플레이어근처일경우 흡수될범위
	Vector2 pos;								//현재 아이템의 좌표
	Vector2 lastPos;							//도착할 좌표
	string name;								//뿌려질 아이템의 이름
	float speed;								//아이템이뿌려질속도
	bool move;									//아이템이 움직이고있는지
	bool isActive;								//현재 아이템이 작동가능한지
	bool getPlayer;								//플레이어에게 습득되었는지
	bool up = false;
	bool left = false;
};

class SpreadItem
{

private:
	vector<ToolItem*> itemList;			//아이템정보를 모두 담고있는 벡터
	ToolItemManager* _toolItemManager;	//아이템정보를 들고있는클래스
	tagSpread _spread;					//뿌려질아이템
	vector<tagSpread> _spreadItemList;	//뿌려질아이템들을 담고있을 벡터

public:
	SpreadItem();
	virtual ~SpreadItem() {};
	
	//그럴릴없겠지만 이 이닛함수 상시업데이트되는곳에넣으면 좆됩니다
	virtual void Init(Spread ty , string name , int index , int num); //뿌려질아이템의 정보들을 넣어둡니다
	virtual void Init(Spread ty , string name , Vector2 index , int num); //뿌려질아이템의 정보들을 넣어둡니다
	
	
	virtual void Update(string name);

	void SpreadUpdate(tagSpread &spread);


	int VectorToIndex(tagSpread s,Vector2 v);

	inline void SetToolMemoryAddressLink(ToolItemManager* t) { _toolItemManager = t; }//툴아이템정보가져오는친구입니다 동적할당 속도느려질까바 가져오는걸로만드듬
};

