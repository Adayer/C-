#include "APM_Practica6Lib.h"
#include <stdio.h>

unsigned int CheckNumberOfAppearnces(char* _tStr, unsigned int _iSize, void* _pFile) 
{
	FILE* pTemp = reinterpret_cast<FILE*>(_pFile);

	char tReadChars[20];
	int iReadChars = 0;
	unsigned int iNumCharCoincidences = 0;
	unsigned int iNumStrCoincidences = 0;
	do
	{
		iReadChars = FileUtilities::ReadFile(_pFile, tReadChars, 20);
		for (unsigned int i = 0; i < iReadChars; ++i) 
		{
			if (tReadChars[i] == _tStr[iNumCharCoincidences]) {
				++iNumCharCoincidences;
				if (iNumCharCoincidences == _iSize)
				{
					++iNumStrCoincidences;
					iNumCharCoincidences = 0;
				}
			}
		}

	}while(iReadChars <= 20)
}