#pragma once
#include <stdio.h>
class CNode
{
public:
	const char* GetChar() { return m_pChar; };
	void SetChar(const char* _char) { m_pChar = _char; };
	void SetNext(CNode* _next) { m_pNext = _next; };
	CNode* GetNext() { return m_pNext; };
private:
	const char* m_pChar = nullptr;
	CNode* m_pNext = nullptr;
};
class TList
{

public:
	int Size() { return m_iSize; };
	int Push(const char* pNewChar);
	const char* First();
	const char* Next();
	const char* Pop();
	void Reset();
	void SetNextToFirst() { m_pCurrent = m_pFirst; };
private:
	unsigned int m_iSize = 0;
	void SetFirst(const char* _node);
	CNode* m_pFirst = nullptr;
	CNode* m_pCurrent = m_pFirst;
};