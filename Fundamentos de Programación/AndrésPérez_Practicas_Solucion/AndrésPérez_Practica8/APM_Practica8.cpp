#include "APM_Practica8.h"

int main()
{
	TFile newFile;
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con portatil: 
	//const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/ANDRES/Desktop/Ejemplo.txt";

	
	if (!newFile.OpenFile(cFileName, "r+"))
	{
		char tCharsRead[20];
		unsigned int iItemsRead = newFile.ReadFile(tCharsRead, 20);
		if (iItemsRead)
		{
			for (unsigned int i = 0; i < iItemsRead; ++i)
			{
				printf("%c", tCharsRead[i]);
			}
		}

		char tCharsToWrite[] = "\nHola buenos dias, esto es un ejemplo.";
		unsigned int iItemsWritten = newFile.WriteFile(tCharsToWrite, 20);
		if (iItemsWritten)
		{
			for (unsigned int i = 0; i < iItemsWritten; ++i)
			{
				printf("%c", tCharsToWrite[i]);
			}
		}

		int iError = newFile.CloseFile();
	}
	return 0;
}