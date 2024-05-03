#include "FileDialogue.h"
#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

static Vector<nfdfilteritem_t> makeFilterItem(Vector<String> names, Vector<String> specs);

namespace Vivid
{
	String FileDialogue::OpenFile(Vector<String> filterName, Vector<String> filterSpecs)
	{
		NFD_Init();

		nfdchar_t* outPath;
		Vector<nfdfilteritem_t> filterItem = makeFilterItem(filterName, filterSpecs);
		nfdresult_t result = NFD_OpenDialog(&outPath, filterItem.data(), filterItem.size(), NULL);
		String path;
		if (result == NFD_OKAY)
		{
			path = String(outPath);
			std::cout << "Open Path: " << outPath << std::endl;
			NFD_FreePath(outPath);
		}
		else if (result == NFD_CANCEL)
		{
			std::cout << "User pressed cancel." << std::endl;
		}
		else
		{
			std::cerr << "Error: " << NFD_GetError() << std::endl;
		}

		NFD_Quit();

		return path;
	}

	String FileDialogue::SaveFile(Vector<String> filter, Vector<String> filterSpecs)
	{
		NFD_Init();

		nfdchar_t* savePath;

		Vector<nfdfilteritem_t> filterItem = makeFilterItem(filter, filterSpecs);

		nfdresult_t result = NFD_SaveDialog(&savePath, filterItem.data(), 2, NULL, "Untitled.c");
		String path;
		if (result == NFD_OKAY)
		{
			std::cout << "Save Path: " << savePath << std::endl;
			path = String(savePath);
			NFD_FreePath(savePath);
		}
		else if (result == NFD_CANCEL)
		{
			std::cout << "User pressed cancel." << std::endl;
		}
		else
		{
			std::cerr << "Error: " << NFD_GetError() << std::endl;
		}

		NFD_Quit();
		return path;
	}
}

static Vector<nfdfilteritem_t> makeFilterItem(Vector<String> names, Vector<String> specs)
{
	int size = names.size();
	Vector<nfdfilteritem_t> filterItems(size);
	if (size != specs.size())
	{
		printf("Error: Name and extensions size mismatch\n");
		return filterItems;
	}

	for (int i = 0; i < size; i++)
	{
		filterItems[i].name = names[i].c_str();
		filterItems[i].spec = specs[i].c_str();
	}

	return filterItems;
}