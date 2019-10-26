// About25.h : Declaration of the CAbout25

#ifndef __ABOUT25_H_
#define __ABOUT25_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CAbout25
class CAbout25 : 
	public CAxDialogImpl<CAbout25>
{
public:
	static HWND hWnd_MyTooltip;
	static DWORD WINAPI CMyTooltipProc(void* pv);
	static void Launch();
public:
	void DrawBitmap(HDC hDC,long ID_Bitmap, long x,long y);
	CAbout25()
	{
	}

	~CAbout25()
	{
	}

	enum { IDD = IDD_ABOUT25 };

BEGIN_MSG_MAP(CAbout25)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	BOOL bTraining_on;
};

#endif //__ABOUT25_H_
