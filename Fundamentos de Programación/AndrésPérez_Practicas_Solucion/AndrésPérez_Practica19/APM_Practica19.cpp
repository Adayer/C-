#include "APM_Practica19.h"
int main()
{
	TList<int> tInts;
	int val1(1);
	int val2(2);
	int val3(3);
	int val4(4);


	if (!tInts.Push(&val1))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tInts.Push(&val2))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tInts.Push(&val3))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tInts.Push(&val4))
	{
		printf("ERROR POPING INTO LIST\n");
	}

	unsigned int iSizeI = tInts.Size();
	int iResult(0);
	for (unsigned int i = 0; i < iSizeI; ++i)
	{
		int* pPop1 = tInts.Pop();
		iResult += *pPop1;
		printf("%d\n", *pPop1);
	}

	printf("result = %d\n\n", iResult);
	
	TList<float> tFloats;
	float float1(34.34f);
	float float2(9.12f);
	float float3(3.f);
	float float4(63.09f);


	if (!tFloats.Push(&float1))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tFloats.Push(&float2))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tFloats.Push(&float3))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tFloats.Push(&float4))
	{
		printf("ERROR POPING INTO LIST\n");
	}

	unsigned int iSizeF = tFloats.Size();
	float fResult(0);
	for (unsigned int i = 0; i < iSizeF; ++i)
	{
		float* pPop1 = tFloats.Pop();
		printf("%.2f\n", *pPop1);
		fResult += *pPop1;
	}

	printf("result = %.2f\n", fResult);

	return 0;
}

template<class T>
int TList<T>::Push(T* pNewObj)
{
	int iPreviousSize = m_iSize;
	if (m_pTail)
	{
		CNode<T>* newNode = new CNode<T>;
		newNode->SetObj(pNewObj);

		m_pTail->SetNext(newNode);
		if (m_pTail->GetNext())
		{
			++m_iSize;
			newNode->SetPreviousNode(m_pTail);
			m_pTail = newNode;
		}
	}
	else
	{
		SetFirst(pNewObj);
		if (m_pFirst)
		{
			++m_iSize;
		}
	}
	return m_iSize - iPreviousSize;
}

template<class T>
void TList<T>::SetFirst(T* _node)
{
	CNode<T>* newFirst = new CNode<T>;
	m_pFirst = newFirst;
	m_pFirst->SetObj(_node);
	m_pFirst->SetNext(nullptr);
	m_pTail = newFirst;
	m_pFirst->SetPreviousNode(nullptr);
	SetNextToFirst();
}

template<class T>
const T* TList<T>::First()
{
	return m_pFirst->GetObj();
}

template<class T>
const T* TList<T>::Next()
{
	if (m_pCurrent->GetNext())
	{
		m_pCurrent = m_pCurrent->GetNext();
		return m_pCurrent->GetObj();
	}
	else
	{
		return nullptr;
	}
}

template<class T>
T* TList<T>::Pop()
{
	--m_iSize;
	CNode<T>* pBuffer = m_pFirst->GetNext();
	T* pWord = m_pFirst->GetObj();

	if (m_iSize == 0)
	{
		delete m_pTail;
		m_pTail = nullptr;
		m_pFirst = nullptr;
	}

	if (pBuffer)
	{
		m_pFirst = pBuffer;
	}

	return pWord;
}

template<class T>
void TList<T>::Reset()
{
	CNode<T>* pBuffer;
	CNode<T>* pCurrent = m_pFirst;

	m_pFirst = nullptr;
	m_pCurrent = nullptr;
	m_iSize = 0;

	do
	{
		pBuffer = pCurrent;
		pCurrent = pCurrent->GetNext();
		delete pBuffer;
	} while (pCurrent);
	delete m_pFirst;
	m_pFirst = nullptr;
	delete m_pTail;
	m_pTail = nullptr;
}
template<class T>
TList<T>::TList(const TList<T>& _rOther)
{
	CNode<T>* pCurrent = _rOther.m_pFirst;

	while (pCurrent)
	{
		this->Push(pCurrent->GetObj());
		pCurrent = pCurrent->GetNext();
	}
}

template<class T>
void TList<T>::GetReverseList(TList<T>& _tSrc)
{
	CNode<T>* pCurrent = _tSrc.m_pTail;

	while (pCurrent)
	{
		this->Push(pCurrent->GetObj());
		pCurrent = pCurrent->GetPrevious();
	}
}