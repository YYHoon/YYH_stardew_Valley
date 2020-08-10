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
}

void ObjectManager::Updater()
{
}

void ObjectManager::Render()
{
}

void ObjectManager::AddGameObject(Type objectType, GameObject* newObject)
{
}

void ObjectManager::RemoveGameObject(Type objectType, GameObject* deleteObject)
{
}

GameObject* ObjectManager::FindObject(Type objectType, string findObject)
{
	return nullptr;
}

vector<GameObject*> ObjectManager::FindObjects(Type objectType, string findObject)
{
	vector<GameObject*> result;

	vector<GameObject*>& objectList = mObjectList[objectType];

	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == findObject)
		{
			result.push_back(objectList[i]);
		}
	}
	return vector<GameObject*>();
}

vector<GameObject*> ObjectManager::GetObjectList(Type objectType)
{
	
	return mObjectList[objectType];
}
