#pragma once
#include <stdio.h>
struct SPadre
{
	SPadre()
	{
		FuncioPrueba();
	}
	virtual void FuncioPrueba();
	virtual void FuncioPrueba2() { printf("Soy padre virtual2\n"); };
};

struct SHijo : SPadre
{
	SHijo()
	{
		FuncioPrueba();
	}
	virtual void FuncioPrueba() override;
	virtual void FuncioPrueba2() override { printf("Soy hijo virtual2\n"); };
};
struct SNieto : SHijo
{
	SNieto()
	{
		FuncioPrueba();
	}
	virtual void FuncioPrueba() override;
	virtual void FuncioPrueba2() override { printf("Soy nieto virtual2\n"); };
};

struct SPadre1
{
	void FuncioPruebaPadre() { printf("Soy padre normal\n"); };
};

struct SHijo1 : SPadre1
{
	void FuncioPruebaHijo() { printf("Soy hijo normal\n"); };
};
struct SNieto1 : SHijo1
{
	void FuncioPruebaNieto() { printf("Soy nieto normal\n"); };
};