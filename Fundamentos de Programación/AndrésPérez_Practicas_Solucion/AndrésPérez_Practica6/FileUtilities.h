#pragma once
#include <stdio.h>
#include <vector>
void ClearVector(std::vector<char>& , unsigned int );
void ClearArray(char*, unsigned int);
namespace FileUtilities
{
	void* OpenFile(const char* fileName, const char* mode);
	int CloseFile(void*& file);
	unsigned int ReadFile(void* file, char* buffer, unsigned int n);
	unsigned int WriteFile(void* file, char* buffer, unsigned int n);

	namespace Algorithms
	{
		unsigned int CheckNumberOfAppearnces(char* _tStr, const unsigned int _iSize, void* _pFile);
		void AddNumbersInFile(void* _pFile, std::vector<int>& tResultados_);
	}
}