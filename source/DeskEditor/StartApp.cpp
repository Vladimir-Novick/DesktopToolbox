// StartApp.cpp: implementation of the StartApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "commctrl.h"
#include "DeskEditor1.h"
#include "windowsx.h"
#include "DeskEditor1.h"
#include "StartApp.h"
//#include "commctrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StartApp::StartApp()
{

}

StartApp::~StartApp()
{

}




HWND StartApp::Run()
{
	CDeskEditor *pD; 
       pD = new CDeskEditor;
       pD->DoModal(::GetDesktopWindow());
return pD->m_hWnd ;
}

