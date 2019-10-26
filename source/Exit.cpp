// Exit.cpp : Implementation of CExit
#include "stdafx.h"
#include "Exit.h"
#include "RegisterSave.h"
#include "NLisence.h"
#include <Windowsx.h>


extern char strFileLink[MAX_PATH];

void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor);

	LRESULT CExit::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	boolReturnValue = FALSE;
    HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
	this->SetIcon(hIcon);
//
     RECT tRect;
	 ::SetWindowText(this->m_hWnd,strWindowTitle);

 	RECT rcParent;
          ::GetWindowRect(this->m_hWnd, &rcParent);

	 ::GetWindowRect(::GetDlgItem(this->m_hWnd,IDC_DELIMITER),&tRect);


		int itop = 2;



		int FlgRegister;
           CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
	    delete pLicense;


		if (FlgRegister==1){
			itop += (tRect.top-rcParent.top);
		}

			 HRGN rgn = CreateRoundRectRgn(2, itop,
				rcParent.right-rcParent.left-4, rcParent.bottom-rcParent.top-4, 15, 15);
			     SetWindowRgn(rgn, TRUE);


	
		return 1;  // Let the system set the focus
	}



	LRESULT CExit::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PAINTSTRUCT ps;
		::BeginPaint(m_hWnd,&ps);

	BITMAP bm;
		int FlgRegister;
           CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
	    delete pLicense;



		  HWND dw = GetDlgItem(IDC_TRYING);
		  HDC hdc = ::GetWindowDC(dw);

		HBITMAP hBmp;
		  
		if (FlgRegister == 0) {
	      hBmp = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TRIAL_EXPIRED));
		}

		if (FlgRegister == 1) {
	      hBmp = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TITLE_purchase));
		}

		if (FlgRegister == 2) {
	      hBmp = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TRYING));
		}		  
		  
    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(hdc);
    ::GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);

    // Select the bitmap into the mem DC.


	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, hBmp);
   
    // Blt the bits.
    ::BitBlt(hdc,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);

    ::DeleteDC(hdcMem); 		  
		  
		  ::DeleteObject(hBmp);

 	     ::ReleaseDC(dw,hdc);





		

		  ::EndPaint(m_hWnd,&ps);
		return 0;
	}


	char *CExit::strWindowTitle = {"MyDesktopToolbox - www.desk4u.net - ExitWindow"};

void CExit::DrawBitmap(HDC hDC, long ID_Bitmap, long x, long y)
{
	HBITMAP	  hBitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(ID_Bitmap));

	BITMAP bm;
    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(hDC);
    // Select the bitmap into the mem DC.
    ::GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, hBitmap);
   
    // Blt the bits.
    ::BitBlt(hDC,
             x, y,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);
    ::DeleteDC(hdcMem); 
	::DeleteObject(hBitmap);
}

LONG RegOpenKeyExM(
  HKEY hKey,         // handle to open key
  LPCTSTR lpSubKey,  // subkey name
  DWORD ulOptions,   // reserved
  REGSAM samDesired, // security access mask
  PHKEY phkResult    // handle to open key
);


extern HWND g_MainWindow;

LRESULT CExit::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		boolReturnValue = TRUE;

		 CRegisterSave mReg;

/*		 HWND thWnd_IDC_DELETE_FROM_STURTUP = ::GetDlgItem(this->m_hWnd,IDC_DELETE_FROM_STURTUP);

		 LRESULT rez = ::SendMessage(thWnd_IDC_DELETE_FROM_STURTUP, BM_GETCHECK, 0, 0);
 
         if ( rez == BST_CHECKED ){



			 	          DeleteFile(strFileLink); //



		 }
*/

 		return 0;
	}



	LRESULT CExit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		long X = GET_X_LPARAM(lParam); 
		long Y = GET_Y_LPARAM(lParam); 


	if (( X > 345) && (X < 436) 
	 &&  ( Y  > 77) && ( Y  < 119) ){
    
		GoHelp = TRUE;

		SetCursor(select_cursor); 

	} else {

		GoHelp = FALSE;
		SetCursor(standard_cursor); 


	}
	return 0;
	}


/////////////////////////////////////////////////////////////////////////////
// CExit
