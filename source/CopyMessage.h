// CopyMessage.h : Declaration of the CCopyMessage

#ifndef __CopyMessage_H_
#define __CopyMessage_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CCopyMessage
class CCopyMessage: 
	public CAxDialogImpl<CCopyMessage>
{
public:
    static void copyFolder(const char *szDesc1, const char *szFolder);
	static DWORD WINAPI CMyTooltipProc(void* pv);
	static HANDLE  Launch(const char *szDescL, const char *szFolderL);
    static DWORD WINAPI CopyProcedure(void* pv);
    static char gbl_szDesc[512];
    static char gbl_szFolder[512];
	static char gbl_szActiveDesktop[512];
	static char szBasePeronalFolderName[512];
	static char gbl_szDestDesktopName[512];

	static HWND Win_hWnd;
	BITMAP bm;
	HBITMAP Bitmap;
	char szTextMessage[255];
	int FlgRegister;
public:
	static void chekError(char *t,char *t2);
	static void ShowMessage(const char *szFrom, const char *szTo);
		CCopyMessage();

	~CCopyMessage()
	{
	::DeleteObject(Bitmap);
	}

	enum { IDD = IDD_CopyMessage };

BEGIN_MSG_MAP(CCopyMessage)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	COMMAND_HANDLER(IDC_OK, BN_CLICKED, OnClickedOk)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
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

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClickedOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(0);
		return 0;
	}
};

#endif //__CopyMessage_H_
