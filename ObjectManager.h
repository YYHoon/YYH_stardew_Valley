#pragma once
enum Type 
{
	PLAYER,
	ENEMY,
	END
};

class ObjectManager
{
	unordered_map<Type,vector<class GameObject*>> mObjectList;
	typedef unordered_map<Type, vector<class GameObject*>>::iterator ObjectListIter;

public:
	static ObjectManager* GetInstance();
	void Release();
	void Updater();
	void Render();

	void AddGameObject(Type objectType,class GameObject* newObject);
	void RemoveGameObject(Type objectType,class GameObject* deleteObject);

	GameObject* FindObject(Type objectType, string findObject);
	vector<GameObject*> FindObjects(Type objectType, string findObject);
	vector<GameObject*> GetObjectList(Type objectType);
};

