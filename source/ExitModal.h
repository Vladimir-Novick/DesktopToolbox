// ExitModal.h: interface for the CExitModal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXITMODAL_H__2EC09ED3_4295_4ABC_92E7_B5F0E107F56E__INCLUDED_)
#define AFX_EXITMODAL_H__2EC09ED3_4295_4ABC_92E7_B5F0E107F56E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Exit.h"

class CExitModal  
{
private:
	static DWORD threadIDReadWord;
public:
    static HANDLE threadDDReadWord;
	int DoModal();
	static VOID ThreadFunc(LPVOID intV);
	static CExit *pD;
	CExitModal();
	virtual ~CExitModal();

};

#endif // !defined(AFX_EXITMODAL_H__2EC09ED3_4295_4ABC_92E7_B5F0E107F56E__INCLUDED_)
