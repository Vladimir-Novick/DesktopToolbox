// About.cpp : Implementation of CAbout
#include "stdafx.h"
#include "About.h"
#include "NLisence.h"

/////////////////////////////////////////////////////////////////////////////
// CAbout 


LRESULT CAbout::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ShellExecute(NULL, "open", "http://www.desk4u.net", NULL, NULL, SW_SHOWNORMAL);

		EndDialog(0);
		
		return 0;
	}



	LRESULT CAbout::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
	    this->SetIcon(hIcon);
		::SetWindowText(this->m_hWnd,strWindowTitle);

HWND hwnd_OK = GetDlgItem(IDC_OK);
HWND hwnd_Text = GetDlgItem(IDC_TEXT_MESSAGE);
RECT rectBut ;
RECT rectButMain ;
::GetWindowRect(this->m_hWnd,&rectButMain);
::GetWindowRect(hwnd_OK,&rectBut);

	int Y = GetSystemMetrics(SM_CYSIZE)+(rectBut.bottom-rectBut.top)*2;
	Y+= bm.bmHeight;
                  ::SetWindowPos(this->m_hWnd, NULL, 
            0 ,
            0 ,
            bm.bmWidth+4 , Y, SWP_NOZORDER | SWP_NOMOVE) ;

::GetWindowRect(hwnd_OK,&rectBut);
                  ::SetWindowPos(hwnd_OK, NULL, 
            rectBut.left - rectButMain.left ,
            bm.bmHeight +5,
            0 , 0, SWP_NOZORDER | SWP_NOSIZE) ;

::GetWindowRect(hwnd_Text,&rectBut);
                  ::SetWindowPos(hwnd_Text, NULL, 
            rectBut.left - rectButMain.left,
            bm.bmHeight + 5 ,
            0 , 0, SWP_NOZORDER | SWP_NOSIZE) ;


				  ::SetWindowText(hwnd_Text,szTextMessage);


		return 1;  // Let the system set the focus
	}



CAbout::CAbout()
	{


           CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
	    delete pLicense;

		if (FlgRegister == 0) {
	      Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TRIAL_EXPIRED));
          strcpy(szTextMessage,"STOP: Please register My Desktop Toolbox application and try again.");

		}

		if (FlgRegister == 1) {
	      Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TITLE_purchase));
          strcpy(szTextMessage,"");
		}

		if (FlgRegister == 2) {
	      Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TRYING));
          strcpy(szTextMessage,"WARNING: It's time-limited version.");
		}

    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	}




	char *CAbout::strWindowTitle = {"About: MyDesktopToolbox"};

	LRESULT CAbout::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

      PAINTSTRUCT ps;

      BeginPaint( &ps );








    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(ps.hdc);
    // Select the bitmap into the mem DC.


	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);
   
    // Blt the bits.
    ::BitBlt(ps.hdc,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);

    ::DeleteDC(hdcMem); 

	      EndPaint( &ps );

		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
