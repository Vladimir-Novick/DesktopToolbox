// DeskEditor1.cpp : Implementation of CDeskEditor
#include "stdafx.h"
#include "CAbout.h"
#include "commctrl.h"
#include "..\\RegisterSave.h"
#include "DeskEditor1.h"
#include <stdio.h>
#include "windowsx.h"


#define SZ_SPLASH "My Desktop Toolbox v3.2"
CDeskEditor *Main_WindowOBJ;

	LRESULT CDeskEditor::OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
			HTREEITEM h_item = NULL ;
	TVHITTESTINFO tv_ht ;
	TVITEM tv ;
	ZeroMemory(&tv, sizeof(TVITEM)) ;
        ZeroMemory(&tv_ht, sizeof(TVHITTESTINFO)) ;
		BOOL yesCursor = FALSE;

	
	if(m_bDragging)
	{
	   ImageList_DragLeave(NULL) ;
	   ImageList_EndDrag() ;
	   ReleaseCapture() ;
	   //determin if we let up on an item
	   GetCursorPos(&(tv_ht.pt)) ;
	   ::ScreenToClient(h_tree, &(tv_ht.pt)) ;
           tv_ht.flags = TVHT_ONITEM ;
//	   ShowCursor(TRUE) ;
		   if (SetCursor(StandardCursor) == YesCursor ){
			yesCursor = TRUE;
		   }
	   DestroyCursor(NoCursor);

	   m_bDragging = FALSE ;
	   ImageList_Destroy(m_pImageList);

	   if(yesCursor) 
	   {
			HTREEITEM pNewTarget = MoveTree(m_TargetItem,m_DropItem);
//		    TreeView_DeleteItem(h_tree,m_DropItem);
			TreeView_SelectItem(h_tree,pNewTarget);
			TestFolderIcon(pNewTarget);
			              SaveTreeToFile(lpCommand);
	   }
	   TreeView_SelectDropTarget(h_tree,NULL);
	} else {
		DWORD dx = GET_X_LPARAM(lParam); 
        DWORD dy = GET_Y_LPARAM(lParam); 
		if ((dx < 85 ) && (dy < 50 )){  
		ShellExecute(NULL, "open", "http://www.mydesktoptoolbox.com", NULL, NULL, SW_SHOWNORMAL);	
		}
	}

		return 0;
	}


	LRESULT CDeskEditor::OnBegindragTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
//
//  HWND hwndTV, LPNMTREEVIEW lpnmtv
//

	HWND hwndTV = GetDlgItem(IDC_TREE_CTRL);
	h_tree = hwndTV;
    

	 LPNMTREEVIEW lpnmtv = (NMTREEVIEW *) pnmh; 
 

//	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pnmh;

	//
	// Do nothing if the user is attempting to drag a top-level item.
	//
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
//	if (TreeView_GetParent(hwndTV,hItem) == NULL)
//		return FALSE;

	m_DropItem = hItem;
	m_CurrentItem = m_DropItem;
	GetItemAttr(m_DropItem,NULL,NULL,m_DragItemIcon);
	if (m_CurrentItem != NULL ){
       MSelect(m_CurrentItem);
	}

	//
	// Create a drag image. If the assertion fails, you probably forgot
	// to assign an image list to the control with SetImageList. Create-
	// DragImage will not work if the control hasn't been assigned an
	// image list!
	//
	m_pImageList = TreeView_CreateDragImage (hwndTV,hItem);
   

	if (m_pImageList != NULL) { // Just to be sure
    ImageList_BeginDrag(m_pImageList, 0, 0, 0) ;
		//
		// Compute the coordinates of the "hot spot"--the location of the
		// cursor relative to the upper left corner of the item rectangle.
		//
		RECT  rect;
		TreeView_GetItemRect(hwndTV,hItem, &rect, TRUE);


   //hide the cursor
   StandardCursor = GetCursor();
    NoCursor = LoadCursor(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDC_CURSOR_NO_DROP_1)); 
	YesCursor = StandardCursor;

//   ShowCursor(FALSE) ;
   //capture the mouse
   ::SetCapture(::GetParent(hwndTV)) ;
   //set global flag to indicate we are in the middle of a drag operation
   POINT point;
	   point.x = rect.left;
      point.y = rect.top;
	  ::ClientToScreen(hwndTV, &point) ;
   //paint our drag image and lock the screen.
   ImageList_DragEnter(NULL, point.x, point.y) ;
   
   m_bDragging = TRUE;
   m_bDragFolder = TestFolder(m_DropItem);
	}
		return 0;
	}




	LRESULT CDeskEditor::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

 
   TVHITTESTINFO tvht;  // hit test information 
	
      
   POINT pnt ;

      HTREEITEM h_item_find = NULL ;

   HTREEITEM h_item = NULL ;
   	HWND hwndTV = GetDlgItem(IDC_TREE_CTRL);
    long yCur = GET_Y_LPARAM(lParam) ;
   long xCur = GET_X_LPARAM(lParam) ;
   pnt.x = xCur ;
   pnt.y = yCur;
   if(m_bDragging)
   {
      //unlock window and allow updates to occur
      ImageList_DragLeave(NULL) ;
      ::ClientToScreen(hwndTV, &pnt) ;
      //check with the tree control to see if we are on an item
      TVHITTESTINFO tv_ht ;
      ZeroMemory(&tv_ht, sizeof(TVHITTESTINFO)) ;
      tv_ht.flags = TVHT_ONITEM ;
      tv_ht.pt.x = pnt.x ;
      tv_ht.pt.y = pnt.y - 50 ;
      ::ScreenToClient(hwndTV, &(tv_ht.pt)) ;
      h_item = (HTREEITEM)SendMessage(hwndTV, TVM_HITTEST, 0, (LPARAM)&tv_ht) ;

	  
	  
	  	     SendMessage(hwndTV, TVM_SELECTITEM, TVGN_DROPHILITE, (LPARAM)h_item) ;
	  
	  if (h_item == m_DropItem ) {
					h_item = NULL;
	  }
      if(h_item)
      {  //if we had a hit, then drop highlite the item
		  if (m_bDragFolder == TRUE ){
			HTREEITEM tar = TreeView_GetParent(hwndTV,h_item);
			while(tar != NULL ) {
				if (tar == m_DropItem ){
					h_item = NULL;
					break;
				}
				tar = TreeView_GetParent(hwndTV,tar);
			}
		  } 
      }
	  if ( h_item != NULL ) {
		     m_TargetItem = h_item;
			 int iconType;
			 GetItemAttr(m_TargetItem,NULL,NULL,iconType);
			 if ((m_DragItemIcon == 4) || (m_DragItemIcon == 2) ){
			 if (!((iconType == 0) || (iconType == 1) )){
		     m_TargetItem = NULL;	
//	         MSelect(m_CurrentItem);
			 }
			 }


			 if ((m_DragItemIcon == 0) || (m_DragItemIcon == 1) ){
			 if (!((iconType == 0) || (iconType == 1) )){
		     m_TargetItem = NULL;	
//	         MSelect(m_CurrentItem);
			 }
			 }

	  }else {
		     m_TargetItem = NULL;	
//	         MSelect(m_CurrentItem);
	  }




      //paint the image in the new location
      ImageList_DragMove(pnt.x,pnt.y-50) ;
      //lock the screen again
      ImageList_DragEnter(NULL, pnt.x, pnt.y - 50) ;

        // Find out if the pointer is on the item. If it is, 
		// highlight the item as a drop target. 
        tvht.pt.x = xCur; 
        tvht.pt.y = yCur; 

		RECT rectTree;
		::GetWindowRect(h_tree,&rectTree);
		BOOL onTree = FALSE;



		if ((rectTree.left < pnt.x ) && (rectTree.right > pnt.x ) &&
			(rectTree.top  < pnt.y ) && (rectTree.bottom  > pnt.y )){
			onTree = TRUE;
		}

	  if (m_TargetItem){
			  SetCursor(YesCursor);
	  }else {
		  if ((onTree == TRUE ) && (h_item == NULL) && ((m_DragItemIcon >= 0) && (m_DragItemIcon <= 4) )){
			  SetCursor(YesCursor);
		  } else {
			  SetCursor(NoCursor);
		  }
	  }

//        if ((htiTarget = TreeView_HitTest(hwndTV, &tvht)) != NULL) { 
//            TreeView_SelectDropTarget(hwndTV, htiTarget); 
//       } 

   }

 
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}








	LRESULT CDeskEditor::OnItemexpandedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	HTREEITEM	hti;

	HWND thWnd = h_tree;
    

	 NMTREEVIEW * pnmtv = (NMTREEVIEW *) pnmh; 
 
       hti = (HTREEITEM)(pnmtv->itemNew).hItem; 

		TestFolderIcon(hti);
		TestChildFolderIcon(hti);

		return 0;
	}


	LRESULT CDeskEditor::OnDblclkTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
    HTREEITEM hCurrentFolder = TreeView_GetSelection(h_tree);

		int iconType;
	   GetItemAttr(hCurrentFolder,NULL,NULL,iconType);



	   if ((iconType>= 0) &&  (iconType<= 4) ) {
              PostMessage(WM_SHOW_EDIT_BOX, 
                SHOW_EDIT_BOX_MSG, 0);
		return 1;
	   } 
	   return 0;
	}


void CDeskEditor::GetItemAttr(HTREEITEM item,char *strName,char *strUrl,int &iconType){
	HTREEITEM hItem = item;
//-----

	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
		 m_EditTreeItem = hItem;
        char * ParStr = (LPSTR)tvi_Sourse.lParam;
		if (strName != NULL ){
		  strcpy(strName,strTemp);
		}
		if ( strUrl != NULL ){
		  strcpy(strUrl,ParStr);
		}
		iconType = tvi_Sourse.iSelectedImage;
//		::SetWindowText(hWndEditBoxURL,ParStr);
//		::SetWindowText(hWndEditBoxName,strTemp);
	}


LRESULT CDeskEditor::OnSelchangedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	 LPNMTREEVIEW lpnmtv = (NMTREEVIEW *) pnmh; 
 

//	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pnmh;

	//
	// Do nothing if the user is attempting to drag a top-level item.
	//
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
         TreeView_SelectDropTarget(h_tree,NULL);
         TreeView_SelectDropTarget(h_tree,pNMTreeView->itemNew.hItem);

//-----

	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
		 m_EditTreeItem = hItem;
        char * ParStr = (LPSTR)tvi_Sourse.lParam;
		::SetWindowText(hWndEditBoxURL,ParStr);
		::SetWindowText(hWndEditBoxName,strTemp);
//    HWND hWndEditBoxName;
// 	  HWND hWndEditBoxURL;
		// TODO : Add Code for control notification handler.
		return 0;
	}


	LRESULT CDeskEditor::OnChangeEdit_url(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (m_EditTreeItem != NULL){
	
	    TVITEM tvi_Sourse;


		char strTemp[255];
		char strTempName[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = m_EditTreeItem; 
        tvi_Sourse.pszText = strTempName; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
		strTemp[0]='\0';
		strTemp[249]='\0';
		::GetWindowText(hWndEditBoxURL,strTemp,250);
		 
		 free((void *)(tvi_Sourse.lParam));
		 int lenField = strlen(strTemp)+2;
         LPSTR newStr = (LPSTR)malloc(lenField);
		 strcpy(newStr,strTemp);
		 tvi_Sourse.lParam = (LPARAM) newStr;
        TreeView_SetItem(h_tree, &tvi_Sourse); 
		}
		return 0;
	}




LRESULT CDeskEditor::OnChangeEdit_name(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (m_EditTreeItem != NULL){

	
	    TVITEM tvi_Sourse;


		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = m_EditTreeItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
		::GetWindowText(hWndEditBoxName,strTemp,250);
        TreeView_SetItem(h_tree, &tvi_Sourse); 
		}
		// TODO : Add Code for control notification handler.
		return 0;
	}



VOID CDeskEditor::AddIconsToImageList(DWORD IDI_icon)
{

    HICON hicon;
    hicon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_icon)); 
	ImageList_AddIcon(hImageList, hicon); 
}

WNDPROC	gwpOrigProc;
BOOL ResizeFl = FALSE;

long FAR PASCAL  ResizerCompProc(
    HWND hwndDlg, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
 
    switch(uMsg) 
    { 
  
	case WM_LBUTTONDOWN :
		{
			ResizeFl = TRUE;
		      HCURSOR mCursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE( IDC_RESIZE_CUR));
		      SetCursor(mCursor);

		}
		break;

	case WM_LBUTTONUP:
			ResizeFl = FALSE;
			{
		      HCURSOR mCursor = LoadCursor(NULL, IDC_SIZEWE);
		      SetCursor(mCursor);


			}
		break;

	case WM_MOUSEMOVE  :
		{
			if (ResizeFl == TRUE ) {
				POINTS pxy = MAKEPOINTS(lParam);
				int NewPOz = pxy.x ;
				if (( NewPOz < - 6 ) || ( NewPOz > 6 )) {
				  Main_WindowOBJ->iPozDelim = Main_WindowOBJ->iPozDelim + NewPOz;
				  if ( Main_WindowOBJ->iPozDelim  < 15 ) {
					  Main_WindowOBJ->iPozDelim  = 15;
				  }

				  if ( Main_WindowOBJ->InnerWidth - 15 < Main_WindowOBJ->iPozDelim ){
					  Main_WindowOBJ->iPozDelim = Main_WindowOBJ->InnerWidth - 15;
				  }
				  Main_WindowOBJ->ResizeWindowPanel(); 
				}
			} else {
		      HCURSOR mCursor = LoadCursor(NULL, IDC_SIZEWE);
		      SetCursor(mCursor);
			}
		}
		break;

    case WM_DESTROY: 
            // Remove the subclass from the edit control. 
 //           SetWindowLong(hwndDelim, GWL_WNDPROC, 
 //               (LONG) wpOrigDelimProc); 
 //           // 
            // Continue the cleanup procedure. 
            // 
    break; 
    } 
 	return (CallWindowProc( (WNDPROC) gwpOrigProc, hwndDlg, uMsg,
                                   wParam, lParam));

} 



	LRESULT CDeskEditor::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


m_EditControl.AttacmentControl(GetDlgItem(IDC_EDIT_TREE_NAME));


	Main_WindowOBJ = this;
	m_TypeSave = Type_SAVE;

	HWND tmhWnd = GetDlgItem(IDC_TREE_CTRL);
	::SendMessage(tmhWnd,TVM_SETBKCOLOR, 0, RGB(205,210,211));

TreeView_SetTextColor(
    tmhWnd, 
    RGB(19,27,39)
); 



::SendMessage( 
  tmhWnd,              // handle to destination window 
  WM_SETFONT,               // message to send
  NULL,          // handle to font
  TRUE          // redraw option
);



	h_tree = tmhWnd;
	    HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_ICON_PERSONAL_LINK));
	this->SetIcon(hIcon);

        CRegisterSave *mReg = new CRegisterSave;


        iPozDelim = 184;

		mReg->UserKeyStore("Delimiter",iPozDelim,CRegisterSave::READ);


		RECT rect; 
        ::GetWindowRect(this->m_hWnd ,&rect);



		rect.top = 68;
		rect.left = 179;
		rect.bottom = 594;
		rect.right = 871;

		mReg->UserKeyStore("top",rect.top ,CRegisterSave::READ);
		mReg->UserKeyStore("left",rect.left  ,CRegisterSave::READ);
		mReg->UserKeyStore("bottom",rect.bottom  ,CRegisterSave::READ);
		mReg->UserKeyStore("right",rect.right   ,CRegisterSave::READ);




		delete mReg;


	::MoveWindow(this->m_hWnd ,rect.left  ,rect.top ,rect.right -rect.left ,rect.bottom - rect.top ,TRUE);


	    TreeView_SetImageList(
       tmhWnd,
       hImageList,
       TVSIL_NORMAL );	




/*    TreeView_InsertItem(
    tmhWnd,
    &pis
    );		
*/


	GetClientRect(&rect);
	InnerWidth = rect.right-rect.left;
	InnerHeight = rect.bottom - rect.top;
        ResizeWindowPanel();


		HWND hwndDelim=  GetDlgItem(  IDC_DELIMITER);

 

 gwpOrigProc = ( WNDPROC ) ::GetWindowLong(hwndDelim, GWL_WNDPROC); 
		


::SetWindowLong(hwndDelim, GWL_WNDPROC, 
               (LONG) ResizerCompProc); 


		SaveRestoreExpand(FALSE);
		GetAllTree();

		return DefWindowProc();  // Let the system set the focus
	}





	void CDeskEditor::GetAllTree(){
    h_tree = GetDlgItem(IDC_TREE_CTRL);
	HTREEITEM hCurrentFolder;
	HTREEITEM	hti;


LPSTR cmdL = GetCommandLine();


	strcpy(lpCommand,&cmdL[1]);

	


	for (int lp = strlen(lpCommand)-1; lp >=0; lp--){
	  lpCommand[lp]=0; 
	  if (lpCommand[lp-1]=='\\') break;
	  if (lpCommand[lp-1]==':') break;
	}

	strcat(lpCommand,"MyDesktopToolbox.ini");

LoadTreeFromFile(lpCommand);
if (TreeView_GetCount(h_tree)== 0){

				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertNewTopItem("Main Windows Desktop",0,4);
				TestFolderIcon(hti);
				MSelect(hti);
				m_CurrentItem = hti;
}
	}


	LRESULT CDeskEditor::OnRclickTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	char Buf[255];
	BOOL folder;
    h_tree = GetDlgItem(IDC_TREE_CTRL);
	HTREEITEM	hti;
	hti = NULL;
	hti = TreeView_GetDropHilight(h_tree);
    if (hti == NULL ){
		hti = TreeView_GetSelection(h_tree);
		  TreeView_SelectDropTarget(h_tree,hti);

	} else {
	  TreeView_SelectItem(h_tree,hti);
	}
	POINT pt;
	/*DWORD par =*/  GetItemID(hti,Buf,folder);

		hti = TreeView_GetSelection(h_tree);
		char strName[255];
		char strUrl[255];
		int iconType;
	GetItemAttr(hti,strName,strUrl,iconType);
		//=====
         HMENU hmenuMain = NULL;
           HMENU hmenuContext = NULL;
		   hmenuMain = LoadMenu(_Module.GetModuleInstance(), 
		      MAKEINTRESOURCE(IDR_MENU_POPUP_TREE));
			  GetCursorPos(&pt);



	   if ((iconType< 0) ||  (iconType >  4) ) {
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_EDITNAMEDBLCLICK,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	   }

			  switch(iconType){
			case 4:
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_DELETE,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );

				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_INSERTFOLDER,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_INSERTITEM,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );

				break;
			case 2:

				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_INSERTFOLDER,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_INSERTITEM,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );

				break;
			  }

			switch( folder )
			{
				// item
			case 0:
				EnableMenuItem(hmenuMain,ID_POPMENUTREE_EXPANDALL,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				EnableMenuItem(hmenuMain,ID_POPMENUTREE_COLLAPSED,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				break;
				// open
			case 1:
				if (!TestNoExpandAll(hti)){
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_EXPANDALL,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				}
				break;
				// close 
			case 2:
				if (TestNoChildren(hti)){
				   EnableMenuItem(hmenuMain,ID_POPMENUTREE_EXPANDALL,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				}
				EnableMenuItem(hmenuMain,ID_POPMENUTREE_COLLAPSED,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
				break;



			}


		   hmenuContext = GetSubMenu(hmenuMain, 0);

            UINT uMenuID = ::TrackPopupMenu(hmenuContext, 
            TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            pt.x, pt.y, 0, h_tree, NULL);
			DestroyMenu(hmenuContext);
			DestroyMenu(hmenuMain);
		  TreeView_SelectDropTarget(h_tree,NULL);
		  if (uMenuID){

			  CaseMenuPopup(uMenuID);
              SaveTreeToFile(lpCommand);
		  }

		return 0;
	}







HTREEITEM CDeskEditor::InsertCopy(HTREEITEM hSrc)
{
  HTREEITEM retNew =	InsertCopyTreeMain (hSrc);
	//
	if (TestFolder(hSrc))
	  	CopyChildren (retNew, hSrc);

	return retNew;
}


HTREEITEM CDeskEditor::MoveTree(HTREEITEM hDest, HTREEITEM hSrc)
{
  HTREEITEM retNew =	CopyTreeMain (hDest, hSrc);
		// If the item has subitems, copy them, too.
	//
	if (TestFolder(hSrc))
	  	CopyChildren (retNew, hSrc);


	TreeView_DeleteItem(h_tree,hSrc);
	return retNew;
}

	LRESULT CDeskEditor::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		    RECT rect; 
			::GetWindowRect(this->m_hWnd ,&rect);
		CRegisterSave *mReg= new CRegisterSave;
				mReg->UserKeyStore("Delimiter",iPozDelim,CRegisterSave::WRITE);
				mReg->UserKeyStore("top",rect.top ,CRegisterSave::WRITE);
				mReg->UserKeyStore("left",rect.left  ,CRegisterSave::WRITE);
				mReg->UserKeyStore("bottom",rect.bottom  ,CRegisterSave::WRITE);
				mReg->UserKeyStore("right",rect.right   ,CRegisterSave::WRITE);
				delete mReg;
        SaveRestoreExpand(TRUE);
		EndDialog(0);
   		return 1;
	}


HTREEITEM CDeskEditor::CopyTree(HTREEITEM hDest, HTREEITEM hSrc)
{
	    TVINSERTSTRUCT tvins; 	
	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hSrc; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
  	HWND hwndTV;
    TVITEM tvi; 

    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;
 
    tvi.pszText = strTemp; 
    tvi.cchTextMax = strlen(strTemp); 
 
    tvi.iImage = tvi_Sourse.iImage; 
    tvi.iSelectedImage = tvi_Sourse.iSelectedImage; 

	int intLenStr = strlen((LPSTR)tvi_Sourse.lParam)+2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,(LPSTR)tvi_Sourse.lParam);
    tvi.lParam = (LPARAM) ParStr; 


 
    tvins.item = tvi; 


//--------------------
//    insert into details 
//	
    if (TestFolder(hDest) == TRUE ) {
      tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
      tvins.hParent = hDest; 
	} else {
      tvins.hInsertAfter = hDest; 
      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
    }
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
//        hti = TreeView_GetParent(hwndTV, hPrev); 
//        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
//        tvi.hItem = hti; 
//        tvi.iImage = mi_nClose; 
//        tvi.iSelectedImage = mi_nClose; 
//        TreeView_SetItem(hwndTV, &tvi); 
	//
    return hPrev;

}


HTREEITEM CDeskEditor::InsertCopyTreeMain(HTREEITEM hSrc)
{
	    TVINSERTSTRUCT tvins; 	
	    TVITEM tvi_Sourse;
        HTREEITEM hDest=hSrc;		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hSrc; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
  	HWND hwndTV;
    TVITEM tvi; 

    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;
 
    tvi.pszText = strTemp; 
    tvi.cchTextMax = strlen(strTemp); 
 
    tvi.iImage = tvi_Sourse.iImage; 
    tvi.iSelectedImage = tvi_Sourse.iSelectedImage; 
 

	int intLenStr = strlen((LPSTR)tvi_Sourse.lParam)+2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,(LPSTR)tvi_Sourse.lParam);
    tvi.lParam = (LPARAM) ParStr; 


    tvins.item = tvi; 


      tvins.hInsertAfter = hDest; 
      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
//        hti = TreeView_GetParent(hwndTV, hPrev); 
//        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
//        tvi.hItem = hti; 
//        tvi.iImage = mi_nClose; 
//        tvi.iSelectedImage = mi_nClose; 
//        TreeView_SetItem(hwndTV, &tvi); 
	//
    return hPrev;

}


HTREEITEM CDeskEditor::CopyTreeMain(HTREEITEM hDest, HTREEITEM hSrc)
{
	    TVINSERTSTRUCT tvins; 	
	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hSrc; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
  	HWND hwndTV;
    TVITEM tvi; 

    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM;
 
    tvi.pszText = strTemp; 
    tvi.cchTextMax = strlen(strTemp); 
 
    tvi.iImage = tvi_Sourse.iImage; 
    tvi.iSelectedImage = tvi_Sourse.iSelectedImage; 
 


	int intLenStr = strlen((LPSTR)tvi_Sourse.lParam)+2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,(LPSTR)tvi_Sourse.lParam);
    tvi.lParam = (LPARAM) ParStr; 

 
    tvins.item = tvi; 


//--------------------
//    insert into details 
//	
    if (TestFolder(hDest) == TRUE ) {
		if (TestNoChildren(hDest)){
           tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
           tvins.hParent = hDest; 
		} else {
			if (TestNoExpaned(hDest)){
                tvins.hInsertAfter = hDest; 
                tvins.hParent = TreeView_GetParent(h_tree,hDest); 
			} else {
               tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
               tvins.hParent = hDest; 
			}
		}
	} else {
      tvins.hInsertAfter = hDest; 
      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
    }
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
//        hti = TreeView_GetParent(hwndTV, hPrev); 
//        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
//        tvi.hItem = hti; 
//        tvi.iImage = mi_nClose; 
//        tvi.iSelectedImage = mi_nClose; 
//        TreeView_SetItem(hwndTV, &tvi); 
	//
    return hPrev;

}





VOID CDeskEditor::CopyChildren(HTREEITEM hDest, HTREEITEM hSrc)
{
	//
	// Get the first subitem.
	//
	HTREEITEM hItem;
	HTREEITEM hItemNew;
	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hSrc);
	hItemBase = hItem;
	//
	// Do the same for other subitems of hSrc.
	//
	while (hItem != NULL) {
	   hItemNew = CopyTree(hDest, hItem);
		   if (TestFolder(hItem)){
	    	  CopyChildren (hItemNew, hItem);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
}

BOOL CDeskEditor::TestFolder(HTREEITEM hDest)
{
			return TRUE;
	    TVITEM tvi;
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.hItem = hDest; 
		BOOL ret = TreeView_GetItem(h_tree, &tvi); 
		if ((tvi.iImage == mi_nClose) || (tvi.iImage == mi_nOpen)){
			return TRUE;
		}
		return FALSE;
}





VOID CDeskEditor::ResizeWindowPanel()
{



	  HWND hwnd_IDC_LEFT = GetDlgItem(IDC_EDIT_CONTAINER);

	  HWND hwnd_IDC_DELIMITER = GetDlgItem(IDC_DELIMITER);	

	  DWORD wHightEdit = 0;
	  DWORD wHightUrl = 0;
	  DWORD wHightTree = InnerHeight;
	  DWORD wBorder = GetSystemMetrics(SM_CYBORDER);
 	  h_tree = GetDlgItem(IDC_TREE_CTRL);




	DWORD hTop = 50;
      
     RECT rect; 
     if (::GetWindowRect(hWndEditBoxName,&rect)){
		 wHightEdit = rect.bottom - rect.top  ;
		 wHightTree = wHightTree - wHightEdit - 2*wBorder ;
	 }

	 

  


	::MoveWindow(hwnd_IDC_LEFT,iPozDelim +  8*wBorder  ,hTop,InnerWidth- iPozDelim - 8*wBorder ,wHightTree - hTop,TRUE);
	::MoveWindow(h_tree,0,hTop,iPozDelim , InnerHeight - 2*wBorder  ,TRUE);    
   ::MoveWindow(hwnd_IDC_DELIMITER,iPozDelim+ 2*wBorder,hTop , 4*wBorder,InnerHeight - 2*wBorder - hTop  , TRUE);


PaintTop();

}


	LRESULT CDeskEditor::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


      PAINTSTRUCT ps;

      BeginPaint( &ps );


HDC hDC = GetDC();


	  DWORD wBorder = GetSystemMetrics(SM_CYBORDER);


	RECT rect;



	GetClientRect(&rect);


		rect.bottom = 50;





	BITMAP bm;
	HBITMAP Bitmap;
	HBITMAP bmMemOld;
	HDC hdcMem;
    hdcMem = ::CreateCompatibleDC(hDC);

	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TOP));
    // Create a memory DC.

    // Select the bitmap into the mem DC.
    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);

int iLeft = bm.bmWidth;
   

     ::BitBlt(hDC,
             0,0,bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             
             SRCCOPY);



 



    ::SelectObject(hdcMem, bmMemOld);
	::DeleteObject(Bitmap);
    ::DeleteDC(hdcMem); 
//




	  PaintTop();
SetBkMode(hDC, TRANSPARENT);

LOGFONT     lf;   

      ZeroMemory(&lf, sizeof(lf));
      lstrcpy(lf.lfFaceName, "Arial");

	  	  lf.lfWeight = FW_BOLD;



      lf.lfHeight =-MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72);

	  lf.lfItalic = TRUE; 
	   lf.lfQuality              =   DRAFT_QUALITY ;



		     HFONT hFont = CreateFontIndirect( &lf );
		     HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);

SetTextColor( hDC,RGB(208,213,221));
		     TextOut(hDC, 85,4, _T(SZ_SPLASH), lstrlen(SZ_SPLASH));



SetTextColor( hDC,RGB(12,67,94));
		     TextOut(hDC, 84,3, _T(SZ_SPLASH), lstrlen(SZ_SPLASH));

		     SelectObject(hDC, hOldFont);
			 DeleteObject(hFont); 


			 
			 ReleaseDC(hDC);



      EndPaint( &ps );


		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return DefWindowProc();
	}




VOID CDeskEditor::SaveRestoreExpand(BOOL SaveFlad)
{

}



VOID CDeskEditor::TestFolderIcon(HTREEITEM hti)
{
    TVITEM tvi; 
    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE ; 
        tvi.hItem = hti; 

		TreeView_GetItem(h_tree, &tvi); 


//
		if ((tvi.iSelectedImage == mi_nOpen) ||  
			(  tvi.iImage == mi_nClose)) {

		if (tvi.state & TVIS_EXPANDED){
			if (TestNoChildren(hti)){
                tvi.hItem = hti; 
                tvi.iImage = mi_nClose; 
                tvi.iSelectedImage = mi_nClose; 
			} else {
                tvi.hItem = hti; 
                tvi.iImage = mi_nOpen; 
                tvi.iSelectedImage = mi_nOpen; 
			}
		} else {
                tvi.hItem = hti; 
                tvi.iImage = mi_nClose; 
                tvi.iSelectedImage = mi_nClose; 
		}
		TreeView_SetItem(h_tree, &tvi); 
	}

}

void CDeskEditor::InsertTopLavel(LPSTR lpszItem,int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
   
    // Save the heading level in the item's application-defined 
    // data area. 


	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 


    tvi.iImage = mi_nClose; 
    tvi.iSelectedImage = mi_nClose; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 
 
    // Set the parent item based on the specified level. 
  
        tvins.hParent = TVI_ROOT; 
   
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
		SteckItem[0]=hPrev;
		LenStectItem=1;
 
}





WNDPROC	gwpOrigEditProc;

///////////////////////////////////////////////////////////////////////////////////////
long FAR PASCAL EditCtrlSubProc(HWND hWnd, WORD wMessage,WORD wParam,LONG lParam)
{
 int k;
 k = 1;
    switch (wMessage)
     {
 
          case WM_GETDLGCODE:
            return (DLGC_WANTALLKEYS |
                    CallWindowProc( (WNDPROC)gwpOrigEditProc, hWnd, wMessage,
                                   wParam, lParam));
 
          case WM_CHAR:
          //Process this message to avoid message beeps.
				if ((wParam == VK_RETURN) || (wParam == VK_TAB))
					return 0;
			break ;
 
       default:
            break;
 
     } /* end switch */


	return (CallWindowProc( (WNDPROC) gwpOrigEditProc, hWnd, wMessage,
                                   wParam, lParam));

}



void CDeskEditor::InsertNextFolder(LPSTR lpszItem, int IndexFolder,int iconType,LPSTR strURL)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
  
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
   
    // Save the heading level in the item's application-defined 
    // data area.
	
	if (strURL ==NULL ){
	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 
	} else {
	int intLenStr = strlen(strURL);
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,strURL);
    tvi.lParam = (LPARAM) ParStr; 
	}


    tvi.iImage = iconType; 
    tvi.iSelectedImage = iconType; 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 
 
    // Set the parent item based on the specified level. 
	if (LenStectItem > 0 ) {
         tvins.hParent = SteckItem[LenStectItem-1]; 
	}else {
		tvins.hParent = TVI_ROOT;
	}
   
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
		SteckItem[LenStectItem]=hPrev;
		LenStectItem++;

}

void CDeskEditor::InsertItem(LPSTR lpszItem, LPSTR lpszParameters,int mi_Document1)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev = (HTREEITEM) TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
    // Assume the item is not a parent item, so give it a 
    // document image. 
    tvi.iImage = mi_Document1; 
    tvi.iSelectedImage = mi_Document1; 
 
    // Save the heading level in the item's application-defined 
    // data area. 

	int intLenStr = strlen(lpszParameters);
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr,lpszParameters);
    tvi.lParam = (LPARAM) ParStr; 
 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 

	if (LenStectItem > 0 ) {
         tvins.hParent = SteckItem[LenStectItem-1]; 
	}else {
		tvins.hParent = TVI_ROOT;
	}
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 


 
}

void CDeskEditor::TestChildFolderIcon(HTREEITEM hti)
{
	//
	// Get the first subitem.
	//
	HTREEITEM hItem;

	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hti);
	hItemBase = hItem;
	//
	while (hItem != NULL) {
  	   TestFolderIcon(hItem);
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
}



void CDeskEditor::SaveTreeToFile(char *pFileName){

   SaveStart (pFileName);
	//
	//
	HTREEITEM hItem;
	HTREEITEM hItemBase;

	    hItemBase =  TreeView_GetFirstVisible(h_tree); 

	hItem = hItemBase; //TreeView_GetChild(h_tree,hItemBase);
	//
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
	    	  SaveChidren(hItem, pFileName);
		   }else {
	          SaveItem(hItem, pFileName);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}

    SaveEnd (pFileName);

}


void CDeskEditor::SaveStart (char *pFileName){
   FILE *stream;
   stream = fopen( pFileName, "w" );
   char strPut[255];

           sprintf(strPut,"^M^%s\n","MyDesktopToolbox v3.2");
	       fputs(strPut,stream);



   fclose(stream);
}


void CDeskEditor::SaveEnd (char *pFileName){
	    FILE *stream;
	    stream = fopen( pFileName, "a" );


      fclose(stream);
}


void CDeskEditor::SaveItem (HTREEITEM retNew,char *pFileName){
    FILE *stream;
	char strName[255];
	char strPut[500];
	char strUrl[255];
	strUrl[0]= 0;

	int iconType;
    GetItemAttr(retNew,strName,strUrl,iconType);


    stream = fopen( pFileName, "a" );



           sprintf(strPut,"^I^%s^166^%s^%d\n",strName,strUrl,iconType);
	       fputs(strPut,stream);


    fclose(stream);
}



void CDeskEditor::SaveFolderItem(HTREEITEM retNew,char *pFileName){
   FILE *stream;
	char strPut[500];
	char strName[255];
	char strUrl[255];
	if (retNew == NULL ) {
	    //  end folder

       stream = fopen( pFileName, "a" );

	       fputs("^F^end\n",stream);

       fclose(stream);


	} else {
		// begin folder
		int iconType;
	   GetItemAttr(retNew,strName,strUrl,iconType);
       stream = fopen( pFileName, "a" );

          sprintf(strPut,"^F^%s^100^%s^%d\n",strName,strUrl,iconType);

	        fputs(strPut,stream);
 




       fclose(stream);

	}
}

   int CDeskEditor::iTreeLevel=0;

void CDeskEditor::SaveChidren (HTREEITEM retNew,char *pFileName){
	HTREEITEM hItem;

	HTREEITEM hItemBase =  retNew;
    SaveFolderItem(retNew,pFileName);
	hItem = TreeView_GetChild(h_tree,hItemBase);
	//
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
	    	  SaveChidren(hItem, pFileName);
		   }else {
	          SaveItem(hItem, pFileName);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
    SaveFolderItem(NULL,pFileName);
}

void CDeskEditor::LoadTreeFromFile(char *pFileName)
{
   LenStectItem = 0;
   FILE *stream;
   char seps[]   = "^\t\n";
   char *token;
   char s_File[255];
   strcpy(s_File,pFileName);	   
   long NFolder = 0;
   char line[600];
   char NameMenuSub1[240];

   if( (stream = fopen( s_File, "r" )) != NULL )
   {
	   fgets( line, 550, stream );
	   while (!feof( stream )){

 
   
         
   token = strtok( line, seps );
   if (token != NULL ){
//
//   folder 
//
   if (strcmp(token,"F")==0) {
      while( token != NULL )
	  {
          /* While there are tokens in "string" */
          //printf( " %s\n", token );
          /* Get next token: */
          token = strtok( NULL, seps );
		  if (strcmp(token,"end")==0){
			  InsertEndFolder();
  			  NFolder--;
			  break;
		  } else {
			  char strName[255];
		  strcpy(strName,token);
			            token = strtok( NULL, seps );
						token = strtok( NULL, seps );
char strURL[255];
		  strcpy(strURL,token);
						token = strtok( NULL, seps );
			  		  int iconType=0;
		  char strIcon[255];
		  strIcon[0]=0;

		  strcpy(strIcon,token);

              iconType = atoi(strIcon);
			  NFolder++;
			  InsertNextFolder(strName,1,iconType,strURL);	
			  break;
		  }
		}
   }

//
//   Item 
//
   if (strcmp(token,"I")==0) {
          /* While there are tokens in "string" */
          //printf( " %s\n", token );
          /* Get next token: */
          token = strtok( NULL, seps );
		  strcpy(NameMenuSub1,token);
          token = strtok( NULL, seps );
		  char NameP[255];
		  NameP[0]='\0';
          token = strtok( NULL, seps );
		  strcpy(NameP,token);
          token = strtok( NULL, seps );

		  int iconType=0;
		  char strIcon[255];
		  strIcon[0]=0;

		  strcpy(strIcon,token);

iconType = atoi(strIcon);

          token = strtok( NULL, seps );
		
		  InsertItem(NameMenuSub1,NameP,iconType);	
   }
   }

		if( fgets( line, 550, stream ) == NULL){
		   break;
		}

        if (ferror( stream )){
			break;
		}

	   }
      fclose( stream );
   }
}



BOOL CDeskEditor::TestNoExpaned(HTREEITEM hti)
{
    TVITEM tvi; 
	BOOL Ret;
    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.hItem = hti; 

		TreeView_GetItem(h_tree, &tvi); 


//
		Ret = FALSE;

		if (tvi.iSelectedImage == mi_nClose){
			Ret  = TRUE;
		}
		return Ret;
}

DWORD CDeskEditor::GetItemID(HTREEITEM hti, char *Text,int &folder)
{
    TVITEM tvi; 
    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_TEXT | TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.hItem = hti; 
		tvi.pszText = Text; 
        tvi.cchTextMax = 128; 

		TreeView_GetItem(h_tree, &tvi); 


//
		folder = 0;

		if (tvi.iSelectedImage == mi_nOpen){
			folder = 1;
		}
		if (  tvi.iImage == mi_nClose) {
			folder = 2;
		}
		return 0;
}

//  ---- all -----
VOID CDeskEditor::ExpandAllW(DWORD Key) {
	//
	//
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	    hItemBase =  TreeView_GetFirstVisible(h_tree); 

	hItem = hItemBase; //TreeView_GetChild(h_tree,hItemBase);
	//
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
              TreeView_Expand(h_tree,hItem,Key);
              ExpandChildren(hItem,Key);
              TestFolderIcon(hItem);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	}
}
// ---------------

VOID CDeskEditor::ExpandAll(HTREEITEM hti,DWORD Key)
{
  TreeView_Expand(h_tree,hti,Key);
  TestFolderIcon(hti);
  ExpandChildren(hti,Key);
}



LRESULT CDeskEditor::OnSaveTree(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
			              SaveTreeToFile(lpCommand);
						  return 0;
}

LRESULT CDeskEditor::OnShowEditBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HTREEITEM hCurrentFolder = TreeView_GetSelection(h_tree);
	m_EditItem = hCurrentFolder;
	if (hCurrentFolder != NULL ){

RECT prc;

TreeView_GetItemRect(
   h_tree,hCurrentFolder,
   &prc,
   TRUE
);

RECT Rect;

HWND t = GetDlgItem(IDC_TREE_CTRL);
HWND hwndEditName = GetDlgItem(IDC_EDIT_TREE_NAME);



::GetWindowRect(t, &Rect ); 

int iWidthDelta = (Rect.right - Rect.left) - prc.right -10;
prc.right += iWidthDelta;





	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hCurrentFolder; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 


m_EditControl.m_EditItem = hCurrentFolder;
m_EditControl.h_tree = h_tree;
m_EditControl.SetWindowText(strTemp);
m_EditControl.h_MainWindow = this->m_hWnd;



m_EditControl.MoveWindow(prc.left ,
            prc.top + 51  ,
            prc.right-prc.left, prc.bottom-prc.top,TRUE);





m_EditControl.ShowWindow(SW_SHOW);


m_EditControl.SetFocus();

/*       pEditBox = new CEdit;
       pEditBox->Create(ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
       CRect(prc), this, 1);
	   pEditBox->SetWindowText(strTemp);
	   pEditBox->SetFocus( );
*/
	}
 


		return 0;
	}

VOID CDeskEditor::ExpandChildren(HTREEITEM hti,DWORD Key)
{
 	//
	// Get the first subitem.
	//
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hti);
	hItemBase = hItem;
	//
	// Do the same for other subitems of hSrc.
	//
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
              TreeView_Expand(h_tree,hItem,Key);
              TestFolderIcon(hItem);
	    	  ExpandChildren(hItem,Key);
		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	} 
}

BOOL CDeskEditor::TestNoExpandAll(HTREEITEM hti)
{
 return TestNoExpandChildren(hti);
}

BOOL CDeskEditor::TestNoChildren(HTREEITEM hti)
{
	HTREEITEM hItem;
	hItem = TreeView_GetChild(h_tree,hti);
	if (hItem){ return FALSE;} else
	{return TRUE;}
}


BOOL CDeskEditor::TestNoExpandChildren(HTREEITEM hti)
{
 	//
	// Get the first subitem.
	//
	BOOL Ret;
	HTREEITEM hItem;
	HTREEITEM hItemBase;
	hItem = TreeView_GetChild(h_tree,hti);
	hItemBase = hItem;
	//
	// Do the same for other subitems of hSrc.
	//
	Ret = FALSE;
	while (hItem != NULL) {
		   if (TestFolder(hItem)){
			  Ret = TestNoExpaned(hItem);
				  if (Ret){
					  break;
				  }
	    	  Ret = TestNoExpandChildren(hItem);
				  if (Ret){
					  break;
				  }

		   }
	   hItem = TreeView_GetNextItem(h_tree,hItem,TVGN_NEXT );
	} 
	return Ret;
}


LRESULT CDeskEditor::OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	   	bHandled = FALSE ;
  	    char MenuFileName[MAX_PATH];
		char *szFilter = "XML files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
		TCHAR filterF[20];
		strcpy(filterF,_T("*.xml;*.*"));
        MenuFileName[0] = '\0';
		switch( wParam ) 
	{
	    case ID_FILE_NEW:
			{
		       m_EditTreeItem = NULL;
   	           TreeView_DeleteAllItems(GetDlgItem(IDC_TREE_CTRL));
 		       strcpy(CurrentFileName,"Untitles.xml");
			}
			break;
		case ID_INSERT_DELETEALL:
		       m_EditTreeItem = NULL;
		       if (::MessageBox (this->m_hWnd ,"Delete all items and all folders ?", TEXT("Question"), MB_OKCANCEL| MB_ICONQUESTION)==IDOK){
   	               TreeView_DeleteAllItems(GetDlgItem(IDC_TREE_CTRL));
			   }


			break;
		case ID_EDIT_INSERTFILE:
			boolClearAll = FALSE;
	    case ID_FILE_OPENFILE:
			{
			   OPENFILENAME ofn;
		   ofn.lStructSize = sizeof(ofn);
		   ofn.hwndOwner = NULL; 
		   ofn.lpstrFile = MenuFileName; 
		   ofn.nMaxFile = MAX_PATH;
           ofn.lpstrFilter  =    szFilter; 
    
		   ofn.nFilterIndex = 1;
		   ofn.lpstrTitle = TEXT("Please Select a File");
		   ofn.lpstrInitialDir = NULL;
		   ofn.lpstrCustomFilter = NULL;
		   ofn.nMaxCustFilter = 0;
		   ofn.lpstrFileTitle = NULL;
		   ofn.nMaxFileTitle = 0;
		   ofn.nFileOffset = 0;
		   ofn.nFileExtension = 0;
		   ofn.lpstrDefExt = NULL;
		   ofn.lCustData = 0;
		   ofn.lpfnHook = 0;
		   ofn.lpTemplateName = 0;
		   ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;



   if (GetOpenFileName(&ofn))
   {
		 m_EditTreeItem = NULL;
		 if ( boolClearAll == TRUE){
	        TreeView_DeleteAllItems(GetDlgItem(IDC_TREE_CTRL));
		 }
    	 LoadTreeFromFile(MenuFileName);
		 if (boolClearAll == TRUE){
		   strcpy(CurrentFileName,MenuFileName);
		 }

   }
			boolClearAll = TRUE;
   


			}
            break;
		case ID_HELP_ABOUT:
			{
				CCAbout nAbout;
				nAbout.DoModal(this->m_hWnd);
			}
			break;

		case ID_EDIT_SAVEFOLDERTOFILE:
			m_SaveCurrentFolder = TRUE;

	    case ID_FILE_SAVE:
			{
				if (m_SaveCurrentFolder == FALSE ){
				if (strcmp(CurrentFileName,"Untitles.xml") != 0 ){
				   TCHAR szText[MAX_PATH] = TEXT("\0");
				   strcpy(szText,"Write :\n");
				   strcat(szText,CurrentFileName);
				   if (::MessageBox (this->m_hWnd ,szText, TEXT("Question"), MB_OKCANCEL| MB_ICONQUESTION)==IDOK){
					  m_TypeSave =  Type_SAVE;
 		              SaveTreeToFile(CurrentFileName);
				   }
                 break;
				}
				}
			}

	    case ID_FILE_SAVEAS:
			{
				TCHAR szFile[MAX_PATH] = TEXT("\0");
				 OPENFILENAME ofn;
  
				 memset (&ofn, 0, sizeof (ofn));
				 ofn.lStructSize  = sizeof (OPENFILENAME);
				 ofn.hwndOwner = this->m_hWnd ;
				 ofn.lpstrFile = szFile;
				 ofn.nMaxFile = MAX_PATH;  

		          ofn.lpstrFilter = szFilter;  
		          ofn.lpstrTitle = TEXT("Save File As");
		          ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | 
                      OFN_PATHMUSTEXIST; 
		          ofn.lpstrDefExt = TEXT("xml");

		          if (GetSaveFileName (&ofn))  
		          {
					  m_TypeSave =  Type_SAVE;
					  SaveTreeToFile(szFile);
					  if (m_SaveCurrentFolder == FALSE){
   		                 strcpy(CurrentFileName,szFile);
					  }
          
		          }
			m_SaveCurrentFolder = FALSE;


			}
            break;
		case ID_EXPORT_HTMLTREEVIEWPAGE:
			{
				TCHAR szFile[MAX_PATH] = TEXT("\0");
				 OPENFILENAME ofn;
		         char *szFilterDHTML = "html page (*.htm;*.html)\0*.htm;*.html\0All Files (*.*)\0*.*\0";
  
				 memset (&ofn, 0, sizeof (ofn));
				 ofn.lStructSize  = sizeof (OPENFILENAME);
				 ofn.hwndOwner = this->m_hWnd ;
				 ofn.lpstrFile = szFile;
				 ofn.nMaxFile = MAX_PATH;  

		          ofn.lpstrFilter = szFilterDHTML;  
		          ofn.lpstrTitle = TEXT("Export in the DHTML page");
		          ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | 
                      OFN_PATHMUSTEXIST; 
		          ofn.lpstrDefExt = TEXT("htm");

		          if (GetSaveFileName (&ofn))  
		          {
					  m_TypeSave =  Type_DHTML;
					  SaveTreeToFile(szFile);
       
		          }


			 break;
			}
	    case ID_FILE_EXIT:
			EndDialog(0);
            break;
        case ID_POPMENUTREE_COLLAPSED_N:
			ExpandAllW(TVE_COLLAPSE);
			break;
		case ID_POPMENUTREE_EXPANDALL_N:
			ExpandAllW(TVE_EXPAND);
			break;
	}


       CaseMenuPopup( wParam );

		return 0;
	}


HTREEITEM CDeskEditor::InsertNewFolder(LPSTR lpszItem, int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = NULL; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hDest= NULL;
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
  


       tvi.mask = TVIF_TEXT | TVIF_IMAGE 
         | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
         // Set the text of the item. 
         tvi.pszText = lpszItem; 
         tvi.cchTextMax = lstrlen(lpszItem); 
 
   
		    // Save the heading level in the item's application-defined 
		    // data area. 


	int intLenStr = 10;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 

		    tvi.iImage = mi_nClose; 
		    tvi.iSelectedImage = mi_nClose; 
		    tvins.item = tvi; 
		    tvins.hInsertAfter = TVI_LAST; 



     hDest=TreeView_GetSelection(hwndTV);
     if (hDest) {
		    // Set the parent item based on the specified level. 
		    if (TestFolder(hDest) == TRUE ) {
		      tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
		      tvins.hParent = hDest; 
			} else {
		      tvins.hInsertAfter = hDest; 
		      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
			}
	 } else {
 	   tvins.hParent = TVI_ROOT;
       tvins.hInsertAfter = TVI_LAST; 

	 }

   
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
	return hPrev;
}



HTREEITEM CDeskEditor::InsertNewTopFolder(LPSTR lpszItem, int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = NULL; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hDest= NULL;
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
  


       tvi.mask = TVIF_TEXT | TVIF_IMAGE 
         | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
         // Set the text of the item. 
         tvi.pszText = lpszItem; 
         tvi.cchTextMax = lstrlen(lpszItem); 
 
   
		    // Save the heading level in the item's application-defined 
		    // data area.
		 

	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 


		    tvi.iImage = mi_nClose; 
		    tvi.iSelectedImage = mi_nClose; 
		    tvins.item = tvi; 
		    tvins.hInsertAfter = TVI_LAST; 


 	   tvins.hParent = TVI_ROOT;
       tvins.hInsertAfter = TVI_LAST; 


   
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
	return hPrev;
}





HTREEITEM CDeskEditor::InsertNewItem(LPSTR lpszItem, int IndexFolder)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = NULL; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hDest= NULL;
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
   
    // Save the heading level in the item's application-defined 
    // data area. 



	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 




    tvi.iImage = mi_Document; 
    tvi.iSelectedImage = mi_Document; 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 
  
    hDest=TreeView_GetSelection(hwndTV);
    if (hDest) {
 
    // Set the parent item based on the specified level. 
    if (TestFolder(hDest) == TRUE ) {
      tvins.hInsertAfter = (HTREEITEM) TVI_LAST; 
      tvins.hParent = hDest; 
	} else {
      tvins.hInsertAfter = hDest; 
      tvins.hParent = TreeView_GetParent(h_tree,hDest); 
    }
   
    } else {
	   tvins.hParent = TVI_ROOT;
       tvins.hInsertAfter = TVI_LAST; 
   }



    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
	return hPrev;
}





HTREEITEM CDeskEditor::InsertNewTopItem(LPSTR lpszItem, int IndexFolder,int mi_Document1)
{
	HWND hwndTV;
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    HTREEITEM hPrev = NULL; 
    HTREEITEM hPrevRootItem = NULL; 
    HTREEITEM hPrevLev2Item = NULL; 
	HTREEITEM hDest= NULL;
	hwndTV = GetDlgItem(IDC_TREE_CTRL);
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
        | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
 
    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
   
    // Save the heading level in the item's application-defined 
    // data area. 


	int intLenStr = 2;
    LPSTR ParStr = (LPSTR)malloc(intLenStr+2);
	strcpy(ParStr," ");
    tvi.lParam = (LPARAM) ParStr; 



    tvi.iImage = mi_Document1; 
    tvi.iSelectedImage = mi_Document1; 
    tvins.item = tvi; 
    tvins.hInsertAfter = TVI_LAST; 
  
	   tvins.hParent = TVI_ROOT;
       tvins.hInsertAfter = TVI_LAST; 



    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hwndTV, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
	return hPrev;
}




HTREEITEM CDeskEditor::DeleteItem(HTREEITEM hti)
{
	HTREEITEM htiCurrent = NULL;
    htiCurrent = TreeView_GetNextItem(h_tree,hti,TVGN_NEXT );
	if (htiCurrent == NULL){
      htiCurrent = TreeView_GetNextItem(h_tree,hti,TVGN_PREVIOUS );
	  if (htiCurrent == NULL){
	     htiCurrent = TreeView_GetParent(h_tree,hti);
	  }
	}
	TreeView_DeleteItem(h_tree,hti);
	return htiCurrent;
}


	LRESULT CDeskEditor::OnDeleteitemTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	m_EditTreeItem = NULL;
	 LPNMTREEVIEW lpnmtv = (NMTREEVIEW *) pnmh; 
 

//	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pnmh;

	//
	// Do nothing if the user is attempting to drag a top-level item.
	//
	HTREEITEM hItem = pNMTreeView->itemOld.hItem;
//         TreeView_SelectDropTarget(h_tree,NULL);

//-----

	    TVITEM tvi_Sourse;
		



		char strTemp[255];
		strTemp[0]=0;

        tvi_Sourse.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE |
            TVIF_TEXT ;


        tvi_Sourse.hItem = hItem; 
        tvi_Sourse.pszText = strTemp; 
        tvi_Sourse.cchTextMax = 250; 
		TreeView_GetItem(h_tree, &tvi_Sourse); 
//-----
        LPSTR ParStr = (LPSTR)tvi_Sourse.lParam;
        free(ParStr);


		::SetWindowText(hWndEditBoxName,"");
		::SetWindowText(hWndEditBoxURL,"");
		return 0;
	}



void CDeskEditor::CaseMenuPopup(DWORD uMenuID)
{
	HTREEITEM	hti;
	HTREEITEM hCurrentFolder;
	hti = m_EditTreeItem;
			switch( uMenuID )
			{
				// item
			case ID_POPMENUTREE_EXPANDALL:
				ExpandAll(hti,TVE_EXPAND);
				MSelect(hti);
				break;

			case ID_POPMENUTREE_COLLAPSED:
				ExpandAll(hti,TVE_COLLAPSE);
			    TreeView_SelectItem(h_tree,hti);
				break;
			case ID_POPMENUTREE_DELETE:
				    hCurrentFolder = DeleteItem(hti);
	                TreeView_SelectItem(h_tree,hCurrentFolder);
				    TestFolderIcon(hCurrentFolder);
				    MSelect(hCurrentFolder);
				break;


			case ID_POPMENUTREE_INSERTITEM:
				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertNewItem("New Desktop",0);
	            TreeView_SelectItem(h_tree,hti);
				TestFolderIcon(hti);
				MSelect(hti);
				break;

			case ID_POPMENUTREE_INSERTCOPY:
				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertCopy(hCurrentFolder);
	            TreeView_SelectItem(h_tree,hti);
				TestFolderIcon(hti);
				MSelect(hti);
				break;

			case ID_POPMENUTREE_INSERTTOPFOLDER:
				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertNewTopFolder("New Folder",0);
				hCurrentFolder= hti;
				TestFolderIcon(hti);
				MSelect(hti);
				break;

			case ID_POPMENUTREE_INSERTTOPITEM:
				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertNewTopItem("New Desktop",0);

				TestFolderIcon(hCurrentFolder);
				hCurrentFolder =hti;
				TestFolderIcon(hti);
				MSelect(hti);
				break;

			case ID_POPMENUTREE_INSERTFOLDER:
				hCurrentFolder = TreeView_GetSelection(h_tree);
				hti = InsertNewFolder("New Folder",0);
				TestFolderIcon(hCurrentFolder);
				hCurrentFolder =hti;
				TestFolderIcon(hti);
				MSelect(hti);
				break;
				
			}

}

void CDeskEditor::MSelect(HTREEITEM hti)
{
      TreeView_SelectItem(h_tree,hti);

}

void CDeskEditor::WebEncode(char *strSrc)
{
 char strBuf[500];
 char strOut[500];
 char charWork;
 int lenOut = 0;
 strcpy(strBuf,strSrc);
 int lenStr = strlen(strBuf);
 for (int i=0;i < lenStr;i++){
	 charWork = strBuf[i];
  switch( charWork ) 
	{
     case '"':
	   strOut[lenOut]='\\';       
	   lenOut++;
	   strOut[lenOut]=charWork;       
	   lenOut++;
        break;
     default :
	   strOut[lenOut]=charWork;       
	   lenOut++;
	}
 
 }
 	   strOut[lenOut]='\0';       
   strcpy(strSrc,strOut);
}

void CDeskEditor::PaintTop()
{
HDC hDC = GetDC();


	  DWORD wBorder = GetSystemMetrics(SM_CYBORDER);


	RECT rect;



	GetClientRect(&rect);


		rect.bottom = 50;





	BITMAP bm;
	HBITMAP Bitmap;
	HBITMAP bmMemOld;
	HDC hdcMem;
    hdcMem = ::CreateCompatibleDC(hDC);

	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TOP_BG));
    // Create a memory DC.

    // Select the bitmap into the mem DC.
    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);

int iLeft = bm.bmWidth;
   

     ::StretchBlt(hDC,
             85,0,rect.right -85,49,
             hdcMem,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             SRCCOPY);



 
	ReleaseDC(hDC);


    ::SelectObject(hdcMem, bmMemOld);
	::DeleteObject(Bitmap);
    ::DeleteDC(hdcMem); 
//



ReleaseDC(hDC);

}

