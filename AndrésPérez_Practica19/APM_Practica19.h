#pragma once
#include <stdio.h>

template<class T>
class CNode
{
public:
	T* GetObj() { return m_pObj; };
	void SetObj(T* _char) { m_pObj = _char; };
	void SetNext(CNode<T>* _next) { m_pNext = _next; };
	CNode<T>* GetNext() { return m_pNext; };
	CNode<T>* GetPrevious() { return m_pPrevious; };
	void SetPreviousNode(CNode<T>* _previous) { m_pPrevious = _previous; };

	CNode<T>* operator=(CNode<T>* _right)
	{
		m_pObj = _right->m_pObj;
		m_pNext = _right->m_pNext;
		m_pPrevious = _right->m_pPrevious;
	}
	CNode<T>() {};
	CNode<T>(const CNode<T>& _rOther)
	{
		m_pObj = _rOther.m_pObj;
		m_pNext = _rOther.m_pNext;
		m_pPrevious = _rOther.m_pPrevious;
	}
	~CNode<T>() {};
private:
	T* m_pObj = nullptr;
	CNode<T>* m_pNext = nullptr;
	CNode<T>* m_pPrevious = nullptr;
};

template<class T> class TList
{
public:
	TList<T>(const TList<T>& _rOther);
	TList<T>() {}
	~TList<T>()
	{
		CNode<T>* pCurrent = m_pTail;

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
	unsigned int Size() { return m_iSize; };
	int Push(T* pNewChar);
	const T* First();
	const T* Next();
	T* Pop();
	void Reset();
	void SetNextToFirst() { m_pCurrent = m_pFirst; };
	void GetReverseList(TList<T>& _tSrc);
	const T* GetCurrent() { return m_pCurrent->GetObj(); };
private:
	unsigned int m_iSize = 0;
	void SetFirst(T* _node);
	CNode<T>* m_pFirst = nullptr;
	CNode<T>* m_pCurrent = m_pFirst;
	CNode<T>* m_pTail = nullptr;
};