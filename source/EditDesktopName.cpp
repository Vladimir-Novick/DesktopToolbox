// EditDesktopName.cpp : Implementation of CEditDesktopName
#include "stdafx.h"
#include "EditDesktopName.h"
#include "RegisterSave.h"
//#include "MyDesktop.h"


/////////////////////////////////////////////////////////////////////////////
// CEditDesktopName

HWND CEditDesktopName::hWnd_EditDesktopName;


DWORD WINAPI CEditDesktopName::CEditDesktopNameProc(void* pv)
{
	    HRESULT hRes = CoInitialize(NULL);

    CEditDesktopName *p = new CEditDesktopName;
    p->DoModal();
	delete p;
	CoUninitialize();
    return 0;
}

	LRESULT CEditDesktopName::OnClickedButton_new(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{

	  HWND hwnd_DesktopName = GetDlgItem(IDC_EDIT_DESKTOP_NAME);
	  HWND hwnd_DesktopComment = GetDlgItem(IDC_EDIT_DESKTOP_COMMENTS);


	  char szActiveDesktopName[255];
	  char szActiveDesktopComment[255];


	  ::GetWindowText(hwnd_DesktopName,szActiveDesktopName,255); 
	  ::GetWindowText(hwnd_DesktopComment,szActiveDesktopComment,255); 


		EndDialog(0);
		return 0;
	}


void CEditDesktopName::Launch()
{
	if (::IsWindow(hWnd_EditDesktopName)){
		::SetFocus(hWnd_EditDesktopName);
	} else {
      DWORD dwThreadID;
      HANDLE h = CreateThread(NULL, 0, CEditDesktopNameProc, 0, 0, &dwThreadID);
	}
}


	LRESULT CEditDesktopName::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	  hWnd_EditDesktopName = m_hWnd;

      HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
	  this->SetIcon(hIcon);



	  HWND hwnd_DesktopName = GetDlgItem(IDC_EDIT_DESKTOP_NAME);
	  HWND hwnd_DesktopComment = GetDlgItem(IDC_EDIT_DESKTOP_COMMENTS);
	  HWND hwnd_DeleteButton = GetDlgItem(IDC_BUTTON_DELETE);


	  HWND hwnd_IDC_CHECK_AS_VISTUAL_DESKTOP =  GetDlgItem(IDC_CHECK_AS_VISTUAL_DESKTOP);


	  

	  if (strcmp(m_Desktop.szActiveDesktop,_T("Desktop")) == 0 ){
		  ::EnableWindow(hwnd_DeleteButton,FALSE);
		  ::EnableWindow(hwnd_IDC_CHECK_AS_VISTUAL_DESKTOP,FALSE);
	  } else {
		  ::EnableWindow(hwnd_DeleteButton,TRUE);
		  ::EnableWindow(hwnd_IDC_CHECK_AS_VISTUAL_DESKTOP,TRUE);
	  }

		return 1;  // Let the system set the focus
	}

void CEditDesktopName::Apply()
{
	  CMyDesktop m_Desktop;
	  HWND hwnd_DesktopName = GetDlgItem(IDC_EDIT_DESKTOP_NAME);
	  HWND hwnd_DesktopComment = GetDlgItem(IDC_EDIT_DESKTOP_COMMENTS);


	  char szActiveDesktopName[255];
	  char szActiveDesktopComment[255];


	  ::GetWindowText(hwnd_DesktopName,szActiveDesktopName,255); 
	  ::GetWindowText(hwnd_DesktopComment,szActiveDesktopComment,255); 

	  m_Desktop.SetDesktopName( szActiveDesktopName,szActiveDesktopComment,m_Desktop.szActiveDesktop);


	  HWND hwnd_IDC_CHECK_AS_VISTUAL_DESKTOP =  GetDlgItem(IDC_CHECK_AS_VISTUAL_DESKTOP);


char keyName[255];
strcpy(keyName,"VD_");
strcat(keyName,m_Desktop.szActiveDesktop);
CRegisterSave mReg;

	  if (BST_CHECKED  == 	  SendMessage( 
  hwnd_IDC_CHECK_AS_VISTUAL_DESKTOP,        // handle to destination window 
  BM_GETCHECK,        // message to send
  NULL,    // highlight state
  NULL     // not used; must be zero
  )){

	m_Desktop.bAsVirtualDesktop = TRUE;




mReg.UserKeyStore(keyName,"Y",1,CRegisterSave::WRITE);
	  } else {
	m_Desktop.bAsVirtualDesktop = FALSE;
mReg.UserKeyStore(keyName,"N",1,CRegisterSave::WRITE);
	  }

}

	LRESULT CEditDesktopName::OnClickedButton_delete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CMyDesktop m_Desktop;
		m_Desktop.DeleteCurrentDestop();
		m_Desktop.RestoreStartMenu();
		EndDialog(wID);
		return 0;
	}

