#include "stdafx.h"
#include "DrainedLoadingScene.h"
#include "progressBar.h"
#include "Player.h"

DrainedLoadingScene::DrainedLoadingScene()
	: _BackGround(nullptr), _LoadingBar(nullptr), _currentCount(NULL)
{
}

DrainedLoadingScene::~DrainedLoadingScene()
{
}

HRESULT DrainedLoadingScene::init()
{
    _BackGround = IMAGEMANAGER->findImage("AlphaOnlyBlackWindow");
    _Loading = IMAGEMANAGER->findImage("DrainLoading");
    _Face = IMAGEMANAGER->findImage("DrainFace");

    _LoadingBar = new progressBar;
    _LoadingBar->init(0, WINSIZEY - 10, WINSIZEX, 10);
    _LoadingBar->setGauge(0, 0);

    _x = _y = _count = 0;

    CreateThread(
        NULL,
        NULL,
        threadfunction2,
        this,
        NULL,
        NULL
    );
    _currentCount = 0;

    return S_OK;
}

void DrainedLoadingScene::release()
{
}

void DrainedLoadingScene::update()
{
    _LoadingBar->update();
    _LoadingBar->setGauge(_currentCount, LOADINGMAX);

    if (_currentCount == LOADINGMAX)
    {
        _player->SetPosition(Vector2(1180, 780));
        SCENEMANAGER->changeScene("HOME");
    }

    _count++;

    if (_count % 20 == 0)
    {
        _x++;
        if (_x > 2) _x = 0;
    }

}

void DrainedLoadingScene::render()
{
    _BackGround->render(getMemDC(), 0, 0);
    _Loading->frameRender(getMemDC(), 100, 800, _x, _y);
    _Face->render(getMemDC(), 720, 360);
}

DWORD threadfunction2(LPVOID lpParameter)
{
    DrainedLoadingScene* LoadingHelper = (DrainedLoadingScene*)lpParameter;

    while (LoadingHelper->_currentCount != LOADINGMAX)
    {
        Sleep(1);

        LoadingHelper->_currentCount++;
    }

	return 0;
}