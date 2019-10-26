// MainWindow.h : Declaration of the CMainWindow

#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "MDragTarget.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMainWindow
class CMainWindow : 
	public CAxDialogImpl<CMainWindow>
{

public:
	CMainWindow()
	{
	}

	~CMainWindow()
	{
	}

	enum { IDD = IDD_MAINWINDOW };

BEGIN_MSG_MAP(CMainWindow)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
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

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
};

#endif //__MAINWINDOW_H_
