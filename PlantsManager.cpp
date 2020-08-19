#include "stdafx.h"
#include "PlantsManager.h"
#include "AllMap.h"
#include "AllPlants.h"

void PlantsManager::Init()
{

}

void PlantsManager::Update()
{
	//하루지나면
	if (ENVIRONMENT->GetIsDayIncrease())Growing();
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (_vActivePlantsList[i]->GetName() == "parsnipObject")
		{
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("parsnipObject"));
			switch (_vActivePlantsList[i]->GetGrowCount())
			{
			case 0:
				_vActivePlantsList[i]->GetImage()->setFrameX(0);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 1:
				_vActivePlantsList[i]->GetImage()->setFrameX(1);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 2:
				_vActivePlantsList[i]->GetImage()->setFrameX(2);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 3:
				_vActivePlantsList[i]->GetImage()->setFrameX(3);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 4:
				_vActivePlantsList[i]->GetImage()->setFrameX(4);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			default:
				break;
			}
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 4)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x - 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetImage()->getFrameX(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
		else if (_vActivePlantsList[i]->GetName() == "kaleObject")
		{
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("kaleObject"));
			switch (_vActivePlantsList[i]->GetGrowCount())
			{
			case 0:
				_vActivePlantsList[i]->GetImage()->setFrameX(0);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 1:
				_vActivePlantsList[i]->GetImage()->setFrameX(1);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 2:
				_vActivePlantsList[i]->GetImage()->setFrameX(2);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 3:
				_vActivePlantsList[i]->GetImage()->setFrameX(3);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 4:
				_vActivePlantsList[i]->GetImage()->setFrameX(4);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			default:
				break;
			}
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 4)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x- 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetImage()->getFrameX(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
		else if (_vActivePlantsList[i]->GetName() == "potatoObject")
		{
			_vActivePlantsList[i]->SetImage(IMAGEMANAGER->findImage("potatoObject"));
			switch (_vActivePlantsList[i]->GetGrowCount())
			{
			case 0:
				_vActivePlantsList[i]->GetImage()->setFrameX(0);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 1:
				_vActivePlantsList[i]->GetImage()->setFrameX(1);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 2:
				_vActivePlantsList[i]->GetImage()->setFrameX(2);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 3:
				_vActivePlantsList[i]->GetImage()->setFrameX(3);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 4:
				_vActivePlantsList[i]->GetImage()->setFrameX(4);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			case 5:
				_vActivePlantsList[i]->GetImage()->setFrameX(5);
				_vActivePlantsList[i]->GetImage()->setFrameY(0);
				break;
			default:
				break;
			}
			if (_vActivePlantsList[i]->GetImage()->getFrameX() >= 5)_vActivePlantsList[i]->SetCanHarvest(true);
			ZORDER->ZOrderPush(getMemDC(), RenderType::FRAMERENDER, _vActivePlantsList[i]->GetImage(), _vActivePlantsList[i]->GetPosition().x - 30, _vActivePlantsList[i]->GetPosition().y - 45,
				_vActivePlantsList[i]->GetImage()->getFrameX(), _vActivePlantsList[i]->GetImage()->getFrameY(), _vActivePlantsList[i]->GetRc().bottom);
		}
	}
}

void PlantsManager::render()
{
}

void PlantsManager::Planting(int index, string plantsName)
{
	int centerX = (_map->GetTiles(index).rc.left + _map->GetTiles(index).rc.right) * 0.5;
	int centerY = (_map->GetTiles(index).rc.top + _map->GetTiles(index).rc.bottom) * 0.5;
	Vector2 tileCenter(centerX, centerY);

	if (_map->GetTiles(index).object == MAPOBJECT::HOETILE)
	{
		for (int i = 0; i < _vActivePlantsList.size(); ++i)
		{
			if (_vActivePlantsList[i]->GetSaveIndex() == index)return;
		}
		if (plantsName == "PasnipSeed")
		{
			_parsnip = new ParsnipObject;
			_parsnip->Init();
			_parsnip->SetPosition(tileCenter);
			_parsnip->SavePosIndex(index);
			_vActivePlantsList.push_back(_parsnip);
		}
		else if (plantsName == "KaleSeed")
		{
			_kale = new KaleObject;
			_kale->Init();
			_kale->SetPosition(tileCenter);
			_kale->SavePosIndex(index);
			_vActivePlantsList.push_back(_kale);
		}
		else if (plantsName == "PotatoSeed")
		{
			_potato = new PotatoObject;
			_potato->Init();
			_potato->SetPosition(tileCenter);
			_potato->SavePosIndex(index);
			_vActivePlantsList.push_back(_potato);
		}
		//cout << _vActivePlantsList.size() << endl;
	}
}

void PlantsManager::Growing()
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (!_map->GetTiles()[_vActivePlantsList[i]->GetSaveIndex()].wet)continue;
		_vActivePlantsList[i]->IncreaseGrowCount(+1);
	}
}


void PlantsManager::Harvesting(int index)
{
	for (int i = 0; i < _vActivePlantsList.size(); ++i)
	{
		if (_vActivePlantsList[i]->GetCanHarvest())
		{
			//아이탬매니저 아이탬생성
			
			SAFE_RELEASE(_vActivePlantsList[i]);
			_vActivePlantsList.erase(_vActivePlantsList.begin() + i);
			return;
		}
		else
		{
			SAFE_RELEASE(_vActivePlantsList[i]);
			_vActivePlantsList.erase(_vActivePlantsList.begin() + i);
			return;
		}
	}
}

