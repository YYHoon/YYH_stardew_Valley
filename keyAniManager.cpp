#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	//싸그리 해제해주자
	deleteAll();
}

void keyAniManager::update()
{
	iterAnimation iter = _mTotalAnimation.begin();

	for (iter; iter != _mTotalAnimation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;

		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}

	iterTotalEffect vIter;
	HIterAnimations mIter;

	for (vIter = _vTomtalAnimation.begin(); vIter != _vTomtalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay()) continue;
				(*vArrIter)->frameUpdate(TIMEMANAGER->getElapsedTime() *1.0f);
			}
		}
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));

}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back( ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setDefPlayFrame(reverse, loop);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(arr, arrLen, loop);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(start, end, reverse, loop);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj, int buffer)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	

	arrAnimations vAniBuffer;
	HAnimations mArrAnimation;

	for (int i = 0; i < buffer; ++i)
	{
		animation* ani = new animation;
		vAniBuffer.push_back(ani);
		vAniBuffer[i]->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
		vAniBuffer[i]->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
		vAniBuffer[i]->setFPS(fps);
	}
	mArrAnimation.insert(pair<string, arrAnimations>(animationKeyName, vAniBuffer));
	_vTomtalAnimation.push_back(mArrAnimation);
}

void keyAniManager::start(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	iter->second->start();
}

void keyAniManager::stop(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	iter->second->stop();
}

void keyAniManager::pause(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	iter->second->pause();
}

void keyAniManager::resume(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	iter->second->resume();
}

void keyAniManager::StartB(string animationKeyName, animation* ani)
{
	iterTotalEffect vIter;
	HIterAnimations mIter;
	for (vIter = _vTomtalAnimation.begin(); vIter != _vTomtalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if ((mIter->first != animationKeyName)) break;
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->isPlay()) continue;
				if ((*vArrIter) != ani) continue;
				(*vArrIter)->start();
				return;
			}
		}
	}
	ani->stop();
}

void keyAniManager::StopB(string animationKeyName, animation* ani)
{
	iterTotalEffect vIter;
	HIterAnimations mIter;
	for (vIter = _vTomtalAnimation.begin(); vIter != _vTomtalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if ((mIter->first != animationKeyName)) break;
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay()) continue;
				if ((*vArrIter) != ani) continue;
				(*vArrIter)->stop();
				return;
			}
		}
	}
}

void keyAniManager::PauseB(string animationKeyName)
{
	//iterTotalEffect vIter;
	//HIterAnimations mIter;
	//for (vIter = _vTomtalAnimation.begin(); vIter != _vTomtalAnimation.end(); ++vIter)
	//{
	//	for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
	//	{
	//		if ((mIter->first != animationKeyName)) break;
	//		iterAnimations vArrIter;
	//		for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
	//		{
	//			if ((*vArrIter)->isPlay()) continue;
	//			(*vArrIter)->start();
	//			return;
	//		}
	//	}
	//}
}

void keyAniManager::ResumeB(string animationKeyName)
{
	//iterTotalEffect vIter;
	//HIterAnimations mIter;
	//for (vIter = _vTomtalAnimation.begin(); vIter != _vTomtalAnimation.end(); ++vIter)
	//{
	//	for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
	//	{
	//		if ((mIter->first != animationKeyName)) break;
	//		iterAnimations vArrIter;
	//		for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
	//		{
	//			if ((*vArrIter)->isPlay()) continue;
	//			(*vArrIter)->start();
	//			return;
	//		}
	//	}
	//}
}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);

	//찾았다면
	if (iter != _mTotalAnimation.end()) return iter->second;
	return nullptr;
}

animation* keyAniManager::FindBufferAnimation(string animationKeyName)
{
	for (iterTotalEffect iter = _vTomtalAnimation.begin(); iter != _vTomtalAnimation.end(); ++iter)
	{
		HIterAnimations mIter = iter->begin();
		mIter->first.find(animationKeyName);
		if (mIter != iter->end())
		{
			iterAnimations viter = mIter->second.begin();
			for (viter; viter != mIter->second.end(); ++viter)
			{
				if (!(*viter)->isPlay())
				{
					return (*viter);
				}
			}
		}
	}

	return nullptr;
}

void keyAniManager::deleteAll()
{
	for (iterAnimation iter = _mTotalAnimation.begin(); iter != _mTotalAnimation.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimation.erase(iter);
		}
		else ++iter;
	}

	_mTotalAnimation.clear();
	HIterAnimations viter;
	for (iterTotalEffect iter = _vTomtalAnimation.begin(); iter != _vTomtalAnimation.end();++iter)
	{
		for (viter = iter->begin(); viter != iter->end(); ++viter)
		{
			iterAnimations mIter;
			for (mIter = viter->second.begin(); mIter != viter->second.end();) 
			{
				if ((*mIter) != NULL)
				{
					(*mIter)->release();
					SAFE_DELETE((*mIter));
					mIter = viter->second.erase(mIter);
				}
				else ++mIter;
			}
		}
	}

	_vTomtalAnimation.clear();

}
