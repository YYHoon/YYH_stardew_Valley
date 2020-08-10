#include "stdafx.h"
#include "ObjectManager.h"
#include"GameObject.h"

ObjectManager* ObjectManager::GetInstance()
{
	static ObjectManager Instance;
	return &Instance;
}

void ObjectManager::Release()
{
	ObjectListIter iter = _vObjectList.begin();
	for (; iter != _vObjectList.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
		}
	}
	_vObjectList.clear();
}

void ObjectManager::Update()
{
	ObjectListIter iter = _vObjectList.begin();
	for (; iter != _vObjectList.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			cout << objectList[i]->GetActive() << endl;
			if (objectList[i]->GetActive())
				objectList[i]->Update();
		}
	}
}

void ObjectManager::Render()
{
	ObjectListIter iter = _vObjectList.begin();
	for (; iter != _vObjectList.end(); ++iter)
	{
		vector<GameObject*>& objectList = iter->second;
		for (int i = 0; i < objectList.size(); ++i)
		{
			if (objectList[i]->GetActive())
				objectList[i]->Render();
		}
	}
}

void ObjectManager::AddGameObject(string objectType, GameObject* newObject)
{
	_vObjectList[objectType].push_back(newObject);
}

void ObjectManager::RemoveGameObject(string objectType, GameObject* deleteObject)
{
	vector<GameObject*>& objectList = _vObjectList[objectType];
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i] == deleteObject)
		{
			objectList[i]->Release();
			SAFE_DELETE(objectList[i]);
			objectList.erase(objectList.begin() + i);
			return;
		}
	}
}

GameObject* ObjectManager::FindObject(string objectType, string findObject)
{
	vector<GameObject*>& objectList = _vObjectList[objectType];
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->GetType() == findObject)
		{
			return objectList[i];
		}
	}

	return nullptr;
}

vector<GameObject*> ObjectManager::FindObjects(string objectType, string findObject)
{
	vector<GameObject*> result;

	vector<GameObject*>& objectList = _vObjectList[objectType];

	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == findObject)
		{
			result.push_back(objectList[i]);
		}
	}
	return result;
}

vector<GameObject*>& ObjectManager::GetObjectList(string objectType)
{
	
	return _vObjectList[objectType];
}
