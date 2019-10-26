// AboutModal.h: interface for the CAboutModal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTMODAL_H__1A2AC8C1_1D94_40DB_BC0B_F1CA0F60BB57__INCLUDED_)
#define AFX_ABOUTMODAL_H__1A2AC8C1_1D94_40DB_BC0B_F1CA0F60BB57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "About.h"

class CAboutModal  
{
private:
	static DWORD threadIDReadWord;
public:
    static HANDLE threadDDReadWord;
	int DoModal();
	static VOID ThreadFunc(LPVOID intV);
	static CAbout *pD;
	CAboutModal();
	virtual ~CAboutModal();

};

#endif // !defined(AFX_ABOUTMODAL_H__1A2AC8C1_1D94_40DB_BC0B_F1CA0F60BB57__INCLUDED_)
