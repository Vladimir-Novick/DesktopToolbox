// ShareWareMessage.h : Declaration of the CShareWareMessage

#ifndef __SHAREWAREMESSAGE_H_
#define __SHAREWAREMESSAGE_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <Windowsx.h>

/////////////////////////////////////////////////////////////////////////////
// CShareWareMessage
class CShareWareMessage : 
	public CAxDialogImpl<CShareWareMessage>
{
public:
	CShareWareMessage()
	{
		GoHelp=FALSE;
		select_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_SELECT));

		standard_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_NORMAL));
	}

	~CShareWareMessage()
	{
	}

	enum { IDD = IDD_SHAREWAREMESSAGE };

BEGIN_MSG_MAP(CShareWareMessage)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	    HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
	    this->SetIcon(hIcon);

		return 1;  // Let the system set the focus
	}

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
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	    EndDialog(0);
		return 0;
	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (GoHelp){
            ShellExecute(NULL, "open", "http://www.desk4u,net", NULL, NULL, SW_SHOWNORMAL);
			EndDialog(0);
		
		}
		return 0;
	}
	BOOL GoHelp;
	HCURSOR  select_cursor;
	HCURSOR standard_cursor ;
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		long X = GET_X_LPARAM(lParam); 
		long Y = GET_Y_LPARAM(lParam); 
	if (( X > 357) && (X < 436) 
	 &&  ( Y  > 94) && ( Y  < 119) ){
    
		GoHelp = TRUE;

		SetCursor(select_cursor); 

	} else {

		GoHelp = FALSE;
		SetCursor(standard_cursor); 


	}
	return 0;
	}
};

#endif //__SHAREWAREMESSAGE_H_
