#include "stdafx.h"
#include "Crafting.h"
#include "ToolItem.h"

HRESULT Crafting::init()
{
    _grilledFish.imageBefore = IMAGEMANAGER->findImage("GrilledFish_before");
    _rawFish.imageBefore = IMAGEMANAGER->findImage("RawFish_before");
    _salad.imageBefore = IMAGEMANAGER->findImage("Salad_before");
    _grilledFish.imageAfter = IMAGEMANAGER->findImage("GrilledFish");
    _rawFish.imageAfter = IMAGEMANAGER->findImage("RawFish");
    _salad.imageAfter = IMAGEMANAGER->findImage("Salad");

    _grilledFish.isPossible = false;
    _salad.isPossible = false;
    _rawFish.isPossible = false;

    _grilledFish.x = 408;
    _grilledFish.y = 230;

    _rawFish.x = 508;
    _rawFish.y = 230;

    _salad.x = 608;
    _salad.y = 230;

    _grilledFish.rc = RectMake(408, 230, 64, 64);
    _rawFish.rc = RectMake(508, 230, 64, 64);
    _salad.rc = RectMake(608, 230, 64, 64);

    return S_OK;
}

void Crafting::release()
{
}

void Crafting::update()
{

}

void Crafting::render()
{
    ///////////////////////////////////// <DebugRect>
    Rectangle(getMemDC(), _grilledFish.rc);
    Rectangle(getMemDC(), _rawFish.rc);
    Rectangle(getMemDC(), _salad.rc);
    ///////////////////////////////////// </DebugRect>
    if (_grilledFish.isPossible) _grilledFish.imageAfter->render(getMemDC(), _grilledFish.x, _grilledFish.y);
    if (_rawFish.isPossible) _rawFish.imageAfter->render(getMemDC(), _rawFish.x, _rawFish.y);
    if (_salad.isPossible) _salad.imageAfter->render(getMemDC(), _salad.x, _salad.y);

    if (!_grilledFish.isPossible) _grilledFish.imageBefore->render(getMemDC(), _grilledFish.x, _grilledFish.y);
    if (!_rawFish.isPossible) _rawFish.imageBefore->render(getMemDC(), _rawFish.x, _rawFish.y);
    if (!_salad.isPossible) _salad.imageBefore->render(getMemDC(), _salad.x, _salad.y);
}
