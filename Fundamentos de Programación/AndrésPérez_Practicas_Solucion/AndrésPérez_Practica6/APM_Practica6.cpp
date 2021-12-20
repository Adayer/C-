#include "APM_Practica6.h"
#include <stdio.h>


//Esta practica tiene un error que sale al salir de main que no conseguimos descubrir en clase cual era su causa
//Poniendo break point se ve que el funcionamiento de la pracitca es correcto

int main()
{
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con portatil: 
	//const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/ANDRES/Desktop/Ejemplo.txt";

	//Contenido del archivo ->abaaaba abcacaba  aba ba bbaaba

	void* pFile = FileUtilities::OpenFile(cFileName, "r");
	if (pFile)
	{
		char tCharsRead[20];
		char tWordToCheck[] = "aba"; //Cadena ejemplo que poner en el fichero "aba bbaaba hhdiabaa aabaaba abba a b a ab a"
		unsigned int iNumRepetitions = FileUtilities::Algorithms::CheckNumberOfAppearnces(tWordToCheck, 3, pFile); //Deberia devolver 5
		printf("\nLa cadena -%s- se repite %d veces\n",tWordToCheck ,iNumRepetitions);

		int iError = FileUtilities::CloseFile(pFile);
	}
	//if (pFile)
	//{
	//	char tCharsRead[20];
	//	std::vector<int> tResultados;
	//	FileUtilities::Algorithms::AddNumbersInFile(pFile, tResultados); //En el fichero los numeros no pueden ser negativos y tienen que estar de la siguiente forma: X,Y A,B ...
	//	for (int iResultado : tResultados) 
	//	{
	//		printf("%d\n", iResultado);
	//	}

	//	int iError = FileUtilities::CloseFile(pFile);
	//}
	return 0;
}