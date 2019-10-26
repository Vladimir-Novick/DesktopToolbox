// MyTooltip.h : Declaration of the CMyTooltip

#ifndef __MyTooltip_H_
#define __MyTooltip_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CMyTooltip
class CMyTooltip : 
	public CAxDialogImpl<CMyTooltip>
{
public:
	static HWND hWnd_MyTooltip;
	static DWORD WINAPI CMyTooltip::CMyTooltipProc(void* pv);
public:

	static void Launch();
	CMyTooltip()
	{
	}

	~CMyTooltip()
	{
	}

	enum { IDD = IDD_MyTooltip };

BEGIN_MSG_MAP(CMyTooltip)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
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


	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
				EndDialog(0);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

};

#endif //__MyTooltip_H_
