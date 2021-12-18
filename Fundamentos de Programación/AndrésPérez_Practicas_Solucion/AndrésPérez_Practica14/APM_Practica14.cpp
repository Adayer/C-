#include "APM_Practica14.h"

int main() 
{

	//a. La tabla de funciones es una tabla de punteros a punteros, por lo tanto ocupa 4 bytes por funcion extra
	SPadre sPadre;

	//b. La tabla de funciones virtuales se encuentra al inicio de la memoria, en un espacio de solo lectura
	// Esto se ve añadiendo un Watch a sPadre
	SPadre* pPadre = &sPadre; 
	SHijo sHijo;
	SPadre* pHijo = &sHijo;
	SNieto sNieto;
	SPadre* pNieto = &sNieto;
	
	SPadre1 sPadre1;
	SHijo1 sHijo1;
	SNieto1 sNieto1;

	//c. las funciones virtuales añaden un puntero a la tabla de funciones por lo que ocupan 4bytes extra.
	printf("Padre: Sizeof virtual %d vs normal %d\n", sizeof(SPadre), sizeof(SPadre1));
	printf("Hijo: Sizeof virtual %d vs normal %d\n", sizeof(SHijo), sizeof(SHijo1));
	printf("Nieto: Sizeof virtual %d vs normal %d\n", sizeof(SNieto), sizeof(SNieto1));

	//d. Si el constructor no es virtual, se llamará a las 3 versiones de la función empezando por la del padre. 
	//En caso de que el unico con constructor se el padre, solo se llamara a la funcion tal y como este definida por el padre
	//En consola se printean las llamadas a la funcion

	//e. Utilizando breakpoints, la llamada a ambas funciones es la misma. 
	//Pero en memoria podemos suponer que una funcion virtual primero tiene que mirar en la tabla de funciones cual es la funcion a la que llamar, 
	//por lo tanto tiene un paso extra
	sHijo.FuncioPrueba();
	sHijo1.FuncioPruebaHijo();
	
	sNieto.FuncioPrueba();
	sNieto1.FuncioPruebaNieto();
	
	return 0;
}

void SPadre::FuncioPrueba()
{
	printf("Soy padre virtual\n"); 
}
void SHijo::FuncioPrueba()
{
	printf("Soy hijo virtual\n"); 
}
void SNieto::FuncioPrueba()
{
	printf("Soy nieto virtual\n");
}