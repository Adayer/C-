#include "FileUtilities.h"
#include <stdio.h>

//Este fichero incluye la solucion a la practica 7

void* FileUtilities::OpenFile(const char* fileName, const char* mode)
{
	FILE* pFile = new FILE;
	if (!fopen_s(&pFile, fileName, mode))
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

int FileUtilities::CloseFile(void*& file)
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	int err = 0;
	if (!fclose(temp))
	{
		printf("\nYou closed the file.\n");
	}
	else
	{
		printf("\nThe file didn't close the file.\n");
		err = 1;
		return NULL;
	}
	delete file;
	file = nullptr;
	return err;
}

unsigned int FileUtilities::ReadFile(void* file, char* buffer, unsigned int n)
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	//fseek se puede utilizar para empezar en un punto determinado del doc
	//El segundo parametro se utiliza para calcular la posicion de inicio
	//fseek(temp, i * 20 * sizeof(char), SEEK_SET);
	return fread(buffer, sizeof(char), n, temp);
}
unsigned int FileUtilities::WriteFile(void* file, char* buffer, unsigned int n)
{
	FILE* temp = reinterpret_cast<FILE*>(file);
	fseek(temp, 0, SEEK_END); //Se posiciona el "cursor de escritura" al final del archivo
	return fwrite(buffer, sizeof(char), n, temp);
}