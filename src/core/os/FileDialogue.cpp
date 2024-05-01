#include "FileDialogue.h"
#include <nfd.h>
#include <stdio.h>
#include <stdlib.h>


const char* FileDialogue::OpenFile(const char* filter)
{
	NFD_Init();

	nfdchar_t *outPath;
	nfdfilteritem_t filterItem[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
	nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
	if (result == NFD_OKAY)
	{
		puts("Success!");
		puts(outPath);
		NFD_FreePath(outPath);
	}
	else if (result == NFD_CANCEL)
	{
		puts("User pressed cancel.");
	}
	else
	{
		printf("Error: %s\n", NFD_GetError());
	}

	NFD_Quit();
	return 0;
}

const char* FileDialogue::SaveFile(const char* filter)
{
	const char* path = nullptr;

	return path;
}