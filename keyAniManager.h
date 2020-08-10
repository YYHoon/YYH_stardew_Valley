#pragma once
#include "singletonBase.h"
#include <map>

class image;
class animation;

#define ANIBUFFER 20
#define EXTRAANIBUFFER 10

#define TOTALANIBUFFER ANIBUFFER + EXTRAANIBUFFER

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef map<string, animation*>				arrAnimation;
	typedef map<string, animation*>::iterator	iterAnimation;


	typedef vector <animation*>			  arrAnimations;
	typedef vector <animation*>::iterator iterAnimations;

	typedef map<string, arrAnimations>					 HAnimations;
	typedef map<string, arrAnimations>::iterator		 HIterAnimations;

	typedef vector<map<string, arrAnimations>>			 arrTotalEffect;
	typedef vector<map<string, arrAnimations>>::iterator iterTotalEffect;
	

private:
	arrAnimation _mTotalAnimation;
	arrTotalEffect _vTomtalAnimation;
public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);
	//buffer
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop,int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);

	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);
	//buffer
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, int buffer);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj, int buffer);

	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);
	//buffer
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, int buffer);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);
	//buffer
	void StartB(string animationKeyName,animation* ani);
	void StopB(string animationKeyName, animation* ani);
	void PauseB(string animationKeyName);
	void ResumeB(string animationKeyName);
	animation* findAnimation(string animationKeyName);
	animation* FindBufferAnimation(string animationKeyName);

	void deleteAll();

};

