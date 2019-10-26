// MenuOperation.h: interface for the CMenuOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUOPERATION_H__7E28C60B_DE4E_4D92_B817_4E7DE3BD9829__INCLUDED_)
#define AFX_MENUOPERATION_H__7E28C60B_DE4E_4D92_B817_4E7DE3BD9829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ENTER_CRITICAL_SECTION EnterCriticalSection( &bActiveTracking_critical_section );
#define LEAVE_CRITICAL_SECTION LeaveCriticalSection( &bActiveTracking_critical_section );





class CMenuOperation  
{
private:
	CMenuOperation();
	static int activButton;
public:
	static void CMenuOperation::setimenuhWnd(HWND hwnd);
    static CRITICAL_SECTION bActiveTracking_critical_section;
	static void CloseAllMenu();
	static VOID ThreadFuncMenu(LPVOID);
	static void Initialize();
	virtual ~CMenuOperation();
	static void ActivateMenu(int CurrentID,int x,int y,HWND mh);
	static void DeActivateMenu(int CurrentID,bool bImmideatly);
	static HANDLE threadDDReadWord;
	static DWORD threadIDReadWord;
	static HWND imenuhWnd;
	static int imenuX;
	static int imenuY;
	static BOOL bActiveTracking;
	static int CMenuOperation::getActivButton();
	static void CMenuOperation::setActivButton(int ix);

	static bool isActive();
};

#endif // !defined(AFX_MENUOPERATION_H__7E28C60B_DE4E_4D92_B817_4E7DE3BD9829__INCLUDED_)
