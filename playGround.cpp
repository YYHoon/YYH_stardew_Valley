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

	//player = new Player;
	//player->Init();
	//OBJECTMANAGER->AddGameObject("PLAYER", player);


	//POINT _CameraMouse = PointMake(_ptMouse.x + CAMERAMANAGER->getL(), _ptMouse.y + CAMERAMANAGER->getT());

	_Inv = new Inventory;
	_Inv->init();

	imginit();

	_TitleScene = new TitleScene;
	_Tset = new TestScene;
	_MaptoolScene = new MapToolScene;
	_dummy = new DummyMap;
	_dummy->init();
	SCENEMANAGER->addScene("타이틀화면", _TitleScene);
	SCENEMANAGER->addScene("테스트", _Tset);
	SCENEMANAGER->addScene("맵툴", _MaptoolScene);
	SCENEMANAGER->addScene("더미맵", _dummy);


	SCENEMANAGER->changeScene("더미맵");


	CAMERAMANAGER->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
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
	_Inv->update();
	OBJECTMANAGER->Update();

	SCENEMANAGER->update();

}

//그리기 전용
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
	//타이틀화면 관련
	IMAGEMANAGER->addImage("TitleBackground", "image/타이틀/stardewPanorama(1600x900).bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("Title", "image/타이틀/타이틀(690x318).bmp", 690, 318, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StartButton", "image/타이틀/Start(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("LoadButton", "image/타이틀/Load(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("ExitButton", "image/타이틀/Exit(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("MaptoolButton", "image/타이틀/maptool(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("TitleBrid", "image/타이틀/Brid(400x69).bmp", 400, 69, 4, 1, true, MAGENTA);

	//UI
	IMAGEMANAGER->addFrameImage("mouse", "image/마우스.bmp", 180, 60, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingSunny", "image/봄_맑음20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("SpingRain", "image/봄_비20T(3800x162).bmp", 3800, 162, 19, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("AlphaOnlyBlackWindow", "image/알파용검은화면.bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("ItemInformation", "image/일반아이템설명.bmp", 293, 258, true, MAGENTA);
	IMAGEMANAGER->addImage("RecoveryItemInformation", "image/회복아이템설명.bmp", 293, 258, true, MAGENTA);

	//상점관련
	IMAGEMANAGER->addFrameImage("StoreOwnerPortrait", "image/상점/상점주인_초상화(420x630).bmp", 420, 630, 2, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreOwnerDot", "image/상점/상점주인_도트(200x600).bmp", 200, 600, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StoreItme", "image/상점/상점물품.bmp", 1041, 210, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreInfo", "image/상점/소개문.bmp", 250, 143, true, MAGENTA);
	IMAGEMANAGER->addImage("StoreWindow", "image/상점/상점창.bmp", 1085, 709, true, MAGENTA);
	IMAGEMANAGER->addImage("CloseButton", "image/닫기버튼.bmp", 44, 44, true, MAGENTA);

	//대화창관련
	IMAGEMANAGER->addImage("ChatWindow", "image/대화창2.bmp", 900, 312, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("RightButton", "image/대화창_우측하단(330x33).bmp", 330, 33, 11, 1, true, WHITE);

	//대화테스트용 이미지입니다 무시하세요
	IMAGEMANAGER->addFrameImage("말랑카우", "image/말랑카우.bmp", 200, 300, 4, 6, true, MAGENTA);
	IMAGEMANAGER->addImage("와츄고너두", "image/초상화용.bmp", 209, 200, true, MAGENTA);

	/////MapTool
	IMAGEMANAGER->addImage("CloseButton", "image/닫기버튼.bmp", 44, 44, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Terrain", "image/mapTool/Terrain.bmp", 0, 0, 448, 448, 448 / TILESIZE, 448 / TILESIZE, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Tree", "image/mapTool/Tree.bmp", 0, 0, 578, 384, 3, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("House", "image/mapTool/House.bmp", 0, 0, 576, 576, 1, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("Line", "image/mapTool/Line.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Collision", "image/mapTool/Collision.bmp", 64, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("Window", "image/mapTool/Window.bmp", 700, 900, true, MAGENTA);

	// Player
	IMAGEMANAGER->addFrameImage("player", "image/Player.bmp", 3000, 4500, 12, 18, true, RGB(255, 0, 255));

	//낚시
	IMAGEMANAGER->addImage("FishingGague", "image/낚시/낚시게이지.bmp", 12, 485, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingMiniGame", "image/낚시/낚시미니게임.bmp", 128, 505, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBar", "image/낚시/낚시바.bmp", 34, 96, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingStart", "image/낚시/낚시시작.bmp", 120, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingPower", "image/낚시/낚시최대파워던짐.bmp", 100, 36, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingRareFish", "image/낚시/레어물고기.bmp", 28, 29, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingFish", "image/낚시/물고기.bmp", 28, 28, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBox", "image/낚시/상자.bmp", 28, 34, true, MAGENTA);
	IMAGEMANAGER->addImage("FishingBack", "image/낚시/낚시말풍선.bmp", 200, 604, true, MAGENTA);
}

void playGround::soundinit()
{
	
}
