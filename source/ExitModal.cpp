// ExitModal.cpp: implementation of the CExitModal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExitModal.h"
#include "Exit.h"

extern HWND g_ToolboxWindow;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExitModal::CExitModal()
{

}

CExitModal::~CExitModal()
{

}



HANDLE CExitModal::threadDDReadWord = NULL;
DWORD CExitModal::threadIDReadWord = NULL;

CExit *CExitModal::pD = NULL;

VOID CExitModal::ThreadFunc(LPVOID intV){

		       pD = new CExit;
               pD->DoModal(GetDesktopWindow());//::GetDesktopWindow());
	           BOOL ret = pD->boolReturnValue;
	           delete pD;
			   pD = NULL;
	           if (ret == TRUE ){
				  ::PostMessage(g_ToolboxWindow,WM_CLOSE,0,0);
			   }
				threadDDReadWord= NULL;

}




int CExitModal::DoModal(){




HWND m_hWnd2 =  FindWindow(
  NULL,  // class name
  CExit::strWindowTitle  // window name
  );


if (m_hWnd2 == NULL ){
	    threadDDReadWord = ::CreateThread(0, 0,(LPTHREAD_START_ROUTINE) CExitModal::ThreadFunc,
                    (LPVOID) 1, 0, &threadIDReadWord);
} else {
	::ShowWindow(m_hWnd2,SW_SHOW);
}

	return 0;
}


