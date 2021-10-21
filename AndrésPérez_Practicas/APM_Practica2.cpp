#include <iostream>
#include <vector>

void ReturnBytes(int, std::vector<char>&);
int GetBiggestNumber(int* _tData, unsigned int size);
char GetBiggestByte(int* _tData, unsigned int _size);
int main() 
{
	//Apartado 1
	int iPrueba = -559038737;
	std::vector<char> tAnswer;
	tAnswer.reserve(4);
	ReturnBytes(iPrueba, tAnswer);


	int tTabla[] = { 1,3,2,5,3,0xFFFFFFFF,2 };

	//Apartado 2
	int iBiggestInt = GetBiggestNumber(tTabla, sizeof(tTabla) / sizeof(int)); 
	std::cout << iBiggestInt << std::endl;

	//Apartado 3
	char cBiggestByte = GetBiggestByte(tTabla, sizeof(tTabla) / sizeof(int));
	printf("%02hhX\n", cBiggestByte);

	return 0;
}

//Apartado 1;
void ReturnBytes(int _pNum, std::vector<char>& _tPtrs)
{
	char* pByte = reinterpret_cast<char*>(&_pNum);
	/*std::vector<char*> tPtrChars;
	tPtrChars.reserve(4);*/

	for (int i = 3; i >= 0; --i) 
	{
		printf("%02hhX\n", *(pByte + i)); //Este printf printea bien, el std::out printea cosas muy raras
		_tPtrs.push_back(*(pByte + i));
	}
	std::cout << _tPtrs[0] << std::endl;
}

int GetBiggestNumber(int *_tData, unsigned int _size)
{
	int iBiggest = *(_tData + 0);
	for (unsigned int i = 1; i < _size; ++i)
	{
		//std::cout << iBiggest << std::endl;
		
		//std::cout << *(_tData + i) << std::endl << std::endl;

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
		std::cout <<"---->" << *(_tData + i)  << std::endl;
		std::vector<char> tBytes;
		//tBytes.reserve(4);
		ReturnBytes(*(_tData + i),tBytes);

		std::cout << "Pointer 0 " << tBytes[0] << std::endl;

		for (unsigned int j = 0; j < sizeof(int); ++j)
		{
			printf("\n%02hhX\n", cBiggest);
			printf("%02hhX\n\n", tBytes[j]);

			if ((tBytes[j]) > cBiggest) {
				cBiggest = tBytes[j];
			}
		}
	}

	return cBiggest;
}

