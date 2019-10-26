// EditDesktopName.h : Declaration of the CEditDesktopName

#ifndef __EDITDESKTOPNAME_H_
#define __EDITDESKTOPNAME_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CEditDesktopName
class CEditDesktopName : 
	public CAxDialogImpl<CEditDesktopName>
{
public:
	static HWND hWnd_EditDesktopName;
	static DWORD WINAPI CEditDesktopName::CEditDesktopNameProc(void* pv);
public:
	void Apply(void);
	static void Launch();
	CEditDesktopName()
	{
	}

	~CEditDesktopName()
	{
	}

	enum { IDD = IDD_EDITDESKTOPNAME };

BEGIN_MSG_MAP(CEditDesktopName)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_BUTTON_APPLY, BN_CLICKED, OnClickedButton_apply)
	COMMAND_HANDLER(IDC_BUTTON_NEW, BN_CLICKED, OnClickedButton_new)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_HANDLER(IDC_BUTTON_DELETE, BN_CLICKED, OnClickedButton_delete)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);



	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{


		Apply();

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnClickedButton_apply(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		Apply();
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedButton_new(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);


	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
				EndDialog(0);
		return 0;
	}

	LRESULT OnClickedButton_delete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

};

#endif //__EDITDESKTOPNAME_H_
