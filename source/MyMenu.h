// MyMenu.h: interface for the CMyMenu class.
//
//////////////////////////////////////////////////////////////////////



#if !defined(MYMENU_H)
#define MYMENU_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000






#include <atlbase.h>

#include "resource.h"

#include <atlapp.h>
//#include "MyDesktop.h"





//#if !defined MIIM_STRING
//#define MIIM_STRING 0x00000040
//#endif



extern TCHAR szPreviewClass[];

#define MIM_STYLE 16
#define MIM_APPLYTOSUBMENUS 0x80000000L 
#define MNS_AUTODISMISS 0x10000000


#define CITEMS 300

#define  CCH_MAXITEMTEXT  255

enum ActionType{ActionGoDesktop=2, ActionRunFile=3};

	 typedef struct _MYITEM 
    { 
		DWORD ID_Bitmap;
        char psz[255]; 
	    int   iAction;
		BOOL asFolder;
		char fileName[512];
		BOOL empty; // empty folder

    } MYITEM;             // structure for item font and string  


/*
typedef struct tagMENUINFO
{
    DWORD   cbSize;
    DWORD   fMask;
    DWORD   dwStyle;
    UINT    cyMax;
    HBRUSH  hbrBack;
    DWORD   dwContextHelpID;
    ULONG_PTR dwMenuData;
}   MENUINFO, FAR *LPMENUINFO;
typedef MENUINFO CONST FAR *LPCMENUINFO;
*/

class CMyMenu : 
	public CMenu,CWindowImpl<CMyMenu>
{

public:
	void AddSubMenuMyItemIcon(DWORD ID_Menu,DWORD ID_Menu_SUB, int ID_Bitmap);

	HMENU AddMyFolder(HMENU m_menu,char *strFolder, char *strDesktopName);
    void AddMyItemIcon(DWORD ID_Menu, int ID_Bitmap);

	    HMENU hmenu;             // handle to main menu 
		BOOL b_GoCommand;

	static char szMyDesktopToolbarFolder[255];
	static char szMyDesktopFavorites[255];

private:
 
    MYITEM *pmyitem;      // pointer to item's font and string        
    MYITEM myitem[CITEMS];   // array of MYITEMS               
           
    COLORREF crSelText;  // text color of selected item        
    COLORREF crSelBkgnd; // background color of selected item  
    COLORREF crText;            // text color of unselected item      
    COLORREF crBkgnd;           // background color unselected item   
    LPMEASUREITEMSTRUCT lpmis;  // pointer to item of data             
    LPDRAWITEMSTRUCT lpdis;     // pointer to item drawing data        
    HDC hdc;                    // handle to screen DC                
                  // menu-item text extents             
    WORD wCheckX;               // check-mark width                   
    int nTextX;                 // width of menu item                 
    int nTextY;                 // height of menu item                
    int i;                      // loop counter                       
    HFONT hfontOld;             // handle to old font                 
    BOOL fSelected ;     // menu-item selection flag  
	
	HWND MainhWnd;
	HMENU BaseMenu;
	int IpMenu;
	HFONT fontText;
	HFONT fontTextTitle;
	HFONT fontTextTitleMain;



public:


    DECLARE_WND_SUPERCLASS(NULL, GetWndClassName())
     BEGIN_MSG_MAP( CMyMenu )


    DEFAULT_REFLECTION_HANDLER()
   



    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_INITMENU, OnInitMenu)

    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER(WM_CANCELMODE, OnCancelMode)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_COMMAND, OnMenuCommand)
	MESSAGE_HANDLER(WM_ENTERMENULOOP, OnEnterMenuLoop)
	MESSAGE_HANDLER(WM_EXITMENULOOP, OnExitMenuLoop)
    MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)

   END_MSG_MAP()

	CMyMenu();
	virtual ~CMyMenu();
	void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor);



/*
	BEGIN_MSG_MAP(CMenuHelp)
		MESSAGE_HANDLER(WM_ENTERMENULOOP, OnEnterMenuLoop)
		MESSAGE_HANDLER(WM_EXITMENULOOP, OnExitMenuLoop)
		MESSAGE_HANDLER(WM_MENUSELECT, OnMenuSelect)
		MESSAGE_HANDLER(WM_INITMENU, OnInitMenu)
		MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
		MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
	END_MSG_MAP()
*/

	LRESULT OnEnterMenuLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
			DefWindowProc( uMsg, wParam, lParam );
		return 0;
	}

	LRESULT OnExitMenuLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
			DefWindowProc( uMsg, wParam, lParam );
		return 0;
	}

	LRESULT OnMenuSelect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	DefWindowProc( uMsg, wParam, lParam );
		return 0;
	}
	
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );
	return 0;
}

private:
		VOID AttachBaseWnd(HWND hWnd);

void DeleteAllMemo(HMENU hmenu);



void MyModifyMenu(HMENU hmenu);
char *GetMenuItemText(HMENU hmenu,int ID);





public:
	HMENU current_hMenu;

LRESULT OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);




	void AddMyItem(HMENU m_menu,char *strFolder,char *strDesktopName,int iActionType);

	void Blur(HDC hDC,RECT rect);
	void AddTitle(HMENU m_menu,char *strTitle);
	VOID AddMenuFromDir(HMENU m_menu,char *strFolder);
	HMENU CreateMenu(VOID);

		VOID AttachMenu(HMENU hm);
			VOID AttachMenu(int m_IDR_MENU1);




	BOOL TrackPopupMenu(UINT nFlags, int x, int y, HWND i1,int indexMenu, LPCRECT lpRect = NULL );




private:

	void DrawColorLine(HDC hDC,COLORREF iColor,int xL,int yL,int xR,int yR);

	VOID MyDrawGradient(HDC hDC,RECT rect,COLORREF t_color,COLORREF b_color,BOOL orientation){


int startR = GetRValue(t_color);
int startG = GetGValue(t_color);
int startB = GetBValue(t_color);

int startR1 ;
int startG1 ;
int startB1 ;
int start_p,end_p;

RECT rect1;


if (orientation){
rect1.left = rect.left; 
rect1.right = rect.right;
start_p= rect.top;
end_p = rect.bottom ;
} else {
rect1.top = rect.top; 
rect1.bottom  = rect.bottom;
start_p=rect.left; 
end_p = rect.right ;
}


double delta_R = ((double)(GetRValue(b_color) - startR  )) / (rect.bottom - rect.top); 
double delta_G = ((double)(GetGValue(b_color) - startG  )) / (rect.bottom - rect.top); 
double delta_B = ((double)(GetBValue(b_color) - startB  )) / (rect.bottom - rect.top); 

COLORREF startBG = t_color;
int kp = 0;

for ( int ip = start_p;ip <= end_p;ip++){ 
	

startR1 = (int)(startR + (delta_R*kp));
startG1 = (int)(startG + (delta_G*kp));
startB1 = (int)(startB + (delta_B*kp));

	HBRUSH hbr1 = CreateSolidBrush(
  RGB(startR1,startG1,startB1)  // brush color value
);



	kp++;


if (orientation){
rect1.top = ip; 
rect1.bottom  = ip+1;
} else {
rect1.left = ip; 
rect1.right  = ip+1;
}

    ::FillRect(hDC, &rect1, hbr1 );
 
     DeleteObject(hbr1);

}

	}

	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnInitMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

//       act_hWnd = GetForegroundWindow();

		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return DefWindowProc(uMsg, wParam, lParam);
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


	DeleteObject(fontText);
	DeleteObject(fontTextTitle);
	DeleteObject(fontTextTitleMain);


		MainhWnd = NULL;
		
		if (IsWindow()){
	      UnsubclassWindow();
		}



/*	if (::IsMenu(hmenu)){
	::DestroyMenu(hmenu);
	}

	if (::IsMenu(BaseMenu)){
	::DestroyMenu(BaseMenu); 
	}

	if (IsMenu()){
	 DestroyMenu(); 
	}
*/
		return DefWindowProc(uMsg, wParam, lParam);
	}


	LRESULT OnCancelMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return DefWindowProc(uMsg, wParam, lParam);
	}
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return DefWindowProc(uMsg, wParam, lParam);
	}


};

#endif // !defined(AFX_MYMENU_H__0E62A67C_CDC2_490A_9BEC_EA46B3DBDCD6__INCLUDED_)
