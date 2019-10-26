// MyMenu.cpp: implementation of the CMyMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyMenu.h"

#include "About.h"
#include "About25.h"
#include "MenuOperation.h"

#include "winuser.h"
#include "NewLoadLib.h"




extern HWND g_ToolboxWindow;

	char CMyMenu::szMyDesktopToolbarFolder[255];

TCHAR szPreviewClass[]= TEXT("MyDesktopToolboxMenu");









	BOOL CMyMenu::TrackPopupMenu(UINT nFlags, int x, int y, HWND i1,int indexMenu , LPCRECT lpRect)
	{



	DWORD dwStyle = WS_POPUP; 
	DWORD dwExStyle =  WS_EX_TRANSPARENT ;




    HWND hShowing = CreateWindowEx(dwExStyle, // extended window style
		                       szPreviewClass, // registered class name
							  NULL, // window name
							  dwStyle, // window style
                              0, // horizontal position of window
                              0, // vertical position of window
                              1,  // window width
                              1, // window height
							  NULL, // handle to parent or owner window
                              HMENU(NULL), // menu handle or child identifier
							  _Module.GetModuleInstance(), //m_MicroH_hIns, // handle to application instance
							  NULL // window-creation data
							  ); 

	CMenuOperation::setimenuhWnd(hShowing);


			::ShowWindow(hShowing, SW_HIDE ); 



			::SetForegroundWindow (g_ToolboxWindow);


		AttachBaseWnd(hShowing);


		BOOL ret = CMenu::TrackPopupMenu(nFlags,  x, y, hShowing, lpRect);




					::SetForegroundWindow (hShowing);


		::PostMessage(hShowing, WM_NULL, 0, 0); 
		::PostMessage(hShowing,WM_CANCELMODE,0,0);
		::PostMessage(hShowing,WM_CLOSE,0,0); //****

		

		return ret;
	}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyMenu::CMyMenu()
{

b_GoCommand = FALSE;

fSelected = FALSE;
      crSelText = RGB(88,0,0); 
      crSelBkgnd = RGB(255,238,194); 

	 crText = RGB(67,68,67);             // text color of unselected item      
     crBkgnd = RGB(206,219,224);            // background color unselected item   
	BaseMenu = NULL;

IpMenu = 0;



				HDC hdc = ::GetDC(GetDesktopWindow()); 

     LOGFONT lf; 
  memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
                 // 

   strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
       lf.lfHeight =  -MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	   lf.lfCharSet=DEFAULT_CHARSET;




        fontText = CreateFontIndirect (&lf); 

  memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
                 // 

   strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
       lf.lfHeight =  -MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	   lf.lfCharSet=DEFAULT_CHARSET;
	   lf.lfWeight  = FW_MEDIUM;


        fontTextTitle = CreateFontIndirect (&lf); 

  memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
                 // 

   strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
       lf.lfHeight =  -MulDiv(8, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	   lf.lfCharSet=DEFAULT_CHARSET;
	   lf.lfWeight  = FW_MEDIUM;


       fontTextTitleMain = CreateFontIndirect (&lf); 

		::ReleaseDC(MainhWnd,hdc);


}

CMyMenu::~CMyMenu()
{



if (::IsWindow(m_hWnd)){
UnsubclassWindow( );
}
if (IsMenu()){
		DeleteAllMemo(hmenu);
}

}



		VOID CMyMenu::AttachBaseWnd(HWND hWnd)
	{
		SubclassWindow(hWnd);
		MainhWnd = hWnd;

 

	}


	LRESULT CMyMenu::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{



// HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts
//  HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.idb\OpenWithProgids


            wCheckX = 26; //GetSystemMetrics(SM_CXMENUCHECK); 
			RECT rect;
         // Get pointers to the menu item's DRAWITEMSTRUCT 
            // structure and MYITEM structure. 
 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
            pmyitem = (MYITEM *) lpdis->itemData; 






			HFONT hfontOld;
			if (strcmp("*title",pmyitem->fileName)==0){			
              hfontOld = (HFONT)SelectObject(lpdis->hDC, fontTextTitle); 
			} else {
              hfontOld = (HFONT)SelectObject(lpdis->hDC, fontText); 
			}
 
            if (lpdis->itemState & ODS_SELECTED) 
            { 
				current_hMenu = (HMENU)lpdis->hwndItem; 
			}

			if (strcmp("*title",pmyitem->fileName)==0){

				RECT rect;
				 rect.left = lpdis->rcItem.left+3; 
				rect.top = lpdis->rcItem.top+3; 
				rect.right = lpdis->rcItem.right-3; 
				rect.bottom = lpdis->rcItem.bottom-4; 



				MyDrawGradient(lpdis->hDC,rect,RGB(163,169,177),RGB(182,187,193),TRUE);


DrawColorLine(lpdis->hDC,RGB(72,84,100),lpdis->rcItem.left, lpdis->rcItem.top,
			  lpdis->rcItem.right,lpdis->rcItem.top);

DrawColorLine(lpdis->hDC,RGB(243,243,243),lpdis->rcItem.left+1, lpdis->rcItem.top+1,
			  lpdis->rcItem.right-1,lpdis->rcItem.top+1);



DrawColorLine(lpdis->hDC,RGB(72,84,100),lpdis->rcItem.left, lpdis->rcItem.bottom-1,
			  lpdis->rcItem.right,lpdis->rcItem.bottom-1);


DrawColorLine(lpdis->hDC,RGB(72,84,100),lpdis->rcItem.left+3, lpdis->rcItem.bottom-4,
			  lpdis->rcItem.right-3,lpdis->rcItem.bottom-4);


DrawColorLine(lpdis->hDC,RGB(243,243,243),lpdis->rcItem.left+2, lpdis->rcItem.bottom-2,
			  lpdis->rcItem.right-2,lpdis->rcItem.bottom-2);


			SetBkMode(lpdis->hDC, 1); 

			COLORREF kl = SetTextColor(lpdis->hDC, RGB(62,82,132));

    SIZE size;

            GetTextExtentPoint32(lpdis->hDC, pmyitem->psz, 
                lstrlen(pmyitem->psz), &size);

			int nTextX = lpdis->rcItem.left + wCheckX/2 + (lpdis->rcItem.right - lpdis->rcItem.left - size.cx )/2;

            int nTextY = lpdis->rcItem.top+4; 



				if (pmyitem->ID_Bitmap != NULL ){


        BITMAP  bm;
			    HBITMAP hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->ID_Bitmap));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            int st_y = lpdis->rcItem.top -1 +  (lpdis->rcItem.bottom - lpdis->rcItem.top - bm.bmHeight) / 2;
			
			DrawTransparentBitmap(lpdis->hDC,hBmp,nTextX-22,st_y,RGB(0,128,0));
			    DeleteObject(hBmp);



				}			



            ExtTextOut(lpdis->hDC, nTextX+1, nTextY+1, ETO_CLIPPED, 
                &lpdis->rcItem, pmyitem->psz, 
                lstrlen(pmyitem->psz), NULL); 


			SetTextColor(lpdis->hDC, RGB(255,255,255));
            SelectObject(lpdis->hDC, fontTextTitleMain); 

            ExtTextOut(lpdis->hDC, nTextX, nTextY, ETO_CLIPPED, 
                &lpdis->rcItem, pmyitem->psz, 
                lstrlen(pmyitem->psz), NULL); 


			} else {


 
            // If the user has selected the item, use the selected 
            // text and background colors to display the item. 


 
            if (lpdis->itemState & ODS_SELECTED) 
            { 		

                SetTextColor(lpdis->hDC, crSelText); 
                SetBkColor(lpdis->hDC, crSelBkgnd); 





	HBRUSH hbr1 = CreateSolidBrush(
  RGB(72,84,100)  // brush color value
);






    rect.left = lpdis->rcItem.left ; 
	rect.top = lpdis->rcItem.top; 
	rect.right = lpdis->rcItem.right; 
	rect.bottom = lpdis->rcItem.bottom;  


    ::FillRect(lpdis->hDC, &rect, hbr1 );
 
DeleteObject(hbr1);

hbr1 = CreateSolidBrush(
  RGB(255,255,255)  // brush color value
);

    rect.left = lpdis->rcItem.left+ 1; 
	rect.top = lpdis->rcItem.top+1; 
	rect.right = lpdis->rcItem.right-1; 
	rect.bottom = lpdis->rcItem.bottom-1; 

    ::FillRect(lpdis->hDC, &rect, hbr1 );

DeleteObject(hbr1);


	hbr1 = CreateSolidBrush(
  crSelBkgnd  // brush color value
);

     rect.left = lpdis->rcItem.left+ 3; 
	rect.top = lpdis->rcItem.top+3; 
	rect.right = lpdis->rcItem.right-3; 
	rect.bottom = lpdis->rcItem.bottom-3; 


    ::FillRect(lpdis->hDC, &rect, hbr1 );
 
DeleteObject(hbr1);


   rect.left = lpdis->rcItem.left+ wCheckX +3; 
	rect.top = lpdis->rcItem.top+3; 
	rect.right = lpdis->rcItem.right-3; 
	rect.bottom = lpdis->rcItem.bottom-3; 


                fSelected = TRUE; 
            } else {
                SetTextColor(lpdis->hDC, crText); 
                SetBkColor(lpdis->hDC, crBkgnd); 


   rect.left = lpdis->rcItem.left; 
	rect.top = lpdis->rcItem.top; 
	rect.right = lpdis->rcItem.right; 
	rect.bottom = lpdis->rcItem.bottom; 


	rect.left = lpdis->rcItem.left+ wCheckX; 




 MyDrawGradient(lpdis->hDC,rect,RGB(204,232,248),RGB(181,208,222),TRUE);


   rect.left = lpdis->rcItem.left; 
	rect.top = lpdis->rcItem.top; 
	rect.right = lpdis->rcItem.right; 
	rect.bottom = lpdis->rcItem.bottom; 


	rect.left = lpdis->rcItem.right -  wCheckX; 




// MyDrawGradient(lpdis->hDC,rect,RGB(198,226,241),RGB(139,163,175),FALSE);



   rect.left = lpdis->rcItem.left; 
	rect.top = lpdis->rcItem.top; 
	rect.right = lpdis->rcItem.right; 
	rect.bottom = lpdis->rcItem.bottom; 


	rect.left = lpdis->rcItem.right -  wCheckX-8; 
	rect.right = rect.left+8; 



//Blur(lpdis->hDC,rect);


DrawColorLine(lpdis->hDC,RGB(251,252,253),lpdis->rcItem.left+ wCheckX, lpdis->rcItem.top,
			  lpdis->rcItem.right,lpdis->rcItem.top);

DrawColorLine(lpdis->hDC,RGB(251,252,253),lpdis->rcItem.left+ wCheckX, lpdis->rcItem.bottom,
			  lpdis->rcItem.right,lpdis->rcItem.bottom);


   rect.left = lpdis->rcItem.left; 
	rect.top = lpdis->rcItem.top; 
	rect.bottom = lpdis->rcItem.bottom;

	rect.right = lpdis->rcItem.left+ wCheckX; 

MyDrawGradient(lpdis->hDC,rect,RGB(139,163,175),RGB(183,210,224),FALSE);

DrawColorLine(lpdis->hDC,RGB(126,143,152),lpdis->rcItem.left, lpdis->rcItem.top,
			  lpdis->rcItem.left,lpdis->rcItem.bottom);

DrawColorLine(lpdis->hDC,RGB(255,255,255),lpdis->rcItem.left+1, lpdis->rcItem.top,
			  lpdis->rcItem.left+1,lpdis->rcItem.bottom);


//DrawColorLine(lpdis->hDC,RGB(255,255,255),lpdis->rcItem.left+wCheckX-1, lpdis->rcItem.top,
//			  lpdis->rcItem.left+wCheckX-1,lpdis->rcItem.bottom);


//DrawColorLine(lpdis->hDC,RGB(126,143,152),lpdis->rcItem.left+wCheckX, lpdis->rcItem.top,
//			  lpdis->rcItem.left+wCheckX,lpdis->rcItem.bottom);


			}
 
            // Remember to leave space in the menu item for the 
            // check-mark bitmap. Retrieve the width of the bitmap 
            // and add it to the width of the menu item. 
 

            nTextX = wCheckX + lpdis->rcItem.left + 6; 
            nTextY = lpdis->rcItem.top+4; 
 
            // Select the font associated with the item into the 
            // item's device context, and then draw the string. 
 
//            hfontOld = SelectObject(lpdis->hDC, pmyitem->hfont);
			

			SetBkMode(lpdis->hDC, 1); 


		char strTest[255];

		strcpy(strTest,pmyitem->psz);
		strTest[35] = '.';
		strTest[36] = '.';
		strTest[37] = '.';
		strTest[38] = 0;



 



            if (lpdis->itemState & ODS_SELECTED) 
            {
			COLORREF kl = SetTextColor(lpdis->hDC, RGB(255,255,255));



            ExtTextOut(lpdis->hDC, nTextX+1, nTextY+1, ETO_CLIPPED, 
                &lpdis->rcItem, strTest, 
                lstrlen(strTest), NULL); 


			SetTextColor(lpdis->hDC, kl);
			}

            ExtTextOut(lpdis->hDC, nTextX, nTextY, ETO_CLIPPED, 
                &lpdis->rcItem, strTest, 
                lstrlen(strTest), NULL); 


			if (!(pmyitem->asFolder == TRUE)){

				if (pmyitem->ID_Bitmap != NULL ){


        BITMAP  bm;
			    HBITMAP hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->ID_Bitmap));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            int st_y = lpdis->rcItem.top + 1 + (lpdis->rcItem.bottom - lpdis->rcItem.top - bm.bmHeight) / 2;
			
			DrawTransparentBitmap(lpdis->hDC,hBmp,5,st_y,RGB(0,128,0));
			    DeleteObject(hBmp);



				}



			} else {


            if (lpdis->itemState & ODS_SELECTED) 
            { 


         BITMAP  bm;
			    HBITMAP hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_MYFOLDER_OPEN));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            int st_y = lpdis->rcItem.top + (lpdis->rcItem.bottom - lpdis->rcItem.top - bm.bmHeight) / 2;
			
			DrawTransparentBitmap(lpdis->hDC,hBmp,3,st_y,RGB(0,128,0));
			    DeleteObject(hBmp);

			} else {

			
			
         BITMAP  bm;
			    HBITMAP hBmp;
				if (pmyitem->empty){
					hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_MYFOLDER_EMPTY));
				} else {
				  hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_MYFOLDER));
				}
				GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            int st_y = lpdis->rcItem.top + (lpdis->rcItem.bottom - lpdis->rcItem.top - bm.bmHeight) / 2;
			
			DrawTransparentBitmap(lpdis->hDC,hBmp,4,st_y+1,RGB(0,128,0));
			    DeleteObject(hBmp);
			
			}

			}

 
            // Select the previous font back into the device 
            // context. 
 
//            SelectObject(lpdis->hDC, hfontOld); 
 
            // Return the text and background colors to their 
            // normal state (not selected). 
 
/*            if (fSelected) 
            { 
                SetTextColor(lpdis->hDC, crText); 
                SetBkColor(lpdis->hDC, crBkgnd); 
            } 
*/
			}

             SelectObject(lpdis->hDC, hfontOld); 


		return DefWindowProc(uMsg, wParam, lParam);
	}



		VOID CMyMenu::AttachMenu(HMENU hm){




			CMenu::Attach(hm); 




            hmenu = hm; 
  



 
MyModifyMenu(hmenu);

 

		}



	void CMyMenu::DrawColorLine(HDC hDC,COLORREF iColor,int xL,int yL,int xR,int yR){
			  
			  
			   


HPEN hPenOld;
HPEN  hPen;

    LOGBRUSH lb; 






            lb.lbStyle = BS_SOLID; 
            lb.lbColor = iColor; 
            lb.lbHatch = 0; 
 


                hPen = ExtCreatePen(PS_COSMETIC , 
                                    1, &lb, 0, NULL); 

				                hPenOld = (HPEN)SelectObject(hDC, hPen); 


                MoveToEx(hDC,xL,yL,  NULL); 

LineTo(lpdis->hDC,xR,yR); 


//                MoveToEx(hdc,lpdis->rcItem.left+ wCheckX, lpdis->rcItem.bottom,  NULL); 

//LineTo(lpdis->hDC,lpdis->rcItem.right,lpdis->rcItem.bottom); 




                SelectObject(hDC, hPenOld); 
                DeleteObject(hPen); 

}



void CMyMenu::DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor)
   {
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdcTemp = CreateCompatibleDC(hdc);
   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device

                                     // to logical points

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = (HBITMAP )SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP )SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP )SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP )SelectObject(hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode(hdcTemp, GetMapMode(hdc));

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
          SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);

   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
          SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
   } 

HMENU CMyMenu::CreateMenu(VOID)
{
	CMenu::CreatePopupMenu();

    hmenu = this->m_hMenu; 
	return hmenu;
}


LRESULT CMyMenu::OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

	return DefWindowProc(uMsg, wParam, lParam);;
	}



VOID CMyMenu::AddMenuFromDir(HMENU m_menu, char *strFolder)
{
       WIN32_FIND_DATA FindFileData;
        HANDLE hFind;
		char strMask[255];

		BOOL ret= TRUE;



		strcpy(strMask,strFolder);
		strcat(strMask,"\\*.*");
        hFind = FindFirstFile(strMask, &FindFileData);


        if (hFind != INVALID_HANDLE_VALUE) {
			while (ret){
			  if (FindFileData.cFileName[0]!='.'){



                MYITEM *pMyItem = (MYITEM *) LocalAlloc(LMEM_FIXED, 
                sizeof(MYITEM)); 

			    ZeroMemory(pMyItem, sizeof(MYITEM));


		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){



		char strNewFolderName[255];
		strcpy(strNewFolderName,strFolder);
		strcat(strNewFolderName,"\\");
		strcat(strNewFolderName,FindFileData.cFileName);

MENUITEMINFO   mii;


HMENU hmenuPopup = ::CreatePopupMenu(); 
AddTitle(hmenuPopup,"");


		 int IpMenu1 = ::GetMenuItemCount(m_menu);

      mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
         mii.wID = IpMenu1;
         mii.fType = MF_STRING ;
         mii.dwTypeData = "";
         mii.fState =  MF_UNCHECKED  ;
		 mii.hSubMenu = hmenuPopup; 





         ::InsertMenuItem(   m_menu,
                           IpMenu1,
                           TRUE,
                           &mii);
		 
                pMyItem->asFolder = TRUE;
				strcpy(pMyItem->psz,FindFileData.cFileName);
				strcpy(pMyItem->fileName,strNewFolderName);



				::ModifyMenu(m_menu, IpMenu1, MF_BYPOSITION | 
                MF_OWNERDRAW, IpMenu1, (LPTSTR) pMyItem); 





		 AddMenuFromDir(hmenuPopup, strNewFolderName);
		
		} else {



MENUITEMINFO   mii;
		 		 int IpMenu1 = ::GetMenuItemCount(m_menu);

       ZeroMemory(&mii, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
         mii.wID = IpMenu1;
         mii.fType = MFT_STRING;
         mii.dwTypeData = "";
         mii.fState = MFS_ENABLED | MFS_UNCHECKED;



         ::InsertMenuItem(   m_menu,
                           IpMenu1,
                           TRUE,
                           &mii);

				strcpy(pMyItem->psz,FindFileData.cFileName);

				strcpy(pMyItem->fileName,strFolder);
				strcat(pMyItem->fileName,"\\");
				strcat(pMyItem->fileName,FindFileData.cFileName);
				pMyItem->iAction =  ActionRunFile;

				                pMyItem->asFolder = FALSE;

				char *type_file = &pMyItem->psz[strlen(pMyItem->psz)-4];

				if (stricmp(type_file,".lnk") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_SHORTCUT;
				  *type_file = 0;
				}

				if (stricmp(type_file,".pdf") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_PDF_DOC;
				}



				if (stricmp(type_file,".dbf") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_DBF_DOC;
				}



				if (stricmp(type_file,".htm") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_HTML_DOC;

				}

				if (stricmp(type_file,".txt") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_TXT_DOC;

				}				


				if (stricmp(type_file,".ini") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_TXT_DOC;

				}


				if (stricmp(type_file,".jpg") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_JPG_DOC;

				}

				if (stricmp(type_file,".gif") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_JPG_DOC;

				}
				
				if (stricmp(type_file,".bmp") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_JPG_DOC;

				}

				if (stricmp(type_file,".xls") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_XLS_DOC;

				}

				if (stricmp(type_file,".csv") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_XLS_DOC;

				}
				

				if (stricmp(type_file,".ppt") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_PPT_DOC;

				}


				

				if (stricmp(type_file,".doc") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_WORD_DOCUMENT;

				}

				if (stricmp(type_file,".url") == 0 ){
				   pMyItem->ID_Bitmap =  IDB_SHORTCUT_URL;
				  *type_file = 0;
				}

				::ModifyMenu(m_menu, IpMenu1, MF_BYPOSITION | 
                MF_OWNERDRAW, IpMenu1, (LPTSTR) pMyItem); 

		}

//        char psz[255]; 
//	    int   cchItemText;
//		BOOL asFolder;
//		char fileName[255];




				IpMenu++;
			  }
			     ret = FindNextFile(hFind,&FindFileData);

			}
		}
  
        FindClose(hFind);
}



	LRESULT CMyMenu::OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        // Retrieve a device context for the main window.  
 
		hdc = ::GetDC(MainhWnd); 


 
            // Retrieve pointers to the menu item's 
            // MEASUREITEMSTRUCT structure and MYITEM structure. 
 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            pmyitem = (MYITEM *) lpmis->itemData; 
 
            // Select the font associated with the item into 
            // the main window's device context. 

			HFONT hfontOld;
			if (strcmp("*title",pmyitem->fileName)==0){			
              hfontOld = ( HFONT )SelectObject(hdc, fontTextTitle); 
			} else {
              hfontOld = ( HFONT )SelectObject(hdc, fontText); 
			}
 
            // Retrieve the width and height of the item's string, 
            // and then copy the width and height into the 
            // MEASUREITEMSTRUCT structure's itemWidth and 
            // itemHeight members. 
 
			
    SIZE size;


		char strTest[255];

		strcpy(strTest,pmyitem->psz);
		strTest[35] = '.';
		strTest[36] = '.';
		strTest[37] = '.';
		strTest[38] = 0;
		strTest[39] = 0;

            GetTextExtentPoint32(hdc, _T(strTest), 
                strlen(_T(strTest)), &size); 
            lpmis->itemWidth = size.cx  + 26; 
            lpmis->itemHeight = size.cy + 6; 

			if (strcmp("*title",pmyitem->fileName)==0){
				lpmis->itemHeight = lpmis->itemHeight + 6;
			}
 
            // Select the old font back into the device context, 
            // and then release the device context. 
 
             SelectObject(hdc, hfontOld); 
            ::ReleaseDC(MainhWnd, hdc); 

		return DefWindowProc(uMsg, wParam, lParam);
	}


	char CMyMenu::szMyDesktopFavorites[255];

void CMyMenu::AddTitle(HMENU m_menu, char *strTitle)
{


                MYITEM *pMyItem = (MYITEM *) LocalAlloc(LMEM_FIXED, 
                sizeof(MYITEM)); 

			    ZeroMemory(pMyItem, sizeof(MYITEM));

MENUITEMINFO   mii;

       ZeroMemory(&mii, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
         mii.wID = IpMenu;
         mii.fType = MFT_STRING;
         mii.dwTypeData = "";
         mii.fState = MFS_ENABLED | MFS_UNCHECKED;

		 		 int IpMenu1 = ::GetMenuItemCount(m_menu);

         ::InsertMenuItem(   m_menu,
                           IpMenu1,
                           TRUE,
                           &mii);

				strcpy(pMyItem->psz,strTitle);

				strcpy(pMyItem->fileName,"*title");


				                pMyItem->asFolder = FALSE;

				::ModifyMenu(m_menu, IpMenu1, MF_BYPOSITION | 
                MF_OWNERDRAW, IpMenu1, (LPTSTR) pMyItem); 


}

void CMyMenu::Blur(HDC hDC, RECT rect)
{

}

void CMyMenu::AddMyItemIcon(DWORD ID_Menu, int ID_Bitmap)
{

   MENUITEMINFO info;
    info.cbSize = sizeof(info);
        info.fMask = MIIM_DATA; 

if (::GetMenuItemInfo(hmenu, ID_Menu, TRUE, &info)){

	MYITEM *pMyItem = (MYITEM *) info.dwItemData; 
	pMyItem->ID_Bitmap = ID_Bitmap;
}


}

void CMyMenu::AddSubMenuMyItemIcon(DWORD ID_Menu,DWORD ID_Menu_SUB, int ID_Bitmap)
{

	HMENU hmenu_sub = ::GetSubMenu(hmenu,ID_Menu);

   MENUITEMINFO info;
    info.cbSize = sizeof(info);
        info.fMask = MIIM_DATA; 

if (::GetMenuItemInfo(hmenu_sub, ID_Menu_SUB, TRUE, &info)){

	MYITEM *pMyItem = (MYITEM *) info.dwItemData; 
	pMyItem->ID_Bitmap = ID_Bitmap;
}


}





HMENU CMyMenu::AddMyFolder(HMENU m_menu,char *strFolder, char *strDesktopName)
{



                MYITEM *pMyItem = (MYITEM *) LocalAlloc(LMEM_FIXED, 
                sizeof(MYITEM)); 

			    ZeroMemory(pMyItem, sizeof(MYITEM));



MENUITEMINFO   mii;


HMENU hmenuPopup = ::CreatePopupMenu(); 
AddTitle(hmenuPopup,"");

		 int IpMenu1 = ::GetMenuItemCount(m_menu);

      mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
         mii.wID = IpMenu1;
         mii.fType = MF_STRING ;
         mii.dwTypeData = "";
         mii.fState =  MF_UNCHECKED  ;
		 mii.hSubMenu = hmenuPopup; 






         ::InsertMenuItem(   m_menu,
                           IpMenu1,
                           TRUE,
                           &mii);
		 
                pMyItem->asFolder = TRUE;
//				pMyItem->empty = m_Desktop.IsDesktopEmpty(strFolder) ;
				strcpy(pMyItem->psz,strDesktopName);
				strcpy(pMyItem->fileName,strFolder);



				::ModifyMenu(m_menu, IpMenu1, MF_BYPOSITION | 
                MF_OWNERDRAW, IpMenu1, (LPTSTR) pMyItem); 

return hmenuPopup;

}



void CMyMenu::AddMyItem(HMENU m_menu,char *strFolder, char *strDesktopName,int iActionType)
{
                MYITEM *pMyItem = (MYITEM *) LocalAlloc(LMEM_FIXED, 
                sizeof(MYITEM)); 

			    ZeroMemory(pMyItem, sizeof(MYITEM));


MENUITEMINFO   mii;

       ZeroMemory(&mii, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
         mii.wID = IpMenu;
         mii.fType = MFT_STRING;
         mii.dwTypeData = "";
         mii.fState = MFS_ENABLED | MFS_UNCHECKED;

		 		 int IpMenu1 = ::GetMenuItemCount(m_menu);

         ::InsertMenuItem(   m_menu,
                           IpMenu1,
                           TRUE,
                           &mii);

				strcpy(pMyItem->psz,strDesktopName);


				strcpy(pMyItem->fileName,strFolder);

				                pMyItem->asFolder = FALSE;
								pMyItem->iAction = iActionType;

				::ModifyMenu(m_menu, IpMenu1, MF_BYPOSITION | 
                MF_OWNERDRAW, IpMenu1, (LPTSTR) pMyItem); 


}

	VOID CMyMenu::AttachMenu(int m_IDR_MENU1){
		HMENU m_d = ::LoadMenu(_Module.GetModuleInstance(),MAKEINTRESOURCE(m_IDR_MENU1));

BaseMenu = m_d;

		HMENU m_d1 = ::GetSubMenu(m_d,0);
		AttachMenu(m_d1);
		

   //     ::DestroyMenu(m_d);

	}

void CMyMenu::DeleteAllMemo(HMENU hmenu){

 MYITEM *pMyItem; 
 int nItem = ::GetMenuItemCount(hmenu);

for (int ip = 0 ; ip < nItem;ip++){


   MENUITEMINFO info;
    info.cbSize = sizeof(info);
        info.fMask = MIIM_DATA; 

    ::GetMenuItemInfo(hmenu, ip, TRUE, &info);

	pMyItem = (MYITEM *) info.dwItemData; 
        LocalFree(pMyItem); 


	HMENU hmenuPopup = ::GetSubMenu(hmenu,ip);

if ( hmenuPopup != NULL ){
	DeleteAllMemo(hmenuPopup);
}
}

}


char *CMyMenu::GetMenuItemText(HMENU hmenu,int ID)
{
    
#ifndef MIIM_STRING
    #define MIIM_STRING 0x40
#endif

    MENUITEMINFO info;
    info.cbSize = sizeof(info);
    info.fMask = MIIM_STRING;
    info.fType = MFT_STRING;
    info.dwTypeData = NULL;
    ::GetMenuItemInfo(hmenu, ID, TRUE, &info);

    char *textbuf = new char[++info.cch];
    info.dwTypeData = reinterpret_cast<LPSTR>(textbuf);
    ::GetMenuItemInfo(hmenu, ID, TRUE, &info);

    return textbuf;
}



void CMyMenu::MyModifyMenu(HMENU hmenu){

 

 MYITEM *pMyItem; 
int nItem = ::GetMenuItemCount(hmenu);

for (int ip = 0 ; ip < nItem ;ip++){




	HMENU hmenuPopup = ::GetSubMenu(hmenu,ip);

        pMyItem = (MYITEM *) LocalAlloc(LMEM_FIXED, 
                sizeof(MYITEM)); 
		ZeroMemory(pMyItem, sizeof(MYITEM));
		

pMyItem->asFolder = FALSE;

 
if ( hmenuPopup != NULL ){
	MyModifyMenu(hmenuPopup);
	pMyItem->asFolder = TRUE;
}


        // Save the item text in the item structure. 
 

char *text = GetMenuItemText(hmenu,ip);


if (text[0] == '*'){
  strcpy(pMyItem->psz,&text[1]);
  strcpy(pMyItem->fileName,"*title");
} else {
  strcpy(pMyItem->psz,text);
}



delete text;


				::ModifyMenu(hmenu, ip, MF_BYPOSITION | 
                MF_OWNERDRAW, ip, (LPTSTR) pMyItem); 
			}


	}

