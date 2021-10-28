#include "FileUtilities.h"

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

unsigned int FileUtilities::Algorithms::CheckNumberOfAppearnces(char* _tStr,const unsigned int _iSize, void* _pFile)
{
	FILE* pTemp = reinterpret_cast<FILE*>(_pFile);

	char tReadChars[20];

	std::vector<char> tBuffer;
	tBuffer.reserve(_iSize);
	tBuffer.resize(_iSize);

	std::vector<char> tBufferDoubleCheck;
	tBufferDoubleCheck.resize(_iSize);
	tBufferDoubleCheck.reserve(_iSize);


	int iReadChars = 0;
	unsigned int iNumCharCoincidences = 0;
	unsigned int iNumStrCoincidences = 0;
	unsigned int iLaps = 0;
	do
	{
		if (iLaps == 0) 
		{
			fseek(pTemp, 0, SEEK_SET);
		}
		else
		{
			fseek(pTemp, iLaps * 20 * sizeof(char), SEEK_SET);
		}
		iReadChars = FileUtilities::ReadFile(_pFile, tReadChars, 20);

		for (unsigned int i = 0; i < iReadChars; ++i) 
		{
			if (tReadChars[i] == _tStr[iNumCharCoincidences]) {

				tBuffer[iNumCharCoincidences] = tReadChars[i];

				++iNumCharCoincidences;
				if (iNumCharCoincidences == _iSize)
				{
					++iNumStrCoincidences;
					ClearVector(tBuffer, iNumCharCoincidences);
					iNumCharCoincidences = 0;
				}
			}
			else if (iNumCharCoincidences >= 0) {
				ClearVector(tBufferDoubleCheck, iNumCharCoincidences);

				unsigned int iNumCharDoubleCheckCoincidences = 0;
				unsigned int iNumCharBeingChecked = 1;

				unsigned int iStartOfNewStr = 1;

				tBuffer[iNumCharCoincidences] = tReadChars[i];

				for (unsigned int j = 1; j <= iNumCharCoincidences; ++j)
				{
					if (tBuffer[j] == _tStr[iNumCharDoubleCheckCoincidences]) {

						tBufferDoubleCheck[iNumCharDoubleCheckCoincidences] = tBuffer[j];

						++iNumCharDoubleCheckCoincidences;
					}
					else {
						++iStartOfNewStr;
						j = iStartOfNewStr;
						++iNumCharBeingChecked;

						ClearVector(tBufferDoubleCheck, iNumCharDoubleCheckCoincidences);
						iNumCharDoubleCheckCoincidences = 0;
					}
				}
				for (unsigned int j = 0; j < iNumCharDoubleCheckCoincidences; ++j) 
				{
					tBuffer[j] = tBufferDoubleCheck[j];
				}


				iNumCharCoincidences = iNumCharDoubleCheckCoincidences;

				//If after the double check las coincidencias son 0 se vacia el vector
				if (iNumCharCoincidences == 0) {
					ClearVector(tBuffer, iNumCharCoincidences);
				}
			}
		}

		++iLaps;

	} while (iReadChars >= 20);

	return iNumStrCoincidences;
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


void FileUtilities::Algorithms::AddNumbersInFile(void* _pFile, std::vector<int>& tResultados_)
{
	FILE* pTemp = reinterpret_cast<FILE*>(_pFile);

	char tReadChars[21];

	int iReadChars = 0;
	unsigned int a = 0;
	unsigned int b = 0;
	bool bFindingA = true;

	bool bAStartsWith0 = false;
	bool bBStartsWith0 = false;

	int iCifra = 0;
	int iNum = 0;

	unsigned int iLaps = 0;
	do
	{
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

		for (unsigned int i = 0; i <= iReadChars; ++i) 
		{			
			int num = static_cast<int>(tReadChars[i] - 48);
			if (tReadChars[i] == ',')
			{
				if (bFindingA) 
				{
					if (a || bAStartsWith0) 
					{
						bFindingA = false;
						iCifra = 0;
					}
					else 
					{
						continue;
					}
				}
			}
			else if (num >= 0 && num <= 9) 
			{
				if (bFindingA) 
				{	
					a = a * 10 + num;
					if (num == 0) 
					{
						if (a == 0 && iCifra == 0) {
							bAStartsWith0 = true;
						}
					}
					iCifra++;
				}
				else 
				{
					b = b * 10 + num;
					if (num == 0)
					{
						if (b == 0 && iCifra == 0) {
							bBStartsWith0 = true;
						}
					}
					iCifra++;
				}
			}
			else if (tReadChars[i] != ',' && (num < 0 || num > 9))
			{
				if(!bFindingA)
				{
					if (b || bBStartsWith0)
					{
						tResultados_.push_back(a + b);
					}
					else 
					{
						printf("ERROR: segundo sumando no es un numero.");
					}
					a = 0;
					b = 0;
					iCifra = 0;
					bAStartsWith0 = false;
					bFindingA = true;
				}
				else
				{
					a = 0;
					b = 0;
					iCifra = 0;
					bAStartsWith0 = false;
				}
			}			
		}

		++iLaps;

	} while (iReadChars >= 20);
}
