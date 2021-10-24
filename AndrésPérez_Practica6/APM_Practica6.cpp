#include "APM_Practica6.h"
#include <stdio.h>

FILE* pFile(nullptr);

int main()
{
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	pFile = reinterpret_cast<FILE*>(FileUtilities::OpenFile(cFileName, "r"));
	if (pFile)
	{
		char tCharsRead[20];
		unsigned int iItemsRead = FileUtilities::ReadFile(pFile, tCharsRead, 20);
		if (iItemsRead)
		{
			for (unsigned int i = 0; i < iItemsRead; ++i)
			{
				printf("%c", tCharsRead[i]);
			}
		}
	}

	int iError = FileUtilities::CloseFile(pFile);
	pFile = reinterpret_cast<FILE*>(FileUtilities::OpenFile(cFileName, "a"));
	if (pFile)
	{
		char tCharsToWrite[] = "\nHola buenos dias, esto es un ejemplo.";
		unsigned int iItemsWritten = FileUtilities::WriteFile(pFile, tCharsToWrite, 20);
		if (iItemsWritten)
		{
			for (unsigned int i = 0; i < iItemsWritten; ++i)
			{
				printf("%c", tCharsToWrite[i]);
			}
		}

		iError = FileUtilities::CloseFile(pFile);
	}

	return 0;
}