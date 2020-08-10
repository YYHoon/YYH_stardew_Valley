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
	imginit();

	_TitleScene = new TitleScene;
	_Tset = new TestScene;
	_MaptoolScene = new MapToolScene;

	SCENEMANAGER->addScene("타이틀화면", _TitleScene);
	SCENEMANAGER->addScene("테스트", _Tset);
	SCENEMANAGER->addScene("맵툴", _MaptoolScene);


	SCENEMANAGER->changeScene("타이틀화면");

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();
	

	SCENEMANAGER->update();
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	SCENEMANAGER->render();

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imginit()
{
	//UI
	IMAGEMANAGER->addImage("TitleBackground", "image/타이틀/stardewPanorama(1600x900).bmp", 1600, 900, false, MAGENTA);
	IMAGEMANAGER->addImage("Title", "image/타이틀/타이틀(690x318).bmp", 690, 318, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("StartButton", "image/타이틀/Start(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("LoadButton", "image/타이틀/Load(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("ExitButton", "image/타이틀/Exit(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("MaptoolButton", "image/타이틀/maptool(203x318).bmp", 203, 318, 1, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("mouse", "image/마우스.bmp", 180, 60, 3, 1, true, MAGENTA);

	IMAGEMANAGER->addImage("CloseButton", "image/닫기버튼.bmp", 44, 44, true, MAGENTA);
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->	
	//IMAGEMANAGER->		
	//IMAGEMANAGER->		
	//IMAGEMANAGER->
	//IMAGEMANAGER->
	//IMAGEMANAGER->

	//





}

void playGround::soundinit()
{
	
}
