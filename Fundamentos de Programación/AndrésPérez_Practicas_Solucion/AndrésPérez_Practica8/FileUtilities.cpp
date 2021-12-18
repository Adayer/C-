#include "FileUtilities.h"

//Returns 0 cuando se abre correctamente el archivo
int TFile::OpenFile(const char* fileName, const char* mode)
{
	if (!fopen_s(&file, fileName, mode))
	{
		printf("\nYou opened the file.\n");
	}
	else
	{
		printf("\nThe file didn't open the file.\n");
		return 1;
	}
	return 0;
}
int TFile::CloseFile()
{
	int err = 0;
	if (!fclose(file))
	{
		printf("\nYou closed the file.\n");
	}
	else
	{
		printf("\nThe file didn't close the file.\n");
		err = 1;
		return NULL;
	}
	return err;
}
unsigned int TFile::ReadFile(char* buffer, unsigned int n)
{
	//fseek se puede utilizar para empezar en un punto determinado del doc
	//El segundo parametro se utiliza para calcular la posicion de inicio
	//fseek(temp, i * 20 * sizeof(char), SEEK_SET);
	return fread(buffer, sizeof(char), n, file);
}
unsigned int TFile::WriteFile(char* buffer, unsigned int n)
{
	fseek(file, 0, SEEK_END); //Se posiciona el "cursor de escritura" al final del archivo
	return fwrite(buffer, sizeof(char), n, file);
}