#pragma once
#include <stdio.h>
class CNode
{
public:
	const char* GetChar() { return m_pChar; };
	void SetChar(const char* _char) { m_pChar = _char; };
	void SetNext(CNode* _next) { m_pNext = _next; };
	CNode* GetNext() { return m_pNext; };
	CNode* GetPrevious() { return m_pPrevious; };
	void SetPreviousNode(CNode* _previous) { m_pPrevious = _previous; };

	CNode* operator=(CNode* _right)
	{
		m_pChar = _right->m_pChar;
		m_pNext = _right->m_pNext;
		m_pPrevious = _right->m_pPrevious;
	}
	CNode() {};
	CNode(const CNode& _rOther)
	{
		m_pChar = _rOther.m_pChar;
		m_pNext = _rOther.m_pNext;
		m_pPrevious = _rOther.m_pPrevious;
	}
	~CNode() {};
private:
	const char* m_pChar = nullptr;
	CNode* m_pNext = nullptr;
	CNode* m_pPrevious = nullptr;
};
class TList
{
public:
	TList(const TList& _rOther);
	TList(){}
	~TList()
	{
		CNode* pCurrent = m_pTail;

		if (pCurrent)
		{
			while (pCurrent->GetPrevious())
			{
				pCurrent = pCurrent->GetPrevious();
				delete pCurrent->GetNext();
				pCurrent->SetNext(nullptr);
			}
			delete m_pTail;
		}

		if (m_pFirst)
		{
			delete m_pFirst;
		}


		m_pFirst = nullptr;
		m_pCurrent = nullptr;
		m_pTail = nullptr;


		m_iSize = 0;
	}
	int Size() { return m_iSize; };
	int Push(const char* pNewChar);
	const char* First();
	const char* Next();
	const char* Pop();
	void Reset();
	void SetNextToFirst() { m_pCurrent = m_pFirst; };
	void GetReverseList(TList& _tSrc);
	const char* GetCurrent() { return m_pCurrent->GetChar(); };
private:
	unsigned int m_iSize = 0;
	void SetFirst(const char* _node);
	CNode* m_pFirst = nullptr;
	CNode* m_pCurrent = m_pFirst;
	CNode* m_pTail = nullptr;
};