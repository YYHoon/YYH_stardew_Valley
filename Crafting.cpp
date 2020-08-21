#include "stdafx.h"
#include "Crafting.h"
#include "Inventory.h"

HRESULT Crafting::init()
{
    _craftItem.Image = IMAGEMANAGER->findImage("GrilledFish");
    _craftItem.ImageBefore = IMAGEMANAGER->findImage("GrilledFish_before");
    _craftItem1.Image = IMAGEMANAGER->findImage("RawFish");
    _craftItem1.ImageBefore = IMAGEMANAGER->findImage("RawFish_before");
    _craftItem2.Image = IMAGEMANAGER->findImage("Salad");
    _craftItem2.ImageBefore = IMAGEMANAGER->findImage("Salad_before");

    _craftItem.x = 408;
    _craftItem.y = 230;

    _craftItem1.x = 508;
    _craftItem1.y = 230;

    _craftItem2.x = 608;
    _craftItem2.y = 230;

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
    _craftItem.Image->render(getMemDC(), _craftItem.x, _craftItem.y);
    _craftItem.ImageBefore->render(getMemDC(), _craftItem.x, _craftItem.y);

    _craftItem1.Image->render(getMemDC(), _craftItem1.x, _craftItem1.y);
    _craftItem1.ImageBefore->render(getMemDC(), _craftItem1.x, _craftItem1.y);

    _craftItem2.Image->render(getMemDC(), _craftItem2.x, _craftItem2.y);
    _craftItem2.ImageBefore->render(getMemDC(), _craftItem2.x, _craftItem2.y);
}
