// MyTooltip.cpp : Implementation of CMyTooltip
#include "stdafx.h"
#include "MyTooltip.h"
//#include "MyDesktop.h"


/////////////////////////////////////////////////////////////////////////////
// CMyTooltip

HWND CMyTooltip::hWnd_MyTooltip;


DWORD WINAPI CMyTooltip::CMyTooltipProc(void* pv)
{
	 HRESULT hRes = CoInitialize(NULL);
    CMyTooltip *p = new CMyTooltip;
    p->DoModal();
	delete p;
	CoUninitialize( );
    return 0;
}


void CMyTooltip::Launch()
{
	if (::IsWindow(hWnd_MyTooltip)){
		::ShowWindow(hWnd_MyTooltip,SW_SHOW);
	} else {
      DWORD dwThreadID;
      HANDLE h = CreateThread(NULL, 0, CMyTooltipProc, 0, 0, &dwThreadID);
	}
}


	LRESULT CMyTooltip::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	  hWnd_MyTooltip = m_hWnd;
		return 1;  // Let the system set the focus
	}


