#include "APM_Practica16.h"


int main()
{
	CElite cElite;
	CElite* pElite = &cElite;
	
	CMiniom cMiniom;
	CMiniom* pMiniom = &cMiniom;

	TList tList;

	if (!tList.Push(pElite))
	{
		printf("ERROR POPING INTO LIST\n");
	}
	if (!tList.Push(pMiniom))
	{
		printf("ERROR POPING INTO LIST\n");
	}

	unsigned int iSize = tList.Size();
	for (unsigned int i = 0; i < iSize; ++i)
	{
		IDamageable* pPop1 = tList.Pop();
		pPop1->TakeDamage(30);
		printf("\n");
	}

	return 0;
}

int TList::Push(IDamageable* pNewObj)
{
	int iPreviousSize = m_iSize;
	if (m_pTail)
	{
		CNode* newNode = new CNode;
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

void TList::SetFirst(IDamageable* _node)
{
	CNode* newFirst = new CNode;
	m_pFirst = newFirst;
	m_pFirst->SetObj(_node);
	m_pFirst->SetNext(nullptr);
	m_pTail = newFirst;
	m_pFirst->SetPreviousNode(nullptr);
	SetNextToFirst();
}
const IDamageable* TList::First()
{
	return m_pFirst->GetObj();
}
const IDamageable* TList::Next()
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
IDamageable* TList::Pop()
{
	--m_iSize;
	CNode* pBuffer = m_pFirst->GetNext();
	IDamageable* pWord = m_pFirst->GetObj();

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
	delete m_pFirst;
	m_pFirst = nullptr;
	delete m_pTail;
	m_pTail = nullptr;
}
TList::TList(const TList& _rOther)
{
	CNode* pCurrent = _rOther.m_pFirst;

	while (pCurrent)
	{
		this->Push(pCurrent->GetObj());
		pCurrent = pCurrent->GetNext();
	}
}
void TList::GetReverseList(TList& _tSrc)
{
	CNode* pCurrent = _tSrc.m_pTail;

	while (pCurrent)
	{
		this->Push(pCurrent->GetObj());
		pCurrent = pCurrent->GetPrevious();
	}
}

void CElite::TakeDamage(int _dmg) 
{
	m_iVida -= _dmg;
	printf("Is that all you got?\n");
	CounterAttack();
}

void CMiniom::TakeDamage(int _dmg) 
{
	m_iVida -= _dmg;
	printf("*whimpers*\n");
}