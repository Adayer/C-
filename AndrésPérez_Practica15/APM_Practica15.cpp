#include "APM_Practica15.h"

int main()
{
	CFile* pFile = new CFile();
	CTcp* pTcp = new CTcp();
	CCom* pCCom = new CCom();

	pFile->Open();
	pFile->Write();
	pFile->Read();
	pFile->Close();
	
	pTcp->Open();
	pTcp->Write();
	pTcp->Read();
	pTcp->Close();
	
	pCCom->Open();
	pCCom->Write();
	pCCom->Read();
	pCCom->Close();
}