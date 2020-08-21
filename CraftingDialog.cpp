#include "stdafx.h"
#include "CraftingDialog.h"

HRESULT CraftingDialog::init()
{
    _CrDiaWindow = IMAGEMANAGER->findImage("ItemInfoWindow");

    _CrDiaRc = RectMake(_ptMouse.x, _ptMouse.y, _CrDiaWindow->getWidth(), _CrDiaWindow->getHeight());
    _SeeStrin = false;

    return S_OK;
}

void CraftingDialog::release()
{
}

void CraftingDialog::TxtOutPut(string itemName)
{
    _CrDiaRc = RectMake(_ptMouse.x +25, _ptMouse.y+35, _CrDiaWindow->getWidth(), _CrDiaWindow->getHeight());
    if (_SeeStrin)
    {
        _CrDiaWindow->render(getMemDC(), _CrDiaRc.left, _CrDiaRc.top);
        if (itemName == "GrilledFish") //구운생선
        {
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+5, "재료", strlen("재료"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+25, "일반생선 : 1EA   감자 : 1EA", strlen("일반생선 : 1EA   감자 : 1EA"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+60, "구운생선 (음식)", strlen("구운생선 (음식)"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 84, "감자와 같이 구운생선", strlen("감자와 같이 구운생선"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+108, "체력 : 40 회복", strlen("체력 : 40 회복"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+130, "기력 : 50 회복", strlen("기력 : 50 회복"));
        }
        if (itemName == "RawFish") //생선회
        {
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 5,  "재료", strlen("재료"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 25, "일반생선 : 1EA", strlen("일반생선 : 1EA"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 60, "생선회 (음식)", strlen("생선회 (음식)"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 84, "얇게 뜬 날 생선", strlen("얇게 뜬 날 생선"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 108, "체력 : 20 회복", strlen("체력 : 20 회복"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 130, "기력 : 30 회복", strlen("기력 : 30 회복"));
        }
        if (itemName == "Salad") //샐러드
        {
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+5,  "재료", strlen("재료"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+25, "케일 : 1EA    파스닙 : 1EA", strlen("케일 : 1EA    파스닙 : 1EA"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+60, "샐러드 (음식)", strlen("샐러드 (음식)"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 84, "건강한 야채샐러드", strlen("건강한 야채샐러드"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+108, "체력 : 10 회복", strlen("체력 : 10 회복"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+130, "기력 : 70 회복", strlen("기력 : 70 회복"));
        }

        if (itemName == "ScareCrow")
        {
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+5, "재료", strlen("재료"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+25, "나무 : 3EA    풀 : 2EA", strlen("나무 : 3EA    풀 : 2EA"));
            TextOut(getMemDC(), _CrDiaRc.left+10, _CrDiaRc.top+60, "허수아비 (제작)", strlen("허수아비 (제작)"));
            TextOut(getMemDC(), _CrDiaRc.left + 10, _CrDiaRc.top + 84, " 까마귀가 작물을 해치지 못하게 막아줍니다.", strlen(" 까마귀가 작물을 해치지 못하게 막아줍니다."));
        }
    }
    else _SeeStrin = false;
}