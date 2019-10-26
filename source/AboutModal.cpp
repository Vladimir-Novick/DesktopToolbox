// AboutModal.cpp: implementation of the CAboutModal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AboutModal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAboutModal::CAboutModal()
{

}

CAboutModal::~CAboutModal()
{

}




HANDLE CAboutModal::threadDDReadWord = NULL;
DWORD CAboutModal::threadIDReadWord = NULL;

CAbout *CAboutModal::pD = NULL;

VOID CAboutModal::ThreadFunc(LPVOID intV){

		       pD = new CAbout;
               pD->DoModal(GetDesktopWindow());//::GetDesktopWindow());
	           delete pD;
			   pD = NULL;
				threadDDReadWord= NULL;

}




int CAboutModal::DoModal(){




HWND m_hWnd2 =  FindWindow(
  NULL,  // class name
  CAbout::strWindowTitle  // window name
  );


if (m_hWnd2 == NULL ){
	    threadDDReadWord = ::CreateThread(0, 0,(LPTHREAD_START_ROUTINE) CAboutModal::ThreadFunc,
                    (LPVOID) 1, 0, &threadIDReadWord);
} else {
	::ShowWindow(m_hWnd2,SW_SHOW);
}

	return 0;
}