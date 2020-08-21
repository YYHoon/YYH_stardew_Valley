#include "stdafx.h"
#include "Inventory.h"
#include "ToolItem.h"
#include "AllToolItem.h"
void Inventory::Save()
{
	SaveLoad* saveFile = new SaveLoad[13];
	for (int i = 0; i < 12; ++i)
	{
		if (_toolInven[i]->GetName() == "")
		{
			saveFile[i].name = "";
			saveFile[i].num = 0;
		}
		else
		{
			saveFile[i].name = _toolInven[i]->GetName();
			saveFile[i].num = _toolInven[i]->GetNumber();
		}
	}
	HANDLE file;
	DWORD write;

	file = CreateFile("Player.inven", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveFile, sizeof(SaveLoad) * 12, &write, NULL);
	CloseHandle(file);
}

void Inventory::Load()
{
	SaveLoad* loadFile = new SaveLoad[13];
	HANDLE file;
	DWORD read;
	file = CreateFile("Player.inven", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, loadFile, sizeof(SaveLoad) * 12, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < 12; i++)
	{
		if (loadFile[i].name == "")
		{
			_toolInven[i] = new Axe;
			_toolInven[i]->SetToolEnum(TOOLS::NONE);
		}
		else
		{
			for (int j = 0; j < _toolList.size(); ++j)
			{
				if (loadFile[i].name == _toolList[j]->GetName())
				{
					_toolInven[i] = _toolList[j];
					_toolInven[i]->SetNumber(loadFile[i].num);
					break;
				}
			}
		}
	}
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
