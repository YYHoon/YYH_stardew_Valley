#include "stdafx.h"
#include "LoadingScene.h"
#include "progressBar.h"
#include "Player.h"

LoadingScene::LoadingScene()
    : _BackGround(nullptr), _LoadingBar(nullptr), _currentCount(NULL)
{
}

LoadingScene::~LoadingScene()
{
}

HRESULT LoadingScene::init()
{
    _BackGround = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");
    _Loading = IMAGEMANAGER->findImage("Loading");

    _player = new Player;
    _player->init();
    _LoadingBar = new progressBar;
    _LoadingBar->init(0, WINSIZEY - 10, WINSIZEX, 10);
    _LoadingBar->setGauge(0, 0);

    _x = _y = _count = 0;

    CreateThread(
        NULL,
        NULL,
        threadfunction,
        this,
        NULL,
        NULL
    );

    return S_OK;
}

void LoadingScene::release()
{
   // SAFE_DELETE(_LoadingBar); 
}

void LoadingScene::update()
{
    _LoadingBar->update();
    _LoadingBar->setGauge(_currentCount, LOADINGMAX);

    if (_currentCount == LOADINGMAX)
    {
        _player->SetPosition(Vector2(1180, 720));
        _player->SavePlayerInfo("playerSave");
        SCENEMANAGER->changeScene("HOME");
    }

    _count++;

    if (_count % 20 == 0)
    {
        _x++;
        if (_x > 2) _x = 0;
    }

}

void LoadingScene::render()
{
    _BackGround->render(getMemDC(), 0, 0);
    _Loading->frameRender(getMemDC(), 100, 800, _x, _y);
    //_LoadingBar->render();
}

DWORD CALLBACK threadfunction(LPVOID lpParameter)
{
    LoadingScene* LoadingHelper = (LoadingScene*)lpParameter;

    while (LoadingHelper->_currentCount != LOADINGMAX)
    {
        Sleep(1);

        LoadingHelper->_currentCount++;
    }

    return 0;
}
