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
private:
	const char* m_pChar;

};