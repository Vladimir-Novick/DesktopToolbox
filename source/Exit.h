// Exit.h : Declaration of the CExit

#ifndef __EXIT_H_
#define __EXIT_H_

#include "resource.h"       // main symbols
#include <atlhost.h>


/////////////////////////////////////////////////////////////////////////////
// CExit
class CExit : 
	public CAxDialogImpl<CExit>
{
public:
	static char* strWindowTitle ;
	BOOL GoHelp;
	BOOL boolReturnValue;
	
	HCURSOR standard_cursor ;
	HCURSOR  select_cursor;
	CExit()
	{
				GoHelp = FALSE;
	    standard_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_NORMAL));
		select_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_SELECT));
	}

	~CExit()
	{
	}

	enum { IDD = IDD_EXIT };

BEGIN_MSG_MAP(CExit)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_OK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_OK, BN_CLICKED, OnOK)
	COMMAND_HANDLER(IDC_BUTTON_CANCEL, BN_CLICKED, OnClickedButton_cancel)
	COMMAND_HANDLER(IDC_BUTTON_ORDERING, BN_CLICKED, OnClickedButton_ordering)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


    void DrawBitmap(HDC hDC, long ID_Bitmap, long x, long y);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnClickedButton_cancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		// TODO : Add Code for control notification handler.
		return 0;
	}

	
	LRESULT OnClickedButton_ordering(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		       ShellExecute(NULL, "open", "http://www.desk4u.net", NULL, NULL, SW_SHOWNORMAL);
		EndDialog(wID);

		return 0;
	}
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (GoHelp){
            ShellExecute(NULL, "open", "http://www.desk4u.net", NULL, NULL, SW_SHOWNORMAL);
			EndDialog(0);
		
		}

		return 0;
	}
};

#endif //__EXIT_H_
