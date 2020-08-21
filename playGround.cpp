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

	imginit();
	soundinit();

	ENVIRONMENT->init();

	SCENEMANAGER->addScene("Title", _TitleScene = new TitleScene);
	SCENEMANAGER->addScene("����", _MaptoolScene = new MapToolScene);
	SCENEMANAGER->addScene("LOADING", _LoadingScene = new LoadingScene);
	SCENEMANAGER->addScene("�½�Ʈ", _Tset = new TestScene);
	MapFarm* _farm;
	MapHome* _home;
	MapTest* _test;
	MapCave* _cave;
	DrainedLoadingScene* _DariLoading;
	SCENEMANAGER->addScene("FARM", _farm = new MapFarm);
	SCENEMANAGER->addScene("HOME", _home = new MapHome);
	SCENEMANAGER->addScene("CAVE", _cave = new MapCave);
	SCENEMANAGER->addScene("Test", _test = new MapTest);
	SCENEMANAGER->addScene("DariLoading", _DariLoading = new DrainedLoadingScene);
	SCENEMANAGER->changeScene("Title");
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

	

	//if (!test->GetNowFishing())
	//{
	//	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//	{
	//		Vector2 i(200, 200);
	//		test->Init(i, PLAYER_DIRECTION::LEFT);
	//	}
	//}
	//if(test->GetNowFishing())test->Update();

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
	//ZORDER->ZOrderRender();
	//test->Render();
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
	IMAGEMANAGER->addFrameImage("Loading", "image/Loading(822x62).bmp", 822, 62, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlot", "image/������.bmp", 800, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlotSelect", "image/��������.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("UpArrow", "image/��ȭ��ǥ.bmp", 40, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("DownArrow", "image/�Ʒ�ȭ��ǥ.bmp", 40, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfo", "image/�Ϲݾ����ۼ���.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInfo", "image/ȸ�������ۼ���.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfoWindow", "Image/ItemInfoWindow.bmp", 180, 130, true, MAGENTA);
	IMAGEMANAGER->addImage("SelectUI", "Image/selectUI.bmp", 1275, 276, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfoWindow2", "Image/ItemInfoWindow2.bmp", 180, 130, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("DrainLoading", "image/CombackHome(822x62).bmp", 822, 62, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("DrainFace", "image/Ż������(150x138).bmp", 150, 138, true, MAGENTA);



	//ȯ��
	IMAGEMANAGER->addImage("Environment_Clock", "image/Environment/Environment_Clock.bmp", 288, 236, true, MAGENTA);

	//�κ��丮
	IMAGEMANAGER->addImage("Inventory_BG", "image/Inventory/Inventory_BG.bmp", 1600, 900, false, BLACK);
	IMAGEMANAGER->addImage("UI_Inventory_Day", "image/Inventory/UI_Inventory_Day.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Night", "image/Inventory/UI_Inventory_Night.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_top", "image/Inventory/UI_Inventory_Craft_top.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Craft_bot", "image/Inventory/UI_Inventory_Craft_bot.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_KeyInfo", "image/Inventory/UI_Inventory_KeyInfo.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Game_Close", "image/Inventory/UI_Inventory_Game_Close.bmp", 848, 648, true, MAGENTA);
	IMAGEMANAGER->addImage("Inventory_Close", "image/Inventory/Inventory_Close.bmp", 44, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("UI_Inventory_Sort", "Image/Inventory/UI_Inventory_Sort.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("UI_Inventory_Trashcan", "image/Inventory/UI_Inventory_Trashcan.bmp", 368, 142, 4, 1, true, MAGENTA);

	//��������
	IMAGEMANAGER->addFrameImage("StoreOwnerPortrait", "image/����/��������_�ʻ�ȭ(420x630).bmp", 420, 630, 2, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreOwnerDot", "image/����/��������_��Ʈ(250x750).bmp", 250, 750, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreItme", "image/����/������ǰ.bmp", 1041, 210, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreInfo", "image/����/�Ұ���.bmp", 250, 143, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreWindow", "image/����/StoreWindow.bmp", 1085, 709, true, MAGENTA);
	IMAGEMANAGER->addImage("LowMoney", "Image/����/LowMoney.bmp", 170, 32, true, MAGENTA);

	//��ȭâ����
	IMAGEMANAGER->addImage("ChatBox", "image/��ȭâ2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("RightButton", "image/��ȭâ_�����ϴ�(330x33).bmp", 330, 33, 11, 1, true, WHITE);

	//�׽�Ʈ�� �̹����Դϴ� �����ϼ���
	IMAGEMANAGER->addFrameImage("����ī��", "image/����ī��.bmp", 200, 300, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addImage("�ʻ�ȭ", "image/powerCow.bmp", 209, 200, true, MAGENTA);

	/////MapTool
	IMAGEMANAGER->addImage("CloseButton", "image/�ݱ��ư.bmp", 44, 44, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Terrain", "image/mapTool/Terrain.bmp", 0, 0, 512, 512, 512 / TILESIZE, 512 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Terrain_InDoor", "image/mapTool/Indoor.bmp", 0, 0, 512, 512, 512 / TILESIZE, 512 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Wall_Cave", "image/mapTool/CaveWall.bmp", 0, 0, 320, 640, 5, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Wall", "image/mapTool/Wall.bmp", 0, 0, 512, 512, 512 / TILESIZE, 512 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("HoeTile", "image/mapTool/HoeTile.bmp", 0, 0, 448, 384, 448 / TILESIZE, 384 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Tree", "image/mapTool/Tree.bmp", 0, 0, 578, 384, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stump", "image/mapTool/Stump.bmp", 0, 0, 192, 84, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("House", "image/mapTool/House.bmp", 0, 0, 576, 576, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("POS", "image/mapTool/POS.bmp", 0, 0, 256, 128, 4, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Bed", "image/mapTool/Bed.bmp", 0, 0, 128, 192, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Blanket", "image/mapTool/Blanket.bmp", 0, 0, 128, 192, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("Line", "image/mapTool/Line.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Collision", "image/mapTool/Collision.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Window", "image/mapTool/Window.bmp", 700, 900, true, MAGENTA);
	IMAGEMANAGER->addImage("F1", "image/mapTool/F1.bmp", 64, 52, true, MAGENTA);
	IMAGEMANAGER->addImage("Save", "image/mapTool/Save.bmp", 229, 52, true, MAGENTA);

	EFFECTMANAGER->addEffect("RockDis", "image/mapTool/Rock.bmp", 4400, 120,200,120 , 1.0f, 0.5f, 300);
	EFFECTMANAGER->addEffect("BranchDis", "image/mapTool/Branch.bmp", 5301, 231,279,231 , 1.0f, 0.5f, 300);
	EFFECTMANAGER->addEffect("WeedDis", "image/mapTool/Weed.bmp", 500, 137,100,137 , 1.0f, 0.2f, 300);
	// Player
	IMAGEMANAGER->addFrameImage("player", "image/Player.bmp", 3000, 4500, 12, 18, true, MAGENTA);

	//����
	IMAGEMANAGER->addImage("FishingGague", "image/����/���ð�����.bmp", 12, 485, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingMiniGame", "image/����/���ù̴ϰ���.bmp", 128, 600, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBar", "image/����/���ù�.bmp", 34, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingStart", "image/����/���ý���.bmp", 120, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingPower", "image/����/�����ִ��Ŀ�����.bmp", 100, 36, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingRareFish", "image/����/������.bmp", 28, 29, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingFish", "image/����/�����.bmp", 28, 28, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBox", "image/����/����.bmp", 28, 34, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBack", "image/����/���ø�ǳ��.bmp", 200, 604, true, MAGENTA);


	//������ �̹��� (x64�� �κ��丮�� �Ⱥپ������� �÷��̾ �տ����������)
	IMAGEMANAGER->addImage("NormalFish(64x64)", "Image/ItemTest/Anchovy(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("NormalFish", "Image/ItemTest/Anchovy.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("RareFish(64x64)", "Image/ItemTest/Catfish(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("RareFish", "Image/ItemTest/Catfish.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Weed(64x64)", "Image/ItemTest/Fiber(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Weed", "Image/ItemTest/Fiber.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Kale(64x64)", "Image/ItemTest/Kale(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Kale", "Image/ItemTest/Kale.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("KaleSeed(64x64)", "Image/ItemTest/Kale_Seeds(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("KaleSeed", "Image/ItemTest/Kale_Seeds.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Pasnip(64x64)", "Image/ItemTest/Parsnip(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Pasnip", "Image/ItemTest/Parsnip.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("PasnipSeed(64x64)", "Image/ItemTest/Parsnip_Seeds(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("PasnipSeed", "Image/ItemTest/Parsnip_Seeds.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Potato(64x64)", "Image/ItemTest/Potato(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Potato", "Image/ItemTest/Potato.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("PotatoSeed(64x64)", "Image/ItemTest/Potato_Seeds(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("PotatoSeed", "Image/ItemTest/Potato_Seeds.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Sap(64x64)", "Image/ItemTest/Sap(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Sap", "Image/ItemTest/Sap.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Stone(64x64)", "Image/ItemTest/Stone(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Stone", "Image/ItemTest/Stone.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("Wood(64x64)", "Image/ItemTest/Wood(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Wood", "Image/ItemTest/Wood.bmp", 48, 48, true, MAGENTA);

	IMAGEMANAGER->addImage("WaterSpray(56x56)", "Image/ItemTest/watering.bmp", 56, 56, true, MAGENTA);

	IMAGEMANAGER->addImage("Axe(64x64)", "Image/ItemTest/Item_Axe.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Homi(64x64)", "Image/ItemTest/Item_Handplow.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Sword(64x64)", "Image/ItemTest/Item_Knife.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Pickax(64x64)", "Image/ItemTest/Item_Pickaxe.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Sickle(64x64)", "Image/ItemTest/Item_Sickle.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingRod(64x64)", "Image/ItemTest/FishingRod(64x64).bmp", 64, 64, true, MAGENTA);

	///////////////// �Ĺ� ������Ʈ
	IMAGEMANAGER->addFrameImage("kaleObject", "image/plants/KaleFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("parsnipObject", "image/plants/ParsnipFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("potatoObject", "image/plants/PotatoFrame.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
	/////////////////ENEMY
	IMAGEMANAGER->addFrameImage("SLIME", "image/Enemy/Slime.bmp", 64,64, 1, 1, true, RGB(255, 0, 255));
}

void playGround::soundinit()
{
	SOUNDMANAGER->addSound("TitleSound", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("FarmMap", "Sounds/farm.mp3", true, true);
	SOUNDMANAGER->addSound("maptool", "Sounds/maptool.mp3", true, true);
	SOUNDMANAGER->addSound("MenuSelect", "Sounds/menu_select.mp3", false, false);
	//playerSounds;
	
	SOUNDMANAGER->addSound("onGrass", "Sounds/PlayerSound/move_grass.mp3", false, false);
	SOUNDMANAGER->addSound("onSoil", "Sounds/PlayerSound/move_soil.mp3", false, false);
	SOUNDMANAGER->addSound("onRock", "Sounds/PlayerSound/move_rock.mp3", false, true);
	SOUNDMANAGER->addSound("actHoe", "Sounds/PlayerSound/hoe.mp3", false, false);
	SOUNDMANAGER->addSound("actSwing", "Sounds/PlayerSound/scythe.mp3", false, false);
	SOUNDMANAGER->addSound("actMining", "Sounds/PlayerSound/smash.mp3", false, false);
	SOUNDMANAGER->addSound("lootItem", "Sounds/PlayerSound/getItem.mp3",false,false);

	SOUNDMANAGER->addSound("RemoveRock", "Sounds/removeRock", false, false);
	SOUNDMANAGER->addSound("RemoveWeed", "Sounds/removeGrass", false, false);
	SOUNDMANAGER->addSound("RemoveBranch", "Sounds/breakTree", false, false);
}
