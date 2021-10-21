#include <iostream>

int main() {

	unsigned int const uDatosJugador(0x054D400C);

	//Bits del 23-16 son las balas
	std::cout << GetNumBullets(uDatosJugador) << "\n";
	//Añadir balas 
	std::cout << AddBullets(uDatosJugador, 10) << "\n";
	//check if bullet time is active
	std::cout << GetIsBulletTimeActive(uDatosJugador) << "\n";
	return 0;
}

#define MASK_1_BYTE 0x000000FF
int GetNumBullets(unsigned int _iData) {
	int iNumBullets = _iData;

	iNumBullets = (iNumBullets >> 16); //iNumBullets pasa a ser 0xXXXXXX4D
	//Hacemos un AND para borrar los bits que no nos interesan y dejar 0x0000004D
	iNumBullets &= MASK_1_BYTE;	

	return iNumBullets;
}

#define MASK_2_BYTE 0x00FF0000
int AddBullets(unsigned int _iData, unsigned int _iBulletsToAdd) {

	int iNumBullets = _iData;

	iNumBullets = (iNumBullets >> 16);
	iNumBullets &= MASK_1_BYTE;

	iNumBullets += _iBulletsToAdd;

	iNumBullets = (iNumBullets << 16);
	iNumBullets &= MASK_2_BYTE;

	int temp = _iData;
	temp &= ~MASK_2_BYTE;
	temp |= iNumBullets;

	return temp;
}

#define MASK_3_BYTE 0X00000002
bool GetIsBulletTimeActive(unsigned int _iData) {
	
	_iData &= MASK_3_BYTE;
	bool bBulletTimeIsActive = _iData; //Si el Bit que encaja con la mascara es 1 entonces el numero que sale no seria 0 por lo tanto seria true y viceversa
	return bBulletTimeIsActive;
}
int ToogleBulletTime(unsigned int _iData) {

	_iData ^= MASK_3_BYTE; // 0 - 0 = 0; (0 - 1) o (1 - 0) = 1 ; 1 - 1 = 0; 
	//Entonces todos los valores originales se mantienen pero el bit que indica si esta o no activo cambia

	return ;
}