#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// Tools from Microsoft for detecting memory leaks
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

char getCinPeek()
{
	char peek = std::cin.peek();
	while (peek != '\n' && isspace(peek))
	{
		std::cin.get();
		peek = std::cin.peek();
	}
	return peek;
}

bool reverse_names()
{
	size_t curMaxNames = 4;
	char** names = new char*[curMaxNames];
	names[0] = nullptr;
	size_t nullPosition = 0;
	char buffer[257]{};
	char peek = getCinPeek();
	bool ret = true;

	while (peek != '\n' && ret)
	{
		std::cin >> std::setw(257) >> buffer;
		peek = getCinPeek();
		size_t bufferLength = std::strlen(buffer) + 1;
		names[nullPosition] = new char[bufferLength];
		std::memmove(names[nullPosition], buffer, bufferLength);

		if (std::cin.eof())
		{
			ret = false;
		}

		if (++nullPosition == curMaxNames)
		{
			curMaxNames *= 2;
			char** const doubleSizeNames = new char*[curMaxNames];
			for (int i = 0; i < nullPosition; i++)
			{
				doubleSizeNames[i] = names[i];
			}
			delete[] names;
			names = doubleSizeNames;
		}

		names[nullPosition] = nullptr;
	}
	std::cin.get();

	for (int i = nullPosition - 1; i >= 0; i--)
	{
		std::cout << names[i] << ' ';
	}
	std::cout << std::endl;

	for (int i = 0; i < nullPosition; i++)
	{
		delete[] names[i];
	}
	delete[] names;

	return ret;
}

int main()
{
	while (reverse_names());
	_CrtDumpMemoryLeaks();
	return 0;
}