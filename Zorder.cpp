#include "stdafx.h"
#include "Zorder.h"

Zorder* Zorder::GetInstance()
{
	static Zorder Instance;
	return &Instance;
}

void Zorder::ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, float ShadowZ)
{
	TagZOrder ZPush;
	ZPush.Hdc = hdc;
	ZPush.RenderType = type;
	ZPush.Img = img;
	ZPush.DextX = DestX;
	ZPush.DextY = DestY;
	ZPush.ShadowZ = ShadowZ;
	vZList.push_back(ZPush);
}

void Zorder::ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, int FrameX, int FrameY, float ShadowZ)
{
	TagZOrder ZPush;
	ZPush.Hdc = hdc;
	ZPush.RenderType = type;
	ZPush.Img = img;
	ZPush.DextX = DestX;
	ZPush.DextY = DestY;
	ZPush.FrameX = FrameX;
	ZPush.FrameY = FrameY;
	ZPush.ShadowZ = ShadowZ;
	vZList.push_back(ZPush);
}

void Zorder::ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, animation* ani, float ShadowZ)
{

	TagZOrder ZPush;
	ZPush.Hdc = hdc;
	ZPush.RenderType = type;
	ZPush.Img = img;
	ZPush.DextX = DestX;
	ZPush.DextY = DestY;
	ZPush.ani = ani;
	ZPush.ShadowZ = ShadowZ;
	vZList.push_back(ZPush);
}

void Zorder::ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, animation* ani, string KeyName, float ShadowZ)
{
	TagZOrder ZPush;
	ZPush.Hdc = hdc;
	ZPush.RenderType = type;
	ZPush.Img = img;
	ZPush.DextX = DestX;
	ZPush.DextY = DestY;
	ZPush.ani = ani;
	ZPush.KeyName = KeyName;
	ZPush.ShadowZ = ShadowZ;
	vZList.push_back(ZPush);
}


void Zorder::ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, animation* ani, float ShadowZ, int alpha)
{
	TagZOrder ZPush;
	ZPush.Hdc = hdc;
	ZPush.RenderType = type;
	ZPush.Img = img;
	ZPush.DextX = DestX;
	ZPush.DextY = DestY;
	ZPush.ani = ani;
	ZPush.ShadowZ = ShadowZ;
	ZPush.alpha = alpha;
	vZList.push_back(ZPush);
}

void Zorder::MergeZOrder(vector<TagZOrder>& vMerge, int left, int right)
{
	if (left >= right) return;
	int mid = (left + right) / 2;
	MergeZOrder(vMerge, left, mid);
	MergeZOrder(vMerge, mid + 1, right);

	MergeSortZOrder(vMerge, left, right, mid);
}

void Zorder::MergeSortZOrder(vector<TagZOrder>& vMerge, int left, int right, int mid)
{
	vector<TagZOrder> copy(right + 1);
	int copyIndex = 0;
	int i = left, j = mid + 1;
	while (i <= mid && j <= right)
	{
		if (vMerge[i].ShadowZ < vMerge[j].ShadowZ) copy[copyIndex++] = vMerge[i++];
		else copy[copyIndex++] = vMerge[j++];
	}

	while (i <= mid) copy[copyIndex++] = vMerge[i++];
	while (j <= right) copy[copyIndex++] = vMerge[j++];

	for (int k = left, copyIndex = 0; k <= right; k++, copyIndex++)
		vMerge[k] = copy[copyIndex];
}

void Zorder::ZOrderRender()
{
	
	MergeZOrder(vZList, 0, vZList.size() - 1);
	for (int i = 0; i < vZList.size(); i++)
	{
		switch (vZList[i].RenderType)
		{
		case RenderType::RENDER:
			CAMERAMANAGER->render(vZList[i].Hdc, vZList[i].Img, vZList[i].DextX, vZList[i].DextY);
			break;
		case RenderType::FRAMERENDER:
			CAMERAMANAGER->frameRender(vZList[i].Hdc, vZList[i].Img, vZList[i].DextX, vZList[i].DextY, vZList[i].FrameX, vZList[i].FrameY);
			break;
		case RenderType::ANIRENDER:
			CAMERAMANAGER->AniRender(vZList[i].Hdc, vZList[i].Img, vZList[i].DextX, vZList[i].DextY, vZList[i].ani);
			break;
		case RenderType::ALPHARENDER:
			break;
		case RenderType::KEYANIRENDER:
			CAMERAMANAGER->KeyAniRender(vZList[i].Hdc, vZList[i].Img, vZList[i].KeyName, vZList[i].DextX, vZList[i].DextY, vZList[i].ani);
			break;
		case RenderType::KEYANIALPHARENDER:
			CAMERAMANAGER->KeyAnialphaRender(vZList[i].Hdc, vZList[i].Img, vZList[i].DextX, vZList[i].DextY, vZList[i].ani,vZList[i].alpha);
			break;
		case RenderType::END:
			break;
		default:
			break;
		}
	}
	vZList.clear();
}
