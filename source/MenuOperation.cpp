// MenuOperation.cpp: implementation of the CMenuOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MenuOperation.h"
#include "toolbox.h"
#include "MyMenu.h"
#include "About25.h"

#include "ExitModal.h"
#include "AboutModal.h"


extern HWND g_ToolboxWindow;

CRITICAL_SECTION CMenuOperation::bActiveTracking_critical_section;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuOperation::CMenuOperation()
{

}



CMenuOperation::~CMenuOperation()
{

}

void CMenuOperation::Initialize()
{
           InitializeCriticalSection( &bActiveTracking_critical_section );

}

void CMenuOperation::setimenuhWnd(HWND hwnd){

	ENTER_CRITICAL_SECTION

    imenuhWnd= hwnd;

	LEAVE_CRITICAL_SECTION

}


int CMenuOperation::getActivButton(){

	int ret = activButton;

	return ret;
}


void CMenuOperation::setActivButton(int active){
	ENTER_CRITICAL_SECTION
	CMenuOperation::activButton = active;
	LEAVE_CRITICAL_SECTION
}

void CMenuOperation::ActivateMenu(int CurrentID,int x,int y,HWND mh){

	ENTER_CRITICAL_SECTION



	if (CurrentID >=0 ){

	if ( CMenuOperation::activButton != CurrentID ) {
	    LEAVE_CRITICAL_SECTION
    
		setActivButton(CurrentID);
	
		ENTER_CRITICAL_SECTION


			imenuX = x;
			imenuY = y;
	        threadDDReadWord = CreateThread(0, 0,(LPTHREAD_START_ROUTINE) ThreadFuncMenu,
                    LPVOID(CurrentID), 0, &threadIDReadWord);

	}
	}

	LEAVE_CRITICAL_SECTION

}





void CMenuOperation::DeActivateMenu(int CurrentID,bool bImmideatly){

	if (CurrentID <0)
		return;

	CloseAllMenu();


}

//-------------

int CMenuOperation::imenuX = {0};
int CMenuOperation::imenuY =  {0};

int CMenuOperation::activButton = -1;


void CMenuOperation::CloseAllMenu(){

	ENTER_CRITICAL_SECTION

		if (imenuhWnd != NULL){
			if (::IsWindow(CMenuOperation::imenuhWnd)) {
				::PostMessage(CMenuOperation::imenuhWnd,
				  WM_CANCELMODE,0,0);
				::PostMessage(CMenuOperation::imenuhWnd,
				  WM_CLOSE,0,0);
				  imenuhWnd = NULL;
			}
		}

		if (threadDDReadWord != NULL){
				DWORD dwExitCode   ;
			  TerminateThread(threadDDReadWord,dwExitCode);
//			  CloseHandle(threadDDReadWord);
			  threadDDReadWord = NULL;
		}





			bActiveTracking = FALSE;



	LEAVE_CRITICAL_SECTION
		setActivButton(-1);

}


 
			HANDLE CMenuOperation::threadDDReadWord = NULL;
			DWORD CMenuOperation::threadIDReadWord =0;
			HWND CMenuOperation::imenuhWnd = NULL;
			BOOL CMenuOperation::bActiveTracking = FALSE;

VOID CMenuOperation::ThreadFuncMenu(LPVOID intV){

	int ipoz = (int )intV;

			char strFolder[255];
			char strDesktopName[255];
	ENTER_CRITICAL_SECTION


			bActiveTracking = TRUE;

	LEAVE_CRITICAL_SECTION


 HRESULT hRes = CoInitialize(NULL);



		CMyMenu menu;

		switch (CMenuOperation::activButton){





		case 5:
			{
				
			HMENU t_m = menu.CreateMenu();

			menu.AddTitle(t_m,"My Tools"); 
		   menu.AddMyItemIcon(0,IDB_TOOLS_ON);
//		   menu.AddMenuFromDir(t_m,CMyMenu::szMyDesktopToolbarFolder);

			}
			break;


		case 4:
			{
				
			HMENU t_m = menu.CreateMenu();
			menu.AddTitle(t_m,"My Desktop Toolbox Favorites"); 
		   menu.AddMyItemIcon(0,IDB_WEB_LINK_ON);
//		   menu.AddMenuFromDir(t_m,CMyMenu::szMyDesktopFavorites);

			}
			break;
		case 2:
			{

		HMENU t_m = menu.CreateMenu();
			menu.AddTitle(t_m,"My Attached Documents"); 
		   menu.AddMyItemIcon(0,IDB_WEB_NOTE_ON);




		   break;
			}
		case 1:
		{




		menu.AttachMenu(IDR_MENU1);

		menu.AddMyItemIcon(1,IDB_HELP_B);
 
		menu.AddMyItemIcon(2,IDB_MENU_HELP);
		menu.AddMyItemIcon(3,IDB_MENU_ABOUT);
		menu.AddMyItemIcon(4,IDB_MENU_CONFIGURATION);


		menu.AddMyItemIcon(5,IDB_MENU_KEY);

		menu.AddMyItemIcon(6,IDB_EXIT_MY_DESKTOPTOOLBOX);

		


        menu.AddSubMenuMyItemIcon(2,1, IDB_RIGHT_LAYAUT);

        menu.AddSubMenuMyItemIcon(2,2, IDB_LEFT_LAYAUT);
        menu.AddSubMenuMyItemIcon(2,3, IDB_TOP_L);
        menu.AddSubMenuMyItemIcon(2,4, IDB_HIDE_BOX);
        menu.AddSubMenuMyItemIcon(2,5, IDB_SHOW_BOX);

		


		

		

		break;
		}

		}








		if (::IsMenu(menu.m_hMenu)){


	    ENTER_CRITICAL_SECTION

		int imenuXL =imenuX+3;
		int imenuYL = imenuY; 
		HWND imenuhWndL = imenuhWnd;
		
		
		
		LEAVE_CRITICAL_SECTION


		BOOL bRet = menu.TrackPopupMenu( 
			TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			imenuXL ,
			imenuYL, imenuhWndL,ipoz);

 
		if (bRet != 0 ){		
		MYITEM *current_pMyItem;



   MENUITEMINFO info;
    info.cbSize = sizeof(info);
        info.fMask = MIIM_DATA; 

    ::GetMenuItemInfo(menu.current_hMenu, bRet, TRUE, &info);

	current_pMyItem = (MYITEM *) info.dwItemData; 



if (current_pMyItem->iAction == ActionRunFile){
	ShellExecute(NULL, NULL, current_pMyItem->fileName,NULL,  NULL, SW_SHOWNORMAL);
} else {


if (strcmp(current_pMyItem->psz,_T("Desk4u.net on the web"))== 0){
		    ShellExecute(NULL, "open", "http://www.desk4u.net", NULL, NULL, SW_SHOWNORMAL);
}



if (strcmp(current_pMyItem->psz,_T("Hide"))== 0){
	::ShowWindow(g_ToolboxWindow,SW_HIDE);
}

if (strcmp(current_pMyItem->psz,_T("Show"))== 0){
	::ShowWindow(g_ToolboxWindow,SW_SHOW);
}

if (strcmp(current_pMyItem->psz,_T("Register Product Online ..."))== 0){
	        CAbout25::Launch();
}




	CRegisterSave pReg;

if (strcmp(current_pMyItem->psz,_T("Fit to Right"))==0){

			 pReg.UserKeyStore("DeskPosition","Right",5,CRegisterSave::WRITE);
			 ::SendMessage(g_ToolboxWindow,msgRestoreToolbox,0,0);
}

if (strcmp(current_pMyItem->psz,_T("Fit to Left"))==0){
			 pReg.UserKeyStore("DeskPosition","Left",4,CRegisterSave::WRITE);
			 ::SendMessage(g_ToolboxWindow,msgRestoreToolbox,0,0);
}

if (strcmp(current_pMyItem->psz,_T("Fit to Top"))==0){
			 pReg.UserKeyStore("DeskPosition","Top",3,CRegisterSave::WRITE);
 
			 ::SendMessage(g_ToolboxWindow,msgRestoreToolbox,0,0);
			 
}

if (strcmp(current_pMyItem->psz,_T("Exit"))==0){
		       CExitModal *pD = new CExitModal;
               pD->DoModal();//::GetDesktopWindow());
}



if (strcmp(current_pMyItem->psz,_T("About My Desktop Toolbox  "))==0){
	CAboutModal m_tAbout;
	m_tAbout.DoModal(); 
}




}
		setActivButton(-1);

		}

//	    ENTER_CRITICAL_SECTION

//		CloseHandle(threadDDReadWord);		
		
//		LEAVE_CRITICAL_SECTION



		}
		





CoUninitialize( );
	ENTER_CRITICAL_SECTION
		    bActiveTracking = FALSE;
			CMenuOperation::activButton = -1;

	LEAVE_CRITICAL_SECTION



}





bool CMenuOperation::isActive(){

	ENTER_CRITICAL_SECTION


   bool ret = CMenuOperation::bActiveTracking;

	LEAVE_CRITICAL_SECTION

		return ret;

}
