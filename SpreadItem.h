#pragma once
#include"ToolItemManager.h"


struct tagSpread
{
	Spread type=Spread::NONE;					//�Ѹ����
	SpreadState state = SpreadState::NONE;		//�ѷ����� ��Ȳ
	MapMain* nowMap;							//�����
	MYRECT renge;								//�������� �÷��̾��ó�ϰ�� ����ɹ���
	Vector2 pos;								//���� �������� ��ǥ
	Vector2 lastPos;							//������ ��ǥ
	string name;								//�ѷ��� �������� �̸�
	float speed;								//�������̻ѷ����ӵ�
	bool move;									//�������� �����̰��ִ���
	bool isActive;								//���� �������� �۵���������
	bool getPlayer;								//�÷��̾�� ����Ǿ�����
	bool up = false;
	bool left = false;
};

class SpreadItem
{

private:
	vector<ToolItem*> itemList;			//������������ ��� ����ִ� ����
	ToolItemManager* _toolItemManager;	//������������ ����ִ�Ŭ����
	tagSpread _spread;					//�ѷ���������
	vector<tagSpread> _spreadItemList;	//�ѷ��������۵��� ������� ����

public:
	SpreadItem();
	virtual ~SpreadItem() {};
	
	//�׷����������� �� �̴��Լ� ��þ�����Ʈ�Ǵ°��������� ���˴ϴ�
	virtual void Init(Spread ty , string name , int index , int num); //�ѷ����������� �������� �־�Ӵϴ�
	virtual void Init(Spread ty , string name , Vector2 index , int num); //�ѷ����������� �������� �־�Ӵϴ�
	
	
	virtual void Update(string name);

	void SpreadUpdate(tagSpread &spread);


	int VectorToIndex(tagSpread s,Vector2 v);

	inline void SetToolMemoryAddressLink(ToolItemManager* t) { _toolItemManager = t; }//��������������������ģ���Դϴ� �����Ҵ� �ӵ���������� �������°ɷθ����
};

