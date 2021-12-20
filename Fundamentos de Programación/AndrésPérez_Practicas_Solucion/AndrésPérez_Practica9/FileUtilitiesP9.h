#pragma once
#include <stdio.h>
#include <vector>
#include "APM_Practica9.h"

void ClearVector(std::vector<char>&, unsigned int);
void ClearArray(char*, unsigned int);

namespace FileUtilities
{
	void* OpenFile(const char* fileName, const char* mode);
	int CloseFile(void*& file);
	unsigned int ReadFile(void* file, char* buffer, unsigned int n);
	unsigned int WriteFile(void* file, char* buffer, unsigned int n);

	namespace Algorithms
	{
		TList FindNumbersInFile(void* _pFile);
	}
}