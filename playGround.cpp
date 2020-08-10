#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	//player = new Player;
	//player->Init();
	//OBJECTMANAGER->AddGameObject("PLAYER", player);

	_Inv = new Inventory;
	_Inv->init();

	imginit();

	_TitleScene = new TitleScene;
	_Tset = new TestScene;
	_MaptoolScene = new MapToolScene;

	SCENEMANAGER->addScene("Ÿ��Ʋȭ��", _TitleScene);
	SCENEMANAGER->addScene("�׽�Ʈ", _Tset);
	SCENEMANAGER->addScene("����", _MaptoolScene);


	SCENEMANAGER->changeScene("Ÿ��Ʋȭ��");


	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
	return S_OK;
}

//�޸� ����
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//����
void playGround::update()
{
	gameNode::update();
	_Inv->update();
	OBJECTMANAGER->Update();

	SCENEMANAGER->update();

}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	OBJECTMANAGER->Render();

	_Inv->render();

	SCENEMANAGER->render();

	ZORDER->ZOrderRender();
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imginit()
{
	//Ÿ��Ʋȭ�� ����
	IMAGEMANAGER->addImage("TitleBackground", "image/Ÿ��Ʋ/stardewPanorama(1600x900).bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("Title", "image/Ÿ��Ʋ/Ÿ��Ʋ(690x318).bmp", 690, 318, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StartButton", "image/Ÿ��Ʋ/Start(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("LoadButton", "image/Ÿ��Ʋ/Load(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("ExitButton", "image/Ÿ��Ʋ/Exit(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("MaptoolButton", "image/Ÿ��Ʋ/maptool(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("TitleBrid", "image/Ÿ��Ʋ/Brid(400x69).bmp", 400, 69, 4, 1, true, MAGENTA);

	//UI
	IMAGEMANAGER->addFrameImage("mouse", "image/���콺.bmp", 180, 60, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingSunny", "image/��_����20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingRain", "image/��_��20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("AlphaOnlyBlackWindow", "image/���Ŀ����ȭ��.bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("ItemInformation", "image/�Ϲݾ����ۼ���.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInformation", "image/ȸ�������ۼ���.bmp", 293, 258, true, MAGENTA);

	//��������
	IMAGEMANAGER->addFrameImage("StoreOwnerPortrait", "image/����/��������_�ʻ�ȭ(420x630).bmp", 420, 630, 2, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreOwnerDot", "image/����/��������_��Ʈ(200x600).bmp", 200, 600, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreItme", "image/����/������ǰ.bmp", 1041, 210, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreInfo", "image/����/�Ұ���.bmp", 250, 143, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreWindow", "image/����/����â.bmp", 1085, 709, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);

	//��ȭâ����
	IMAGEMANAGER->addImage("ChatWindow", "image/��ȭâ2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("RightButton", "image/��ȭâ_�����ϴ�(330x33).bmp", 330, 33, 11, 1, true, WHITE);

	//��ȭ�׽�Ʈ�� �̹����Դϴ� �����ϼ���
	IMAGEMANAGER->addFrameImage("����ī��", "image/����ī��.bmp", 200, 300, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addImage("�����ʵ�", "image/�ʻ�ȭ��.bmp", 209, 200, true, MAGENTA);
}

void playGround::soundinit()
{
	
}
