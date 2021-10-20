#include <iostream>
#include <vector>


void ReturnBytes(int);
void PrintBiggestNumber(int* _tData, unsigned int size);
int main() {

	int iPrueba = -559038737;
	ReturnBytes(iPrueba);

	int tTabla[] = { 1,3,2,5,3,0xFFFFFFFF,2 };

	PrintBiggestNumber(tTabla, sizeof(tTabla));

	return 0;
}

//Apartado 1;
void ReturnBytes(int _pNum) 
{
	char *pByte = reinterpret_cast<char*>(&_pNum);
	
	printf("%02hhX\n", *(pByte + 3)); //Este printf printea bien, el std::out printea cosas muy raras
	printf("%02hhX\n", *(pByte + 2));
	printf("%02hhX\n", *(pByte + 1));
	printf("%02hhX\n", *(pByte + 0));
}

void PrintBiggestNumber(int* _tData, unsigned int _size)
{
	int iBiggest = _tData[0];
	for (unsigned int i = 1; i < _size; ++i) 
	{
		if (_tData[i] > iBiggest) {
			iBiggest = _tData[i];
		}
	}
	std::cout << iBiggest<<std::endl;
	std::cout << 0xFFFFFFFF;
}