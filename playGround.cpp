#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	//POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT()); 마우스 카메라 위치

	imginit();
	soundinit();

	ENVIRONMENT->init();
	MapFarm* _farm;
	MapHome* _home;
	MapTest* _test;
	MapCave* _cave;
	DrainedLoadingScene* _DariLoading;

	SCENEMANAGER->addScene("Title", _TitleScene = new TitleScene);
	SCENEMANAGER->addScene("맵툴", _MaptoolScene = new MapToolScene);
	SCENEMANAGER->addScene("LOADING", _LoadingScene = new LoadingScene);
	SCENEMANAGER->addScene("태스트", _Tset = new TestScene);
	SCENEMANAGER->addScene("FARM", _farm = new MapFarm);
	SCENEMANAGER->addScene("HOME", _home = new MapHome);
	SCENEMANAGER->addScene("CAVE", _cave = new MapCave);
	SCENEMANAGER->addScene("Test", _test = new MapTest);
	SCENEMANAGER->addScene("DariLoading", _DariLoading = new DrainedLoadingScene);
	SCENEMANAGER->changeScene("Title");
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	OBJECTMANAGER->Release();
}

//연산
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	OBJECTMANAGER->Update();
	KEYANIMANAGER->update();
}

//그리기 전용
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
	//타이틀화면 관련
	IMAGEMANAGER->addImage("TitleBackground", "image/타이틀/stardewPanorama(1600x900).bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("Title", "image/타이틀/타이틀(690x318).bmp", 690, 318, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StartButton", "image/타이틀/Start(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("LoadButton", "image/타이틀/Load(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("ExitButton", "image/타이틀/Exit(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("MaptoolButton", "image/타이틀/maptool(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("TitleBrid", "image/타이틀/Brid(400x69).bmp", 400, 69, 4, 1, true, MAGENTA);

	//UI
	IMAGEMANAGER->addFrameImage("mouse", "image/마우스.bmp", 360, 60, 6, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingSunny", "image/봄_맑음20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingRain", "image/봄_비20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("AlphaOnlyBlackWindow", "image/알파용검은화면.bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("ItemInformation", "image/일반아이템설명.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInformation", "image/회복아이템설명.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Loading", "image/Loading(822x62).bmp", 822, 62, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlot", "image/퀵슬롯.bmp", 800, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("QuickSlotSelect", "image/퀵스선택.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("UpArrow", "image/위화살표.bmp", 40, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("DownArrow", "image/아래화살표.bmp", 40, 44, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfo", "image/일반아이템설명.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInfo", "image/회복아이템설명.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfoWindow", "Image/ItemInfoWindow.bmp", 276, 200, true, MAGENTA);
	IMAGEMANAGER->addImage("SelectUI", "Image/selectUI.bmp", 1275, 276, true, MAGENTA);
	IMAGEMANAGER->addImage("ItemInfoWindow2", "Image/ItemInfoWindow2.bmp", 180, 130, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("DrainLoading", "image/CombackHome(822x62).bmp", 822, 62, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("DrainFace", "image/탈진상태(150x138).bmp", 150, 138, true, MAGENTA);

	//환경
	IMAGEMANAGER->addImage("Environment_Clock", "image/Environment/Environment_Clock.bmp", 288, 236, true, MAGENTA);

	//인벤토리
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
	IMAGEMANAGER->addImage("GetItem", "Image/getItem.bmp", 205, 74, true, MAGENTA);

	//제작
	IMAGEMANAGER->addImage("GrilledFish", "Image/Crafting/GrilledFish.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("GrilledFish_before", "Image/Crafting/GrilledFish_before.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("RawFish", "Image/Crafting/RawFish.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("RawFish_before", "Image/Crafting/RawFish_before.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Salad", "Image/Crafting/Salad.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Salad_before", "Image/Crafting/Salad_before.bmp", 64, 64, true, MAGENTA);

	//상점관련
	IMAGEMANAGER->addFrameImage("StoreOwnerPortrait", "image/상점/상점주인_초상화(420x630).bmp", 420, 630, 2, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreOwnerDot", "image/상점/상점주인_도트(250x750).bmp", 250, 750, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreItme", "image/상점/상점물품.bmp", 1041, 210, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreInfo", "image/상점/소개문.bmp", 250, 143, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreWindow", "image/상점/StoreWindow.bmp", 1085, 709, true, MAGENTA);
	IMAGEMANAGER->addImage("LowMoney", "Image/상점/LowMoney.bmp", 170, 32, true, MAGENTA);

	//대화창관련
	IMAGEMANAGER->addImage("ChatBox", "image/대화창2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/닫기버튼.bmp", 44, 44, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("RightButton", "image/대화창_우측하단(330x33).bmp", 330, 33, 11, 1, true, WHITE);

	//테스트용 이미지입니다 무시하세요
	IMAGEMANAGER->addFrameImage("말랑카우", "image/말랑카우.bmp", 200, 300, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addImage("초상화", "image/powerCow.bmp", 209, 200, true, MAGENTA);

	/////MapTool
	IMAGEMANAGER->addImage("CloseButton", "image/닫기버튼.bmp", 44, 44, true, MAGENTA);

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
	EFFECTMANAGER->addEffect("Water", "image/mapTool/WaterSplash.bmp", 640, 64, 64, 64, 1.0f, 0.2f, 300);

	/// ///////////////////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("ScareCrow(64x64)", "Image/MapTool/ScareCrow(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("ScareCrow", "Image/MapTool/ScareCrow.bmp", 64, 128, true, MAGENTA);
	IMAGEMANAGER->addImage("Flowerpot(64x64)", "Image/MapTool/Flowerpot(64x64).bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Flowerpot", "Image/MapTool/Flowerpot.bmp", 64, 128, true, MAGENTA);
	/// ///////////////////////////////////////////////////////////////////////////

	// Player
	IMAGEMANAGER->addFrameImage("player", "image/Player.bmp", 3000, 4500, 12, 18, true, MAGENTA);

	//낚시
	IMAGEMANAGER->addImage("FishingGague", "image/낚시/낚시게이지.bmp", 12, 485, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingMiniGame", "image/낚시/낚시미니게임.bmp", 128, 600, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBar", "image/낚시/낚시바.bmp", 34, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingStart", "image/낚시/낚시시작.bmp", 120, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingPower", "image/낚시/낚시최대파워던짐.bmp", 100, 36, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingRareFish", "image/낚시/레어물고기.bmp", 28, 29, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingFish", "image/낚시/물고기.bmp", 28, 28, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBox", "image/낚시/상자.bmp", 28, 34, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingWWWW", "image/낚시/WWWW.bmp", 50, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBack", "image/낚시/낚시말풍선.bmp", 200, 604, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Fishing_LR", "image/Fishing_LR.bmp", 2068, 312, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Fishing_UP", "image/Fishing_UP.bmp", 612, 133, 12, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Fishing_DOWN", "image/Fishing_DOWN.bmp", 650, 167, 10, 1, true, MAGENTA);

	//아이템 이미지 (x64는 인벤토리용 안붙어있으면 플레이어가 손에들고있을때)
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

	///////////////// 식물 오브젝트
	IMAGEMANAGER->addFrameImage("kaleObject", "image/plants/KaleFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("parsnipObject", "image/plants/ParsnipFrame.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("potatoObject", "image/plants/PotatoFrame.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
	/////////////////ENEMY
	IMAGEMANAGER->addFrameImage("SLIME", "image/Enemy/Slime.bmp", 64,64, 1, 1, true, RGB(255, 0, 255));

	/////////////////////////////////////PLAYER//////////////////////////////////////////////////////////////
	/////////////////IDLE////////////////////
	int rightIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Idle_Player", "player", rightIdle, 1, 6, false);
	int leftIdle[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Idle_Player", "player", leftIdle, 1, 6, false);
	int upIdle[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Idle_Player", "player", upIdle, 1, 6, false);
	int downIdle[] = { 23 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Idle_Player", "player", downIdle, 1, 6, false);
	/////////////////MOVE////////////////////
	int RightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Move_Player", "player", RightMove, 5, 10, true);
	int LeftMove[] = { 7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Move_Player", "player", LeftMove, 5, 10, true);
	int UpMove[] = { 13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Move_Player", "player", UpMove, 7, 10, true);
	int DownMove[] = { 21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Move_Player", "player", DownMove, 6, 10, true);
	/////////////////ITEMIDLE////////////////////
	int ItemDownIdle[] = { 116 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Item_Idle_Player", "player", ItemDownIdle, 1, 6, false);
	int ItemLeftIdle[] = { 120 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Item_Idle_Player", "player", ItemLeftIdle, 1, 6, false);
	int ItemRightIdle[] = { 125 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Item_Idle_Player", "player", ItemRightIdle, 1, 6, false);
	int ItemUpdle[] = { 134 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Item_Idle_Player", "player", ItemUpdle, 1, 6, false);
	/////////////////ItemMOVE////////////////////
	int leftItemMove[] = { 120,121,122,123 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Item_Move_Player", "player", leftItemMove, 4, 10, false);
	int rightItemMove[] = { 125,126,127,128 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Item_Move_Player", "player", rightItemMove, 4, 10, false);
	int upItemMove[] = { 132,133,134,135,136,137 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Item_Move_Player", "player", upItemMove, 6, 10, false);
	int downItmeMove[] = { 139,140,141,142 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Item_Move_Player", "player", downItmeMove, 4, 10, false);
	/////////////////FELLING////////////////////
	int rightFelling[] = { 33,34,35,36 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Felling_Player", "player", rightFelling, 4, 10, false);
	int leftFelling[] = { 38,39,40,41,42 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Felling_Player", "player", leftFelling, 4, 10, false);
	int upFelling[] = { 43,44,45,46 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Felling_Player", "player", upFelling, 4, 10, false);
	int downFelling[] = { 27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Felling_Player", "player", downFelling, 6, 10, false);
	/////////////////Plowing////////////////////
	int downPlowing[] = { 48,49,50 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Plowing_Player", "player", downPlowing, 3, 10, false);
	int upPlowing[] = { 51,52,53,54 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Plowing_Player", "player", upPlowing, 4, 10, false);
	int rightPlowing[] = { 55,56,57,58,59 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Plowing_Player", "player", rightPlowing, 4, 10, false);
	int leftPlowing[] = { 60,61,62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Plowing_Player", "player", leftPlowing, 5, 10, false);
	/////////////////MINING////////////////////
	int downMining[] = { 168,169,170, 171, 172,173,174 };
	KEYANIMANAGER->addArrayFrameAnimation("down_mining_Player", "player", downMining, 7, 10, false);
	int upMining[] = { 175,176,177,178,179 };
	KEYANIMANAGER->addArrayFrameAnimation("up_mining_Player", "player", upMining, 5, 10, false);
	int rightMining[] = { 180,181,182,183,184 };
	KEYANIMANAGER->addArrayFrameAnimation("right_mining_Player", "player", rightMining, 5, 10, false);
	int leftMining[] = { 189,188,187,186,185 };
	KEYANIMANAGER->addArrayFrameAnimation("left_mining_Player", "player", leftMining, 5, 10, false);
	/////////////////SWING////////////////////
	int downSickleSwing[] = { 65,66,67,68,69,70 };
	KEYANIMANAGER->addArrayFrameAnimation("down_SickleSwing_Player", "player", downSickleSwing, 6, 10, false);
	int rightSickleSwing[] = { 72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("right_SickleSwing_Player", "player", rightSickleSwing, 6, 10, false);
	int lefSickleSwing[] = { 78,79,80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("left_SickleSwing_Player", "player", lefSickleSwing, 5, 10, false);
	int upSickleSwing[] = { 84,85,86,87,88,89 };
	KEYANIMANAGER->addArrayFrameAnimation("up_SickleSwing_Player", "player", upSickleSwing, 6, 10, false);
	int downAttack[] = { 143,144,145,146,147,148, 149 };
	KEYANIMANAGER->addArrayFrameAnimation("down_SwordSwing_Player", "player", downAttack, 7, 10, false);
	int rightAttack[] = { 150,151,152,153,154,155 };
	KEYANIMANAGER->addArrayFrameAnimation("right_SwordSwing_Player", "player", rightAttack, 6, 10, false);
	int leftAttack[] = { 156,157,158,159,160,161 };
	KEYANIMANAGER->addArrayFrameAnimation("left_SwordSwing_Player", "player", leftAttack, 6, 10, false);
	int upAttack[] = { 162,163,164 };
	KEYANIMANAGER->addArrayFrameAnimation("up_SwordSwing_Player", "player", upAttack, 3, 10, false);
	/////////////////EATING////////////////////
	int eating[] = { 192,193,194,195,196,197,198,199,200,201 };
	KEYANIMANAGER->addArrayFrameAnimation("eating_Player", "player", eating, 10, 10, false);
	/////////////////WATERING////////////////////
	int rightWatering[] = { 90,91,92,93,94, 93, 94, 93, 94, 93, 94 };
	KEYANIMANAGER->addArrayFrameAnimation("right_Watering_Player", "player", rightWatering, 11, 10, false);
	int downWatering[] = { 96,97,98,99,100,101,102,103,104,105,106, 107 };
	KEYANIMANAGER->addArrayFrameAnimation("down_Watering_Player", "player", downWatering, 12, 10, false);
	int leftWatering[] = { 108,109,110,111,112 , 111, 112, 111, 112, 111, 112 };
	KEYANIMANAGER->addArrayFrameAnimation("left_Watering_Player", "player", leftWatering, 11, 10, false);
	int upWatering[] = { 113,114, 115, 115, 115, 115, 115, 115, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("up_Watering_Player", "player", upWatering, 9, 10, false);
	/////////////////FISHINGSTART////////////////////
	int downMiningS[] = { 168,169,170, 171, 172,173,174 };
	KEYANIMANAGER->addArrayFrameAnimation("down_mining_Player", "player", downMiningS, 7, 10, false);
	int upMiningS[] = { 175,176,177,178,179 };
	KEYANIMANAGER->addArrayFrameAnimation("up_mining_Player", "player", upMiningS, 5, 10, false);
	int rightMiningS[] = { 180,181,182,183,184 };
	KEYANIMANAGER->addArrayFrameAnimation("right_mining_Player", "player", rightMiningS, 5, 10, false);
	int leftMiningS[] = { 189,188,187,186,185 };
	KEYANIMANAGER->addArrayFrameAnimation("left_mining_Player", "player", leftMiningS, 5, 10, false);
	/////////////////FISHINGPROCEEDING////////////////////
	int downMiningP[] = { 170 };
	KEYANIMANAGER->addArrayFrameAnimation("own_mining_Player", "player", downMiningP, 1, 10, false);
	int upMiningP[] = { 176 };
	KEYANIMANAGER->addArrayFrameAnimation("p_mining_Player", "player", upMiningP, 1, 10, false);
	int rightMiningP[] = { 181 };
	KEYANIMANAGER->addArrayFrameAnimation("ight_mining_Player", "player", rightMiningP, 1, 10, false);
	int leftMiningP[] = { 188 };
	KEYANIMANAGER->addArrayFrameAnimation("eft_mining_Player", "player", leftMiningP, 1, 10, false);
	/////////////////FISHINGEND////////////////////
	int Left_Fishing_Charge[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("Left_Fishing_Charge", "Fishing_LR", Left_Fishing_Charge, 1, 5, false);
	int Right_Fishing_Charge[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("Right_Fishing_Charge", "Fishing_LR", Right_Fishing_Charge, 1, 5, false);
	int Up_Fishing_Charge[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("Up_Fishing_Charge", "Fishing_UP", Up_Fishing_Charge, 1, 5, false);
	int Down_Fishing_Charge[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("Down_Fishing_Charge", "Fishing_DOWN", Down_Fishing_Charge, 1, 5, false);
	int Left_Fishing_Shot[] = { 2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Left_Fishing_Shot", "Fishing_LR", Left_Fishing_Shot, 3, 10, false);
	int Right_Fishing_Shot[] = { 18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation("Right_Fishing_Shot", "Fishing_LR", Right_Fishing_Shot, 3, 10, false);
	int Up_Fishing_Shot[] = { 2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("Up_Fishing_Shot", "Fishing_UP", Up_Fishing_Shot, 4, 10, false);
	int Down_Fishing_Shot[] = { 1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Down_Fishing_Shot", "Fishing_DOWN", Down_Fishing_Shot, 4, 10, false);
	int Left_Fishing_Doing[] = { 7,8,9, };
	KEYANIMANAGER->addArrayFrameAnimation("Left_Fishing_Doing", "Fishing_LR", Left_Fishing_Doing, 3, 10, false);
	int Right_Fishing_Doing[] = { 14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("Right_Fishing_Doing", "Fishing_LR", Right_Fishing_Doing, 3, 10, false);
	int Up_Fishing_Doing[] = { 8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("Up_Fishing_Doing", "Fishing_UP", Up_Fishing_Doing, 2, 10, false);
	int Down_Fishing_Doing[] = { 8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("Down_Fishing_Doing", "Fishing_DOWN", Down_Fishing_Doing, 2, 10, false);
	int Left_Fishing_Sus[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("Left_Fishing_Sus", "Fishing_LR", Left_Fishing_Sus, 1, 10, false);
	int Right_Fishing_Suc[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("Right_Fishing_Suc", "Fishing_LR", Right_Fishing_Suc, 1, 10, false);
	int Down_Fishing_Suc[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("Down_Fishing_Suc", "Fishing_DOWN", Down_Fishing_Suc, 1, 10, false);
	int Up_Fishing_Suc[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("Up_Fishing_Suc", "Fishing_UP", Up_Fishing_Suc, 1, 10, false);

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

	SOUNDMANAGER->addSound("Menu_Open", "Sounds/menuopen.mp3", false, false);
	SOUNDMANAGER->addSound("Menu_Close", "Sounds/menuclose.mp3", false, false);
}
