#include <vector>
#include <string>

char* ReturnStringInTable(const std::vector<char*>&, const int = 0);
void ReturnInvertedStringInTable(const std::vector<char*>& _tData, const int _iIndex, std::vector<char>& tInverted_);
int main()
{
	std::vector<char*> tCadenas;

	char palabra0[] = "Archivo";
	tCadenas.push_back(palabra0);

	char palabra1[] = "Editar";
	tCadenas.push_back(palabra1);

	char palabra2[] = "Ver";
	tCadenas.push_back(palabra2);

	char palabra3[] = "Git";
	tCadenas.push_back(palabra3);

	char palabra4[] = "Proyecto";
	tCadenas.push_back(palabra4);

	char* pReturnedNormal = ReturnStringInTable(tCadenas, 1);
	if (pReturnedNormal) {
		printf("The list returns: %s\n", pReturnedNormal);
	}
	else {
		printf("The list failed to return a word!");
	}

	std::vector<char> tReturnInverted;
	ReturnInvertedStringInTable(tCadenas, 0, tReturnInverted);
	
	if (tReturnInverted.size() > 0)
	{
		printf("The list returns: ");
		for (char c : tReturnInverted) 
		{
			printf("%c", c);
		}
		printf("\n");
	}
	else 
	{
		printf("The list failed to return an inverted word!");
	}

	ReturnInvertedStringInTable(tCadenas, 4, tReturnInverted);

	if (tReturnInverted.size() > 0)
	{
		printf("The list returns: ");
		for (char c : tReturnInverted)
		{
			printf("%c", c);
		}
		printf("\n");
	}
	else
	{
		printf("The list failed to return an inverted word!");
	}

	return 0;
}

char* ReturnStringInTable(const std::vector<char*>& _tData, const int _iIndex)
{
	if ((_iIndex >= 0) && (_iIndex <= (sizeof(_tData) / sizeof(char*))))
	{
		return _tData[_iIndex];
	}
	return nullptr;
}

void ReturnInvertedStringInTable(const std::vector<char*>& _tData, const int _iIndex, std::vector<char>& tInverted_)
{
	if ((_iIndex >= 0) && (_iIndex <= (sizeof(_tData) / sizeof(char*))))
	{
		int iLength = strlen(_tData[_iIndex]);
		
		tInverted_.resize(iLength);

		for (int i = iLength - 1; i >= 0; --i)
		{
			int iIndexInverted = iLength - i - 1;
			tInverted_[iIndexInverted] = (*(_tData[_iIndex] + i));
		}
	}
	return;
}