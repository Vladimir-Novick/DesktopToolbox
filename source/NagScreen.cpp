// NagScreen.cpp : Implementation of CNagScreen
#include "stdafx.h"
#include "NagScreen.h"

/////////////////////////////////////////////////////////////////////////////
// CNagScreen


LRESULT CNagScreen::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{



		 RECT rcScreen;
         SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);

	BITMAP bm;
	HBITMAP Bitmap;
	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_NAG_SCREEN));


    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);


   
    // Blt the bits.

	bmWidth = bm.bmWidth ; 
	bmHeight = bm.bmHeight;


         SetWindowPos(HWND_TOPMOST, 
            0 ,
            0 ,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);




         SetWindowPos(HWND_TOPMOST, 
            
            (rcScreen.right- bm.bmWidth)/2 ,
			0,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);








	::DeleteObject(Bitmap);

	POINT lpptS[] = { 0,0,20,20,380,20,400,0,0,0};

	 HRGN rgn4 = CreatePolygonRgn(lpptS,5, ALTERNATE);



 HRGN rgnE = CreateRoundRectRgn(
  9,      // x-coordinate of upper-left corner
  16,       // y-coordinate of upper-left corner
  26,     // x-coordinate of lower-right corner
  33,    // y-coordinate of lower-right corner
  16,  // height of ellipse
  16  // width of ellipse
);

 HRGN rgnE2 = CreateRoundRectRgn(
  41,      // x-coordinate of upper-left corner
  21,       // y-coordinate of upper-left corner
  367,     // x-coordinate of lower-right corner
  35,    // y-coordinate of lower-right corner
  16,  // height of ellipse
  16  // width of ellipse
);



  
CombineRgn(rgnE,rgn4,rgnE,RGN_OR);
CombineRgn(rgnE,rgnE2,rgnE,RGN_OR);

		    int tmp = SetWindowRgn(rgnE, TRUE);


		return 1;  // Let the system set the focus
	}



HWND CNagScreen::hWnd_MyTooltip = NULL;
HWND CNagScreen::parenthWnd = NULL;


DWORD WINAPI CNagScreen::CMyTooltipProc(void* pv)
{
	    HRESULT hRes = CoInitialize(NULL);
    CNagScreen *p = new CNagScreen;
    p->DoModal(parenthWnd);
	delete p;
    CoUninitialize( );
    return 0;
}


void CNagScreen::Launch(HWND phWnd)
{
	if (::IsWindow(hWnd_MyTooltip)){
		::ShowWindow(hWnd_MyTooltip,SW_SHOW);
	} else {
      DWORD dwThreadID;
	  parenthWnd = phWnd;
      HANDLE h = CreateThread(NULL, 0, CMyTooltipProc, 0, 0, &dwThreadID);
	}
}