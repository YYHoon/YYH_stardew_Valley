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
	//POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT()); ���콺 ī�޶� ��ġ

	_Inv = new Inventory;
	_Inv->init();

	imginit();
	soundinit();

	SCENEMANAGER->addScene("Ÿ��Ʋȭ��", _TitleScene = new TitleScene);
	SCENEMANAGER->addScene("�׽�Ʈ", _Tset = new TestScene);
	SCENEMANAGER->addScene("����", _MaptoolScene = new MapToolScene);
	SCENEMANAGER->addScene("LOADING", _LoadingScene = new LoadingScene);
	SCENEMANAGER->addScene("Dummy", _dummy = new DummyMap);


	SCENEMANAGER->changeScene("Dummy");


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
	SCENEMANAGER->update();
	OBJECTMANAGER->Update();
	KEYANIMANAGER->update();

}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	SCENEMANAGER->render();

	/////////////////////////////////
	TIMEMANAGER->render(getMemDC());
	//////////////////////////////////
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

	IMAGEMANAGER->addFrameImage("mouse", "image/���콺.bmp", 360, 60, 6, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingSunny", "image/��_����20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingRain", "image/��_��20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("AlphaOnlyBlackWindow", "image/���Ŀ����ȭ��.bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("ItemInformation", "image/�Ϲݾ����ۼ���.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInformation", "image/ȸ�������ۼ���.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Loading", "image/Loading(822x62).bmp", 822, 62,3,1, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlot", "image/������.bmp", 800, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlotSelect", "image/��������.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("UpArrow", "image/��ȭ��ǥ.bmp", 40, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("DownArrow", "image/�Ʒ�ȭ��ǥ.bmp", 40, 44, true, MAGENTA);

	//ȯ��
	IMAGEMANAGER->addImage("Environment_Clock", "Image/Environment/Environment_Clock.bmp", 284, 160, true, MAGENTA);

	//�κ��丮
	IMAGEMANAGER->addImage("Inventory_BG", "Image/Inventory/Inventory_BG.bmp", 1600, 900, false, BLACK);
	IMAGEMANAGER->addImage("UI_Inventory_Day", "Image/Inventory/UI_Inventory_Day.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Night", "Image/Inventory/UI_Inventory_Night.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_top", "Image/Inventory/UI_Inventory_Craft_top.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_bot", "Image/Inventory/UI_Inventory_Craft_bot.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_KeyInfo", "Image/Inventory/UI_Inventory_KeyInfo.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Game_Close", "Image/Inventory/UI_Inventory_Game_Close.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("Inventory_Close", "Image/Inventory/Inventory_Close.bmp", 44, 44, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI_Inventory_Trashcan", "Image/Inventory/UI_Inventory_Trashcan.bmp", 184, 71, 4, 1, true, MAGENTA);

	//��������
	IMAGEMANAGER->addFrameImage("StoreOwnerPortrait", "image/����/��������_�ʻ�ȭ(420x630).bmp", 420, 630, 2, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreOwnerDot", "image/����/��������_��Ʈ(200x600).bmp", 200, 600, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreItme", "image/����/������ǰ.bmp", 1041, 210, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreInfo", "image/����/�Ұ���.bmp", 250, 143, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreWindow", "image/����/����â.bmp", 1085, 709, true, MAGENTA);
	IMAGEMANAGER->addImage("BeanSeed", "image/����/beanSeed.bmp", 56, 56, true, MAGENTA);
	IMAGEMANAGER->addImage("CauliFlowerSeed", "image/����/cauliFlowerSeed.bmp", 56, 56, true, MAGENTA);
	IMAGEMANAGER->addImage("PotatoSeed", "image/����/potatoSeed.bmp", 56, 56, true, MAGENTA);
	IMAGEMANAGER->addImage("sugarRadishSeed", "image/����/sugarRadishSeed.bmp", 56, 56, true, MAGENTA);
	IMAGEMANAGER->addImage("��پ���", "image/����/��پ���.bmp", 56, 56, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);

	//��ȭâ����
	IMAGEMANAGER->addImage("ChatBox", "image/��ȭâ2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);

	//��ȭâ����
	IMAGEMANAGER->addImage("ChatWindow", "image/��ȭâ2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("RightButton", "image/��ȭâ_�����ϴ�(330x33).bmp", 330, 33, 11, 1, true, WHITE);

	//��ȭ�׽�Ʈ�� �̹����Դϴ� �����ϼ���
	IMAGEMANAGER->addFrameImage("����ī��", "image/����ī��.bmp", 200, 300, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addImage("�����ʵ�", "image/�ʻ�ȭ��.bmp", 209, 200, true, MAGENTA);
	IMAGEMANAGER->addImage("�ʻ�ȭ", "image/powerCow.bmp", 209, 200, true, MAGENTA);

	//���ð���
	IMAGEMANAGER->addImage("FishingPowerMax", "image/����/�����ִ��Ŀ�����.bmp", 100, 36, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingStart", "image/����/���ý���.bmp", 120, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBackGrond", "image/����/���ø�ǳ��.bmp", 200, 604, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingMiniGame", "image/����/���ù̴ϰ���.bmp", 128, 505, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingGauge", "image/����/���ð�����.bmp", 12, 486, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingGaugeBar", "image/����/���ù�.bmp", 34, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("Fish", "image/����/�����.bmp", 28, 28, true, MAGENTA);
	IMAGEMANAGER->addImage("FishBox", "image/����/����.bmp", 28, 34, true, MAGENTA);
	IMAGEMANAGER->addImage("FishRare", "image/����/������.bmp", 28, 29, true, MAGENTA);
	/////MapTool
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Terrain", "image/mapTool/Terrain.bmp", 0, 0, 448, 448, 448 / TILESIZE, 448 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Tree", "image/mapTool/Tree.bmp", 0, 0, 578, 384, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("House", "image/mapTool/House.bmp", 0, 0, 576, 576, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("Line", "image/mapTool/Line.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Collision", "image/mapTool/Collision.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Window", "image/mapTool/Window.bmp", 700, 900, true, MAGENTA);

	// Player
	IMAGEMANAGER->addFrameImage("player", "image/Player.bmp", 3000, 4500, 12, 18, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("FishingGague", "image/����/���ð�����.bmp", 12, 485, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingMiniGame", "image/����/���ù̴ϰ���.bmp", 128, 505, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBar", "image/����/���ù�.bmp", 34, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingStart", "image/����/���ý���.bmp", 120, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingPower", "image/����/�����ִ��Ŀ�����.bmp", 100, 36, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingRareFish", "image/����/������.bmp", 28, 29, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingFish", "image/����/�����.bmp", 28, 28, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBox", "image/����/����.bmp", 28, 34, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBack", "image/����/���ø�ǳ��.bmp", 200, 604, true, MAGENTA);
}

void playGround::soundinit()
{
	SOUNDMANAGER->addSound("TitleSound", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("maptool", "Sounds/maptool.mp3", true, true);
	SOUNDMANAGER->addSound("MenuSelect", "Sounds/menu_select.mp3", false, false);
}
