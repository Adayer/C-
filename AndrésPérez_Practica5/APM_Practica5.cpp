#include "APM_Practica5.h"
#include <stdio.h>

FILE* pFile(nullptr);

int main() 
{
	const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	pFile = reinterpret_cast<FILE*>(OpenFile(cFileName,"r"));
	
	char tCharsRead[30];
	unsigned int iItemsRead = ReadFile(pFile, tCharsRead, 20);
	
	int iError = CloseFile(pFile);
	
	return 0;
}

void* OpenFile(const char* fileName, const char* mode) 
{
	int err = fopen_s(&pFile, fileName, mode);
	if (err == 0) 
	{
		printf("You opened the file.");
	}	
	else
	{
		printf("The file didn't open the file.");
		return NULL;
	}
	return pFile;
}

int CloseFile(void* file) 
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	int err = fclose(temp);
	if (err == 0)
	{
		printf("You closed the file.");
	}
	else
	{
		printf("The file didn't close the file.");
		return NULL;
	}
	return err;
}

unsigned int ReadFile(void* file, char* buffer, unsigned int n) 
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	return fread(buffer, n, n, temp);	
}
unsigned int WriteFile(void* file, char* buffer, unsigned int n) 
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	return fwrite(buffer, n, n, temp);
}