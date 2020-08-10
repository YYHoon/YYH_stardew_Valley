#pragma once

class ObjectManager
{
	unordered_map<string,vector<class GameObject*>> _vObjectList;
	typedef unordered_map<string, vector<class GameObject*>>::iterator ObjectListIter;

public:
	static ObjectManager* GetInstance();
	void Release();
	void Update();
	void Render();

	void AddGameObject(string objectType,class GameObject* newObject);
	void RemoveGameObject(string objectType,class GameObject* deleteObject);

	GameObject* FindObject(string objectType, string findObject);
	vector<GameObject*> FindObjects(string objectType, string findObject);
	vector<GameObject*>& GetObjectList(string objectType);
};