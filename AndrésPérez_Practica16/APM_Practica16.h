#pragma once
#include <stdio.h>


class IDamageable
{
protected:
	int m_iVida = 0;
public:
	virtual void TakeDamage(int _dmg) = 0;
};
class CMiniom : public IDamageable
{
	virtual void TakeDamage(int _dmg) override;
};

class CElite: public IDamageable
{
public:
	virtual void TakeDamage(int _dmg) override;
	void CounterAttack() { printf("Take this!"); };

};

class CNode
{
public:
	IDamageable* GetObj() { return m_pObj; };
	void SetObj(IDamageable* _char) { m_pObj = _char; };
	void SetNext(CNode* _next) { m_pNext = _next; };
	CNode* GetNext() { return m_pNext; };
	CNode* GetPrevious() { return m_pPrevious; };
	void SetPreviousNode(CNode* _previous) { m_pPrevious = _previous; };

	CNode* operator=(CNode* _right)
	{
		m_pObj = _right->m_pObj;
		m_pNext = _right->m_pNext;
		m_pPrevious = _right->m_pPrevious;
	}
	CNode() {};
	CNode(const CNode& _rOther)
	{
		m_pObj = _rOther.m_pObj;
		m_pNext = _rOther.m_pNext;
		m_pPrevious = _rOther.m_pPrevious;
	}
	~CNode() {};
private:
	IDamageable* m_pObj = nullptr;
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
	unsigned int Size() { return m_iSize; };
	int Push(IDamageable* pNewChar);
	const IDamageable* First();
	const IDamageable* Next();
	IDamageable* Pop();
	void Reset();
	void SetNextToFirst() { m_pCurrent = m_pFirst; };
	void GetReverseList(TList& _tSrc);
	const IDamageable* GetCurrent() { return m_pCurrent->GetObj(); };
private:
	unsigned int m_iSize = 0;
	void SetFirst(IDamageable* _node);
	CNode* m_pFirst = nullptr;
	CNode* m_pCurrent = m_pFirst;
	CNode* m_pTail = nullptr;
};