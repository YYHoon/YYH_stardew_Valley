#pragma once

enum class RenderType
{
	RENDER,
	FRAMERENDER,
	ANIRENDER,
	ALPHARENDER,
	KEYANIRENDER,
	KEYANIALPHARENDER,
	END
};

struct TagZOrder
{
	HDC Hdc;
	RenderType RenderType;
	image* Img;
	animation* ani;
	//MYRECT Rect;
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
	void MergeZOrder(vector<TagZOrder>& vMerge, int left, int right);
	void MergeSortZOrder(vector<TagZOrder>& vMerge,int left,int right, int mid);
	void ZOrderRender();
	
};

