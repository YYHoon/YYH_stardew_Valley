#pragma once

enum class RenderType
{
	RENDER,
	FRAMERENDER,
	ANIRENDER,
	ALPHARENDER,
	KEYANIRENDER,
	KEYANIALPHARENDER,
	RECTANGLE,
	END
};

struct TagZOrder
{
	HDC Hdc;
	RenderType RenderType;
	image* Img;
	animation* ani;
	TTYONE_UTIL::MYRECT Rect;
	string KeyName;
	float DextX, DextY;
	int FrameX, FrameY;
	float ShadowZ;
	float SourX, SourY;
	float SourWidth, SourHeight;
	int alpha;
};

class Zorder
{
private:
	vector<TagZOrder> vZList;
public:
	static Zorder* GetInstance();
	void ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY,float ShadowZ);
	void ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, int FrameX, int FrameY, float ShadowZ);
	void ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY,animation* ani, float ShadowZ);
	void ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, animation* ani,string KeyName, float ShadowZ);
	void ZOrderPush(HDC hdc, RenderType type, image* img, float DestX, float DestY, animation* ani, float ShadowZ, int alpha);
	void ZOrderPush(HDC hdc, RenderType type, TTYONE_UTIL::MYRECT rc, float DestX, float DestY, float ShadowZ);
	void MergeZOrder(vector<TagZOrder>& vMerge, int left, int right);
	void MergeSortZOrder(vector<TagZOrder>& vMerge,int left,int right, int mid);
	void ZOrderRender();
	
};

