#include "FileUtilitiesP9.h"

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

void ClearVector(std::vector<char>& _tVec, unsigned int _iSize)
{
	for (unsigned int i = 0; i < _iSize; ++i) {
		_tVec[i] = '\0';
	}
	return;
}
void ClearArray(char* _pPtr, unsigned int _iSize)
{
	for (unsigned int i = 0; i < _iSize; ++i) {
		_pPtr[i] = '\0';
	}
	return;
}

TList FileUtilities::Algorithms::FindNumbersInFile(void* _pFile)
{
	FILE* pTemp = reinterpret_cast<FILE*>(_pFile);

	TList tNumbersRead;


	int iReadChars = 0;
	
	int a = 0;
	bool bAStartWith0 = false;
	bool bAIsNegative= false;

	unsigned int iLaps = 0;

	bool bFileReadingError = false;

	do
	{
		char tReadChars[21];
		if (iLaps == 0)
		{
			fseek(pTemp, 0, SEEK_SET);
		}
		else
		{
			fseek(pTemp, iLaps * 20 * sizeof(char), SEEK_SET);
		}
		if (iLaps != 0)
		{
			ClearArray(tReadChars, 21);
		}
		iReadChars = FileUtilities::ReadFile(_pFile, tReadChars, 20);

		for (unsigned int i = 0; i < iReadChars; ++i)
		{
			char* newChar = new char;
			*newChar = tReadChars[i];
			int num = static_cast<int>(*newChar - 48); //Si no resto 48 el cast no se hace correctamente
			if (num >= 0 && num <= 9)
			{
				if (a == 0) 
				{
					if (num == 0)
					{
						if (!bAStartWith0)
						{
							bAStartWith0 = true;
						}
					}
					else
					{
						a = a * 10 + num;
					}
				}
				else 
				{
					a = a * 10 + num;
				}
			}
			else if(tReadChars[i] == ',')
			{
				if (a != 0 || bAStartWith0)
				{
					if (bAIsNegative)
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a * -1);
						tNumbersRead.Push(finalValue);
					}
					else
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a);
						tNumbersRead.Push(finalValue);
					}

					a = 0;
					bAIsNegative = false;
					bAStartWith0 = false;
				}
			}
			else if(tReadChars[i] == '-')
			{
				if (a == 0)
				{
					bAIsNegative = true;
				}
				else
				{
					if (bAIsNegative)
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a * -1);
						tNumbersRead.Push(finalValue);
					}
					else
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a);
						tNumbersRead.Push(finalValue);
					}
					a = 0;
					bAIsNegative = false;
					bAStartWith0 = false;
					bFileReadingError = true;
					printf("An unexpected character was found on position %d -> %c.\n", iLaps * 20 + i, tReadChars[i]);
					break;
				}
			}
			else 
			{
				if (a != 0 || bAStartWith0)
				{
					if (bAIsNegative)
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a * -1);
						tNumbersRead.Push(finalValue);
					}
					else
					{
						char* finalValue = new char;
						*finalValue = static_cast<char>(a);
						tNumbersRead.Push(finalValue);
					}
					a = 0;
					bAIsNegative = false;
					bAStartWith0 = false;
				}
				bFileReadingError = true;
				printf("An unexpected character was found on position %d -> %c.\n", iLaps * 20 + i + 1, tReadChars[i]);
				break;
			}			
		}

		++iLaps;

	} while (iReadChars >= 20 && !bFileReadingError);

	if (a != 0 || bAStartWith0)
	{
		if (bAIsNegative)
		{
			char* finalValue = new char;
			*finalValue = static_cast<char>(a * -1);
			tNumbersRead.Push(finalValue);
		}
		else
		{
			char* finalValue = new char;
			*finalValue = static_cast<char>(a);
			tNumbersRead.Push(finalValue);
		}
		a = 0;
		bAIsNegative = false;
		bAStartWith0 = false;
	}

	return tNumbersRead;
}
