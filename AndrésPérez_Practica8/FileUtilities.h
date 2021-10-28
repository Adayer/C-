#pragma once
#pragma once
#include <stdio.h>
#include <vector>
void ClearVector(std::vector<char>&, unsigned int);
void ClearArray(char*, unsigned int);
class TFile
{
	FILE* file = nullptr;
public:
	int OpenFile(const char* fileName, const char* mode);
	int CloseFile();
	unsigned int ReadFile(char* buffer, unsigned int n);
	unsigned int WriteFile(char* buffer, unsigned int n);
};