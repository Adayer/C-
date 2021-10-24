#pragma once
namespace FileUtilities
{
	void* OpenFile(const char* fileName, const char* mode);
	int CloseFile(void* file);
	unsigned int ReadFile(void* file, char* buffer, unsigned int n);
	unsigned int WriteFile(void* file, char* buffer, unsigned int n);
}