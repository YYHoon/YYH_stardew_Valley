#include "stdafx.h"
#include "ParsnipObject.h"
#include "PlantsManager.h"

void PlantsManager::Save()
{
	Plants* saveTile = new Plants[_vActivePlantsList.size() + 1];
	size = _vActivePlantsList.size();
	SaveSize();
	for (int i = 0; i < _vActivePlantsList.size(); i++)
	{
		saveTile[i] = *_vActivePlantsList[i];
	}
	HANDLE file;
	DWORD write;

	file = CreateFile("FarmPlants.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveTile, sizeof(Plants) * size, &write, NULL);
	CloseHandle(file);
}

void PlantsManager::Load()
{
	LoadSize();
	Plants* saveTile = new Plants[size + 1];
	HANDLE file;
	DWORD read;
	vector<Plants*> tmp;
	file = CreateFile("FarmPlants.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(Plants) * size, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < size; i++)
	{
		Plants* temp = new Plants;
		temp = &saveTile[i];
		tmp.push_back(temp);
		cout << temp->GetName() << endl;
	}
}

void PlantsManager::SaveSize()
{
	size = _vActivePlantsList.size();
	HANDLE file;
	DWORD write;

	file = CreateFile(("masize.size"), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &size, sizeof(int), &write, NULL);

	CloseHandle(file);
}


void PlantsManager::LoadSize()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(("masize.size"), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &size, sizeof(int), &read, NULL);

	CloseHandle(file);
	cout << size << "Å©±â" << endl;
}
