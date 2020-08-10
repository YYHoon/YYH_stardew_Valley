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

	_Inv = new Inventory;
	_Inv->init();

	imginit();

	_TitleScene = new TitleScene;
	_Tset = new TestScene;
	_MaptoolScene = new MapToolScene;

	SCENEMANAGER->addScene("타이틀화면", _TitleScene);
	SCENEMANAGER->addScene("테스트", _Tset);
	SCENEMANAGER->addScene("맵툴", _MaptoolScene);


	SCENEMANAGER->changeScene("타이틀화면");


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
}

void playGround::soundinit()
{
	
}
