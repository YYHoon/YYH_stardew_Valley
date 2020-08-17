#include "stdafx.h"
#include "HpStaminaBar.h"
#include "Player.h"

HRESULT HpStaminaBar::init()
{

//---------------------------------------스테미나----------------------------------------//

	_StaminaBar.x = 1500;
	_StaminaBar.y = 750;
	
	_StaminaBar.topImg = IMAGEMANAGER->addImage("StaminaHead", "image/StBarHead.bmp", 50,58, true, MAGENTA);
	_StaminaBar.midImg = IMAGEMANAGER->addImage("StaminaBody", "image/BarBody.bmp", 50, _pl->GetmaxStamina(), true, MAGENTA);
	_StaminaBar.bottomImg = IMAGEMANAGER->addImage("StaminaBottom", "image/BarBottom.bmp", 50, 17, true, MAGENTA);

	_StaminaBar.frontBarImg =  IMAGEMANAGER->addImage("FrontBar", "image/남은체력스테(25x171).bmp", 25, _pl->GetmaxStamina(), true, MAGENTA);
	_StaminaBar.BottomBarImg = IMAGEMANAGER->addImage("BottomBar", "image/체력스테뒷배경(25x171).bmp", 25, _pl->GetStamina(), true, MAGENTA);

	_StaminaBar.midRc = RectMake(_StaminaBar.x - 12, _StaminaBar.y, _StaminaBar.midImg->getWidth(), _StaminaBar.midImg->getHeight());
	_StaminaBar.frontBarRc = RectMake(_StaminaBar.x, _StaminaBar.y, _StaminaBar.frontBarImg->getWidth(), _StaminaBar.frontBarImg->getHeight());
	_StaminaBar.bottomBarRc = RectMake(_StaminaBar.x, _StaminaBar.y, _StaminaBar.BottomBarImg->getWidth(), _StaminaBar.BottomBarImg->getHeight());

	_StaminaBar.hit = 0;
		
	_pl->SetIncreaseStamina(_StaminaBar.hit);

//------------------------------------------체력----------------------------------------//

	_HpBar.x = 1450;
	_HpBar.y = 750;

	_HpBar.topImg = IMAGEMANAGER->addImage("HpHead", "image/HpBarHead.bmp", 50, 58, true, MAGENTA);
	_HpBar.midImg = IMAGEMANAGER->addImage("HpBody", "image/BarBody.bmp", 50, _pl->GetmaxStamina(), true, MAGENTA);
	_HpBar.bottomImg = IMAGEMANAGER->addImage("HpBottom", "image/BarBottom.bmp", 50, 17, true, MAGENTA);

	_HpBar.frontBarImg = IMAGEMANAGER->addImage("HpFrontBar", "image/남은체력스테(25x171).bmp", 25, _pl->GetmaxStamina(), true, MAGENTA);
	_HpBar.BottomBarImg = IMAGEMANAGER->addImage("HpBottomBar", "image/체력스테뒷배경(25x171).bmp", 25, _pl->GetStamina(), true, MAGENTA);

	_HpBar.midRc = RectMake(_HpBar.x - 12, _HpBar.y, _HpBar.midImg->getWidth(), _HpBar.midImg->getHeight());
	_HpBar.frontBarRc = RectMake(_HpBar.x, _HpBar.y, _HpBar.frontBarImg->getWidth(), _HpBar.frontBarImg->getHeight());
	_HpBar.bottomBarRc = RectMake(_HpBar.x, _HpBar.y, _HpBar.BottomBarImg->getWidth(), _HpBar.BottomBarImg->getHeight());

	_HpBar.hit = 0;

	_pl->SetDecreaseHp(_HpBar.hit);

	return S_OK;
}

void HpStaminaBar::release()
{
}

void HpStaminaBar::update()
{

	if (_StaminaBar.hit > _StaminaBar.frontBarImg->getHeight()) _StaminaBar.hit = _StaminaBar.frontBarImg->getHeight();	
	if (_StaminaBar.hit < 0) _StaminaBar.hit = 0;
	if (_HpBar.hit > _HpBar.frontBarImg->getHeight()) _HpBar.hit = _HpBar.frontBarImg->getHeight();
	if (_HpBar.hit < 0) _HpBar.hit = 0;
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
												 _StaminaBar.BottomBarImg->getWidth(), _StaminaBar.hit); //뽀얀쪽이 길이조정HP

	Font = CreateFont(35, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Sandoll 미생"));
	OldFont = (HFONT)SelectObject(getMemDC(), Font);

	char TT[40];
	sprintf_s(TT, "%d / %d", _pl->GetStamina() - _StaminaBar.hit, _pl->GetmaxStamina());

	if (PtInRect(&_StaminaBar.frontBarRc, _ptMouse))
	{		
		TextOut(getMemDC(), _ptMouse.x + 25, _ptMouse.y+25, TT, strlen(TT));
	}

}

void HpStaminaBar::hpBarRender()
{
	_HpBar.topImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.top - _HpBar.topImg->getHeight() + 8);
	_HpBar.midImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.top);
	_HpBar.bottomImg->render(getMemDC(), _HpBar.midRc.left, _HpBar.midRc.bottom - 8);

	_HpBar.frontBarImg->render(getMemDC(), _HpBar.frontBarRc.left, _HpBar.frontBarRc.top); //연두색쪽이 플레이어MAXHP
	_HpBar.BottomBarImg->render(getMemDC(), _HpBar.bottomBarRc.left, _HpBar.bottomBarRc.top, 0, 0, _HpBar.BottomBarImg->getWidth(), _HpBar.hit); //뽀얀쪽이 길이조정HP

	char TT[40];
	sprintf_s(TT, "%d / %d", _HpBar.frontBarImg->getHeight() - _HpBar.hit, _HpBar.frontBarImg->getHeight());

	if (PtInRect(&_HpBar.frontBarRc, _ptMouse))
	{
		TextOut(getMemDC(), _ptMouse.x + 25, _ptMouse.y + 25, TT, strlen(TT));
	}

}

void HpStaminaBar::setPlayerHP(int hp)
{
	_HpBar.hit -= hp;
}

void HpStaminaBar::setPlayerStamina(int stamina)
{
	_StaminaBar.hit -= stamina;
}
