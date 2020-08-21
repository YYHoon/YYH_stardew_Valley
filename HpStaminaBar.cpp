#include "stdafx.h"
#include "HpStaminaBar.h"
#include "Player.h"

HRESULT HpStaminaBar::init()
{
	//---------------------------------------스테미나----------------------------------------//

	_StaminaBar.x = 1500;
	_StaminaBar.y = 750;

	_StaminaBar.topImg = IMAGEMANAGER->addImage("StaminaHead", "image/StBarHead.bmp", 50, 58, true, MAGENTA);
	_StaminaBar.midImg = IMAGEMANAGER->addImage("StaminaBody", "image/BarBody.bmp", 50, _pl->GetmaxStamina(), true, MAGENTA);
	_StaminaBar.bottomImg = IMAGEMANAGER->addImage("StaminaBottom", "image/BarBottom.bmp", 50, 17, true, MAGENTA);

	_StaminaBar.frontBarImg = IMAGEMANAGER->addImage("FrontBar", "image/남은체력스테(25x171).bmp", 25, _pl->GetmaxStamina(), true, MAGENTA);
	_StaminaBar.BottomBarImg = IMAGEMANAGER->addImage("BottomBar", "image/체력스테뒷배경(25x171).bmp", 25, _pl->GetStamina(), true, MAGENTA);

	//------파츠들----------//
	_StaminaBar.midRc = RectMake(_StaminaBar.x - 12, _StaminaBar.y, _StaminaBar.midImg->getWidth(), _StaminaBar.midImg->getHeight());
	_StaminaBar.frontBarRc = RectMake(_StaminaBar.x, _StaminaBar.y, _StaminaBar.frontBarImg->getWidth(), _StaminaBar.frontBarImg->getHeight());
	_StaminaBar.bottomBarRc = RectMake(_StaminaBar.x, _StaminaBar.y, _StaminaBar.BottomBarImg->getWidth(), _StaminaBar.BottomBarImg->getHeight());
	//----------------------//
	_StaminaBar.hit = 0;


	//------------------------------------------체력----------------------------------------//

	_HpBar.x = 1450;
	_HpBar.y = 750;

	_HpBar.topImg = IMAGEMANAGER->addImage("HpHead", "image/HpBarHead.bmp", 50, 58, true, MAGENTA);
	_HpBar.midImg = IMAGEMANAGER->addImage("HpBody", "image/BarBody.bmp", 50, _pl->GetMaxHp(), true, MAGENTA);
	_HpBar.bottomImg = IMAGEMANAGER->addImage("HpBottom", "image/BarBottom.bmp", 50, 17, true, MAGENTA);

	_HpBar.frontBarImg = IMAGEMANAGER->addImage("HpFrontBar", "image/남은체력스테(25x171).bmp", 25, _pl->GetMaxHp(), true, MAGENTA);
	_HpBar.BottomBarImg = IMAGEMANAGER->addImage("HpBottomBar", "image/체력스테뒷배경(25x171).bmp", 25, _pl->GetHp(), true, MAGENTA);

	_HpBar.midRc = RectMake(_HpBar.x - 12, _HpBar.y, _HpBar.midImg->getWidth(), _HpBar.midImg->getHeight());
	_HpBar.frontBarRc = RectMake(_HpBar.x, _HpBar.y, _HpBar.frontBarImg->getWidth(), _HpBar.frontBarImg->getHeight());
	_HpBar.bottomBarRc = RectMake(_HpBar.x, _HpBar.y, _HpBar.BottomBarImg->getWidth(), _HpBar.BottomBarImg->getHeight());

	_HpBar.hit = 0;

	return S_OK;
}

void HpStaminaBar::release()
{
}

void HpStaminaBar::update()
{
	if (_pl->GetStamina() <= 0)
	{
		_pl->SetStamina(_pl->GetmaxStamina());
		_pl->SetHp(_pl->GetMaxHp());

		SCENEMANAGER->changeScene("DariLoading");
	}
}

void HpStaminaBar::staminaBarRender()
{
	SetBkMode(getMemDC(), 1);
	SetTextColor(getMemDC(), BLACK);

	_StaminaBar.topImg->render(getMemDC(), _StaminaBar.midRc.left, _StaminaBar.midRc.top - _StaminaBar.topImg->getHeight() + 8);
	_StaminaBar.midImg->render(getMemDC(), _StaminaBar.midRc.left, _StaminaBar.midRc.top);
	_StaminaBar.bottomImg->render(getMemDC(), _StaminaBar.midRc.left, _StaminaBar.midRc.bottom - 8);


	_StaminaBar.frontBarImg->render(getMemDC(), _StaminaBar.frontBarRc.left, _StaminaBar.frontBarRc.top); //연두색쪽이 플레이어MAX스테미나	
	_StaminaBar.BottomBarImg->render(getMemDC(), _StaminaBar.bottomBarRc.left, _StaminaBar.bottomBarRc.top, 0, 0,
		_StaminaBar.BottomBarImg->getWidth(), -_pl->GetStamina() + _pl->GetmaxStamina()); //뽀얀쪽이 길이조정HP

	HFONT STFont, OldSTFont;
	STFont = CreateFont(35, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldSTFont = (HFONT)SelectObject(getMemDC(), STFont);

	char TT[10];
	sprintf_s(TT, "%d / %d", _pl->GetStamina(), _pl->GetmaxStamina());

	if (PtInRect(&_StaminaBar.frontBarRc, _ptMouse))
	{
		TextOut(getMemDC(), _ptMouse.x - 30, _ptMouse.y + 30, TT, strlen(TT));
	}

	SelectObject(getMemDC(), OldSTFont);
	DeleteObject(OldSTFont);
	DeleteObject(STFont);
}

void HpStaminaBar::hpBarRender()
{
	_HpBar.topImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.top - _HpBar.topImg->getHeight() + 8);
	_HpBar.midImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.top);
	_HpBar.bottomImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.bottom - 8);

	_HpBar.frontBarImg->render(getMemDC(), _HpBar.frontBarRc.left, _HpBar.frontBarRc.top); //연두색쪽이 플레이어MAXHP
	_HpBar.BottomBarImg->render(getMemDC(), _HpBar.bottomBarRc.left, _HpBar.bottomBarRc.top, 0, 0, _HpBar.BottomBarImg->getWidth(), -_pl->GetHp() + _pl->GetMaxHp()); //뽀얀쪽이 길이조정HP

	HFONT HpFont, OldHpFont;
	HpFont = CreateFont(35, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldHpFont = (HFONT)SelectObject(getMemDC(), HpFont);

	char TT2[10];
	sprintf_s(TT2, "%d / %d", _pl->GetHp(), _pl->GetMaxHp());

	if (PtInRect(&_HpBar.frontBarRc, _ptMouse))
	{
		TextOut(getMemDC(), _ptMouse.x - 30, _ptMouse.y + 30, TT2, strlen(TT2));
	}
	SelectObject(getMemDC(), OldHpFont);
	DeleteObject(OldHpFont);
	DeleteObject(HpFont);
}