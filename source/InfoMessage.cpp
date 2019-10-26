// InfoMessage.cpp : Implementation of CInfoMessage
#include "stdafx.h"
#include "InfoMessage.h"

/////////////////////////////////////////////////////////////////////////////
// CInfoMessage



HANDLE CInfoMessage::threadDDReadWord = NULL;
DWORD CInfoMessage::threadIDReadWord = NULL;

CInfoMessage *CInfoMessage::pD = NULL;

VOID CInfoMessage::ThreadFunc(LPVOID intV){

		       pD = new CInfoMessage;
               pD->DoModal(GetDesktopWindow());//::GetDesktopWindow());
	           delete pD;
			   pD = NULL;
				threadDDReadWord= NULL;

}

void CInfoMessage::ShowMessage(char *message){

	HWND m_hWnd2 =  FindWindow(
		NULL,  // class name
		CInfoMessage::strWindowTitle  // window name
		);


		if (m_hWnd2 == NULL ){
			threadDDReadWord = ::CreateThread(0, 0,(LPTHREAD_START_ROUTINE) CInfoMessage::ThreadFunc,
                    (LPVOID) 1, 0, &threadIDReadWord);
		} else {
			::ShowWindow(m_hWnd2,SW_SHOW);
		}

		return ;
}

	char *CInfoMessage::strWindowTitle  = {"MyDesktopToolbox Information."};
