// NagScreen.h : Declaration of the CNagScreen

#ifndef __NAGSCREEN_H_
#define __NAGSCREEN_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CNagScreen
class CNagScreen : 
	public CAxDialogImpl<CNagScreen>
{
public:
	CNagScreen()
	{
	}

	~CNagScreen()
	{
	}

	enum { IDD = IDD_NAGSCREEN };

BEGIN_MSG_MAP(CNagScreen)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

static HWND hWnd_MyTooltip;
static DWORD WINAPI CMyTooltipProc(void* pv);
static void Launch(HWND phWnd);

	int bmWidth  ; 
	int bmHeight ;
static HWND parenthWnd;


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      PAINTSTRUCT ps;

      BeginPaint( &ps );

HDC hDC = GetDC();

	BITMAP bm;
	HBITMAP Bitmap;
	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_NAG_SCREEN));
    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(ps.hdc);
    // Select the bitmap into the mem DC.
    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);
   
    // Blt the bits.
    ::BitBlt(ps.hdc,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);
	::DeleteObject(Bitmap);
    ::DeleteDC(hdcMem); 

ReleaseDC(hDC);

      EndPaint( &ps );
	  return 0;
	}
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ShellExecute(NULL, "open", "http://www.mydesktoptoolbox.com/registration_process.html", NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		hWnd_MyTooltip = NULL;
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		EndDialog(0);
		return 0;
	}
};

#endif //__NAGSCREEN_H_
