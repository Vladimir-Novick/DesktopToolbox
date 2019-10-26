// ToolBox.h : Declaration of the CToolBox

#ifndef __TOOLBOX_H_
#define __TOOLBOX_H_

#include "resource.h"       // main symbols

#include <atlhost.h>
#include <Windowsx.h>
#include <Windows.h>
#include <commctrl.h>
#include "RegisterSave.h"
#include "MenuOperation.h"

// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This adgHANDLE_DLGMSG macro corrects the problem:
#define adgHANDLE_DLGMSG(hwnd, message, fn)                          \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))



#define TEST_TOOLBAR_HIDE  1
#define UM_DISPRESICONNOTIFY     (WM_USER + 100)

#define TOOLBAR_HIDE 2
#define TOOLBAR_SHOW 3


extern  UINT msgRestoreToolbox ;

typedef struct strButtonParam
{
    int ID_ShowButton;
    int ID_ShowButtonActive;
    int x;
    int y;
} pButtonParam;




/////////////////////////////////////////////////////////////////////////////
// CToolBox
class CToolBox : 
	public CAxDialogImpl<CToolBox>
{
public:
	static char* strMyDesktopTollboxMainWindow;
private:
	static VOID CALLBACK
   CToolBox::TrackMouseTimerProc(HWND hWnd,UINT uMsg,UINT idEvent,DWORD dwTime) ;


	static BOOL  CheckProcessWindow();
	BOOL bEditNameFlag;
	void DrawTitle(HDC hDC,const char *textTitle,int x,int y,COLORREF crText);
	int CurrentMenuID ;
	strButtonParam dButton[10];
	void showButtonPlus(int pIShow,int pIShowActive,int x,int y);
	LPDROPTARGET pIDropTarget;
	HIMAGELIST hImageList;
	int iMaxButton;
	BOOL dwn;
	int bmWidth ; 
	int bmHeight;
	UINT CurrentScreenID;
	int dx;
	int dy;
	int iCurrentButton;
	HCURSOR standard_cursor ;
	HCURSOR  select_cursor;
	void SetWorkWindowRGN_RIGHT(void);
	void SetWorkWindowRGN_LEFT(void);
	void SetWorkWindowRGN_TOP(void);
public:
	void initPanel(void);
	LRESULT InitDesktopPanel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static int activButton;
	static HWND toolBarhWnd;
	void checkButtonList(int x,int y);
		LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	CToolBox();

	~CToolBox()
	{

	}

	enum { IDD = IDD_TOOLBOX };

BEGIN_MSG_MAP(CToolBox)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
	MESSAGE_HANDLER(WM_DELETEITEM, OnDeleteItem)
	MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
	MESSAGE_HANDLER(UM_DISPRESICONNOTIFY,onIconNotify);
    MESSAGE_HANDLER(msgRestoreToolbox,InitDesktopPanel);
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




	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);



	LRESULT  OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	
	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam == FALSE ){
			ShowWindow(SW_SHOW);
		}
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

	LRESULT OnDeleteItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
	LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT onIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
  switch (lParam) {


	        case WM_LBUTTONUP:  // The menu was cancelled
		  {
			  
			  POINT pt;
			  ::GetCursorPos(&pt);
			  RECT r;
			  ::GetWindowRect(this->m_hWnd,&r);
			  CMenuOperation::ActivateMenu(3,pt.x , pt.y, this->m_hWnd);
			  break;
		  }

	        case WM_RBUTTONUP:  // The menu was cancelled
		  {

			  POINT pt;
			  ::GetCursorPos(&pt);
			  CMenuOperation::ActivateMenu(1,pt.x , pt.y, this->m_hWnd);

			  break;
		  }


  }
		return 0;
	}

	LRESULT OnQueryEndSession(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


};

#endif //__TOOLBOX_H_
