#pragma once
#include <stdio.h>

class CImage 
{
public:
	bool hasAlpha = false;
protected:	
	CImage(bool _type) : hasAlpha(_type) {};
};

class CPNG : public CImage
{
public:
	CPNG() : CImage(true) {};
	void RemoveAlpha() 
	{ 
		printf("Alpha removed\n");  
		alpha = 0.f; 
	}
private:
	float alpha = 1.f; //Value is [0 - 1.f];
};

class CJPG : public CImage
{
public:
	CJPG() : CImage(false) {};
};

class CRAW : public CImage
{
public:
	CRAW() : CImage(false) {};
};