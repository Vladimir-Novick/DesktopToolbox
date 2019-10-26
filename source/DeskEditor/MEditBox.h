#ifndef __CMEditBox_H_
#define __CMEditBox_H_
#include "commctrl.h"
#include "resource.h"       // main symbols
//#include <atlwin.h>
#undef SubclassWindow 
#define  WM_SAVE_TREE WM_USER+202



class CMEditBox: public CWindowImpl< CMEditBox >
{
public:
    HWND m1_hWnd;
	HFONT fontText;
	HFONT OldfontText;
    LOGFONT lf;
	HTREEITEM m_EditItem;
	HWND	h_tree;
	HWND	h_MainWindow;

  DECLARE_WND_SUPERCLASS(NULL, _T("EDIT") )

   BEGIN_MSG_MAP( CMEditBox )
   MESSAGE_HANDLER(WM_CTLCOLOREDIT,OnCtlColorEdit)


     DEFAULT_REFLECTION_HANDLER()
   

MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
   END_MSG_MAP()


UINT m_DragDropFormat;
   void DestroyControl(){
   	   this->SetFont(OldfontText) ;
	   DeleteObject(fontText);

   }
void AttacmentControl(HWND thwnd)
{
	SubclassWindow (thwnd);
       m1_hWnd = thwnd;
		m_EditItem = NULL;

       memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	   HDC phDc = ::GetWindowDC(thwnd);
       lf.lfHeight =  -MulDiv(10, GetDeviceCaps(phDc, LOGPIXELSY), 72);
	   ::ReleaseDC(m1_hWnd,phDc);


	     lf.lfCharSet=DEFAULT_CHARSET;
         strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
          fontText = CreateFontIndirect (&lf);  




       OldfontText = (HFONT)this->GetFont();
	   this->SetFont(fontText);
	   DeleteObject(OldfontText);


//	m_DragDropFormat = CF_TEXT;
	
}




LRESULT OnCtlColorEdit(UINT uMsg, WPARAM 
		wParam, LPARAM lParam, BOOL& 
		bHandled)
{
//		::SetTextColor((HDC)wParam, 
//			TranslateColor(m_clrForeColor));
//		::SetBkColor((HDC)wParam, 
//			TranslateColor(m_clrBackColor));
//		if(m_hbrushEdit != NULL)
//			return (LRESULT)m_hbrushEdit;
//else
			return (LRESULT)::GetStockObject(
				WHITE_BRUSH);
}



	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ShowWindow(SW_HIDE);

		if (m_EditItem != NULL){


	
	    TVITEM tvi_Sourse;


		char strTemp[255];
				char strTempOld[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = m_EditItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 

		strcpy(strTempOld,strTemp);
//-----
		::GetWindowText(m1_hWnd,strTemp,250);

		if (strcmp(strTempOld,strTemp) != 0 ){
		::PostMessage(h_MainWindow,WM_SAVE_TREE, 
                0, 0);
           TreeView_SetItem(h_tree, &tvi_Sourse); 
		}
		}



		m_EditItem = NULL;
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
}; // 


#endif

