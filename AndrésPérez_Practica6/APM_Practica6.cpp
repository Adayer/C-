#include "APM_Practica6.h"
#include <stdio.h>

FILE* pFile(nullptr);

int main()
{
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	pFile = reinterpret_cast<FILE*>(OpenFile(cFileName, "r"));
	if (pFile)
	{
		char tCharsRead[20];
		unsigned int iItemsRead = ReadFile(pFile, tCharsRead, 20);
		if (iItemsRead)
		{
			for (unsigned int i = 0; i < iItemsRead; ++i)
			{
				printf("%c", tCharsRead[i]);
			}
		}
	}

	int iError = CloseFile(pFile);
	pFile = reinterpret_cast<FILE*>(OpenFile(cFileName, "a"));
	if (pFile)
	{
		char tCharsToWrite[] = "\nHola buenos dias, esto es un ejemplo.";
		unsigned int iItemsWritten = WriteFile(pFile, tCharsToWrite, 20);
		if (iItemsWritten)
		{
			for (unsigned int i = 0; i < iItemsWritten; ++i)
			{
				printf("%c", tCharsToWrite[i]);
			}
		}

		iError = CloseFile(pFile);
	}

	return 0;
}

void* OpenFile(const char* fileName, const char* mode)
{
	int err = fopen_s(&pFile, fileName, mode);
	if (err == 0)
	{
		printf("\nYou opened the file.\n");
	}
	else
	{
		printf("\nThe file didn't open the file.\n");
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
		printf("\nYou closed the file.\n");
	}
	else
	{
		printf("\nThe file didn't close the file.\n");
		return NULL;
	}
	return err;
}

unsigned int ReadFile(void* file, char* buffer, unsigned int n)
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	//fseek se puede utilizar para empezar en un punto determinado del doc
	//El segundo parametro se utiliza para calcular la posicion de inicio
	//fseek(temp, i * 20 * sizeof(char), SEEK_SET);
	return fread(buffer, sizeof(char), n, temp);
}
unsigned int WriteFile(void* file, char* buffer, unsigned int n)
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	//fseek(temp, 0, SEEK_END); //Se posiciona el "cursor de escritura" al final del archivo
	return fwrite(buffer, sizeof(char), n, temp);
}
