#pragma once
class TList
{
public:
	int Size();
	int Push(const char* pNewChar);
	const char* First();
	const char* Next();
	const char* Pop();
	void Reset();
private:
	CNode* m_pFirst;
	CNode* m_pCurrent;
	int m_iSize;
};

class CNode
{
public:
	const char* GetChar() { return m_pChar; };
	void SetChar(const char* _char) { m_pChar = _char; };
	void SetNext(CNode* _next) { m_Next = _next; };
private:
	const char* m_pChar;
	CNode* m_Next;
};