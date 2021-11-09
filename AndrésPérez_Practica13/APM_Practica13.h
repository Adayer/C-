#pragma once

enum class TypeOfImage
{
	PNG,
	JPG,
	RAW,
	Size
};

class CImage 
{
public:
	TypeOfImage GetImageType() { return m_typeOfImage; };
protected:	
	TypeOfImage m_typeOfImage; 
};

class CPNG : public CImage
{
private:
	float alpha = 0.f; //Value is [0 - 1.f];
public:
	void RemoveAlpha() { alpha = 0.f; }
};

class CJPG : public CImage
{

};

class CRAW : public CImage
{

};