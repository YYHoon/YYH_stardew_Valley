#include "stdafx.h"
#include "Inventory.h"
#include "ToolItem.h"
void Inventory::Save()
{
	size = _toolInven.size();
	ToolItem* saveTile = new ToolItem[size + 1];
	SaveSize();
	for (int i = 0; i < _toolInven.size(); i++)
	{
		saveTile[i] = *_toolInven[i];
	}
	HANDLE file;
	DWORD write;

	file = CreateFile(("Player.inven"), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveTile, sizeof(ToolItem) * size, &write, NULL);
	CloseHandle(file);
}

void Inventory::Load()
{
	LoadSize();
	ToolItem* saveTile = new ToolItem[size + 1];
	HANDLE file;
	DWORD read;
	vector<ToolItem*> tmp;
	file = CreateFile(("Player.inven"), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, saveTile, sizeof(ToolItem) * size, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < size; i++)
	{
		ToolItem* temp = new ToolItem;
		temp = &saveTile[i];
		temp->SetImageI(temp->GetName());
		tmp.push_back(temp);
	}
	_toolInven = tmp;
}

void Inventory::SaveSize()
{
	size = _toolInven.size();
	HANDLE file;
	DWORD write;

	file = CreateFile(("Inven.size"), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &size, sizeof(int), &write, NULL);

	CloseHandle(file);
}


void Inventory::LoadSize()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(("Inven.size"), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &size, sizeof(int), &read, NULL);

	CloseHandle(file);
}
