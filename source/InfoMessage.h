// InfoMessage.h : Declaration of the CInfoMessage

#ifndef __INFOMESSAGE_H_
#define __INFOMESSAGE_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CInfoMessage
class CInfoMessage : 
	public CAxDialogImpl<CInfoMessage>
{
public:

	static char *strWindowTitle ;

	static HANDLE threadDDReadWord;
	static DWORD threadIDReadWord;

	static void ShowMessage(char *message);

    static CInfoMessage *pD ;

    static VOID ThreadFunc(LPVOID intV);

	CInfoMessage()
	{
	}

	~CInfoMessage()
	{
	}

	enum { IDD = IDD_INFOMESSAGE };

BEGIN_MSG_MAP(CInfoMessage)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
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
};

#endif //__INFOMESSAGE_H_
