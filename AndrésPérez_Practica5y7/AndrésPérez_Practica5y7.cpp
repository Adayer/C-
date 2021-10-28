#include "AndrésPérez_Practica5y7.h"
#include <stdio.h>

int main() 
{
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con portatil: 
	//const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/ANDRES/Desktop/Ejemplo.txt";

	void* pFile = FileUtilities::OpenFile(cFileName,"r+");
	if(pFile)
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

		char tCharsToWrite[] = "\nHola buenos dias, esto es un ejemplo.";
		unsigned int iItemsWritten = FileUtilities::WriteFile(pFile, tCharsToWrite, 20);
		if (iItemsWritten)
		{
			for (unsigned int i = 0; i < iItemsWritten; ++i)
			{
				printf("%c", tCharsToWrite[i]);
			}
		}

		int iError = FileUtilities::CloseFile(pFile);
	}
	
	return 0;
}