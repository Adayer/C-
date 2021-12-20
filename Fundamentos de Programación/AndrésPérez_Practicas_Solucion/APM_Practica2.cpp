#include <iostream>
#include <vector>

void ReturnBytes(int, std::vector<char>&);
int GetBiggestNumber(int* _tData, unsigned int size);
char GetBiggestByte(int* _tData, unsigned int _size);
char* ReturnInverted(char* _pStr);


int main() 
{
	//Apartado 1
	int iPrueba = -559038737;
	std::vector<char> tAnswer;
	tAnswer.reserve(4);
	ReturnBytes(iPrueba, tAnswer);

	printf("Returned Bytes-> ");
	for (unsigned int i = 0; i < 4; ++i)
	{
		printf("%02hhX", tAnswer[i]);
	}
	printf("\n");


	int tTabla[] = { 1,3,2,5,3,0xFFFFFFFF,2 };

	//Apartado 2
	int iBiggestInt = GetBiggestNumber(tTabla, sizeof(tTabla) / sizeof(int)); 
	printf("Biggest Int -> %d\n", iBiggestInt);

	//Apartado 3
	char cBiggestByte = GetBiggestByte(tTabla, sizeof(tTabla) / sizeof(int));
	printf("Biggest Byte -> %02hhX\n", cBiggestByte);

	char wordToInvert[] = "Andres";
	printf("%s", wordToInvert);
	
	printf(" invertido es -> %s\n", ReturnInverted(wordToInvert));

	return 0;
}

//Apartado 1;
void ReturnBytes(int _pNum, std::vector<char>& _tPtrs)
{
	char* pByte = reinterpret_cast<char*>(&_pNum);

	int iIndex = sizeof(int) - 1;
	for (int i = iIndex; i >= 0; --i) 
	{
		_tPtrs.push_back(*(pByte + i));
	}
}

int GetBiggestNumber(int *_tData, unsigned int _size)
{
	int iBiggest = INT_MIN;
	for (unsigned int i = 0; i < _size; ++i)
	{
		if (*(_tData + i)> iBiggest) {
			iBiggest = *(_tData + i);
		}
	}
	return iBiggest;
}

char GetBiggestByte(int *_tData, unsigned int _size) 
{
	char cBiggest = CHAR_MIN;
	for (unsigned int i = 0; i < _size; ++i) 
	{
		std::vector<char> tBytes;
		tBytes.reserve(4);
		ReturnBytes(*(_tData + i),tBytes);

		for (unsigned int j = 0; j < sizeof(int); ++j)
		{
			if ((tBytes[j]) > cBiggest) {
				cBiggest = tBytes[j];
			}
		}
	}

	return cBiggest;
}

char* ReturnInverted(char* _pStr)
{
	if (!_pStr) {
		return nullptr;
	}

	int iLength = strlen(_pStr);
	char* pTemp = new char[iLength];

	for (int i = iLength - 1; i >= 0; --i)
	{
		int iIndexInverted = iLength - i - 1;
		int iIndexNormal = i;

		*(pTemp + iIndexInverted) = *(_pStr + i);
	}

	for (unsigned int i = 0; i < iLength; i++)
	{
		*(_pStr + i) = *(pTemp + i);
	}

	delete[] pTemp;
	pTemp = nullptr;
	return _pStr;
}