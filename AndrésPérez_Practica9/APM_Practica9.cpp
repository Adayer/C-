#include "APM_Practica9.h"
#include "FileUtilitiesP9.h"

int main()
{
	//Esta parte demuestra la funcionalidad de la Practica 9
#pragma region Practica9
	/*const char tWord1[] = "Hello";
	const char tWord2[] = "there!";
	const char tWord3[] = "General";
	const char tWord4[] = "Kenobi.";
	const char tWord5[] = "I hate sand.";

	TList tWordList;

	if (tWordList.Push(tWord1))
	{
		printf("%d\n", tWordList.Size());
	}
	if (tWordList.Push(tWord2))
	{
		printf("%d\n", tWordList.Size());
	}


	int iSize = tWordList.Size();
	for (unsigned int i = 0; i < iSize; ++i)
	{
		const char* pPop1 = tWordList.Pop();
		printf("%s ", pPop1);
	}

	printf("\n%d\n", tWordList.Size());

	tWordList.Push(tWord1);
	tWordList.Push(tWord2);

	tWordList.Reset();

	printf("%d\n", tWordList.Size());

	tWordList.Push(tWord3);
	tWordList.Push(tWord4);

	if (tWordList.First() == tWord1)
	{
		printf("Those are the lines of General Kenobi.\n");
	}
	else
	{
		printf("Those are the lines of General Grievous.\n");
	}

	tWordList.Push(tWord5);
	bool bDoesAnakinHaveToSpeak = false;
	iSize = tWordList.Size();
	for (unsigned int i = 0; i < iSize; ++i)
	{
		if (i == 0)
		{
			if (tWordList.First() == tWord5)
			{
				bDoesAnakinHaveToSpeak = true;
				break;
			}
		}
		else
		{
			const char* pNext = tWordList.Next();
			if (pNext)
			{
				if (pNext == tWord5)
				{
					bDoesAnakinHaveToSpeak = true;
					break;
				}
			}
		}
	}
	tWordList.Reset();*/
#pragma endregion

	//Esta parte demuestra la funcionalidad de la Practica 10
#pragma region Practica10

	
	//Ejemplo con ordenador clase: 
	//const char* cFileName = "C:/Users/andres.perez/source/repos/Ejemplo.txt";
	//Ejemplo con portatil: 
	//const char* cFileName = "C:/Users/andre/Desktop/Ejemplo.txt";
	//Ejemplo con ordenador casa: 
	const char* cFileName = "C:/Users/ANDRES/Desktop/Ejemplo.txt";
	
	void* pFile = FileUtilities::OpenFile(cFileName, "r+");
	
	if (pFile)
	{
		TList pNumbers = FileUtilities::Algorithms::FindNumbersInFile(pFile);
		int iQuantityOfNumbersFound = pNumbers.Size();
		int a = 0;
		int bAStartsWith0 = false;
		int bIsNegative = false;
		printf("\n");
		for (unsigned int i = 0; i < iQuantityOfNumbersFound; ++i)
		{
			const char* cReadChar = pNumbers.Pop();
			char charRead = *cReadChar;
			int num = static_cast<int>(charRead);

			printf("%d, ", num);
			delete cReadChar;
		}
	}
	

#pragma endregion

	return 0;
}

int TList::Push(const char* pNewChar)
{
	int iPreviousSize = m_iSize;
	CNode* pCurrent = m_pFirst;
	if (pCurrent) 
	{
		while (pCurrent->GetNext())
		{
			pCurrent = pCurrent->GetNext();
		}
		CNode* newNode = new CNode;
		newNode->SetChar(pNewChar);

		pCurrent->SetNext(newNode);
		if (pCurrent->GetNext()) 
		{
			++m_iSize;
		}
	}
	else 
	{
		SetFirst(pNewChar);
		if (m_pFirst) 
		{
			++m_iSize;
		}
	}
	return m_iSize - iPreviousSize;
}
void TList::SetFirst(const char* _node)
{
	CNode* newFirst = new CNode;
	m_pFirst = newFirst;
	m_pFirst->SetChar(_node);
	m_pFirst->SetNext(nullptr);
	SetNextToFirst();
}
const char* TList::First()
{
	return m_pFirst->GetChar();
}
const char* TList::Next()
{
	m_pCurrent = m_pCurrent->GetNext();
	return m_pCurrent->GetChar();
}
const char* TList::Pop()
{
	--m_iSize;
	CNode* pBuffer = m_pFirst->GetNext();
	const char* pWord = m_pFirst->GetChar();
	delete m_pFirst;
	if (m_iSize == 0)
	{
		printf("");
	}
	if (pWord) 
	{
		m_pFirst = pBuffer;
	}
	else
	{
		m_pFirst = nullptr;
	}
	
	return pWord;
}
void TList::Reset()
{
	CNode* pBuffer;
	CNode* pCurrent = m_pFirst;

	m_pFirst = nullptr;
	m_pCurrent = nullptr;
	m_iSize = 0;

	do
	{
		pBuffer = pCurrent;
		pCurrent = pCurrent->GetNext();
		delete pBuffer;
	} while (pCurrent);
}
TList::TList(const TList& _rOther)
{
	m_iSize = _rOther.m_iSize;
	m_pFirst = _rOther.m_pFirst;
	m_pFirst = _rOther.m_pFirst;
	m_pCurrent = _rOther.m_pCurrent;
	CNode* pCurrent = _rOther.m_pFirst;


	if (pCurrent)
	{
		m_pFirst->SetNext(pCurrent->GetNext());
		pCurrent = m_pFirst->GetNext();
		while (pCurrent)
		{
			pCurrent->SetNext(pCurrent->GetNext());
		}
	}
}