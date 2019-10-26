// ToolBox.cpp : Implementation of CToolBox
#include "stdafx.h"
#include <atlapp.h>
#include "ToolBox.h"
#include "MDragTarget.h"
#include "Exit.h"
#include "MyMenu.h"
#include "About25.h"
#include "About.h"
#include "NagScreen.h"
#include "NLisence.h"
#include "MenuOperation.h"


extern HWND g_ToolboxWindow;


int CurrentMenuID = -1;
BOOL bGoMenu;

extern HWND g_MainWindow;



#define WM_MENUCOMMAND 0x0126 

static char szDeskPos[10];
UINT msgRestoreToolbox ;
static	HANDLE threadDDReadWord = NULL;
static	DWORD threadIDReadWord = NULL;


static 	int imenuX;
static 	int imenuY;

			HMENU m_Menu;



LONG APIENTRY MicroHeloWndProc (HWND hWnd,
                              UINT msg,
                              WPARAM wParam,
                              LPARAM lParam)
{
         HDC hdc;
         PAINTSTRUCT ps;

 

   switch (msg)
   {



      case WM_CREATE:
		  {
         //
         // save the index
         //
//         SetWindowLong (hWnd, GWL_USERDATA,
//                       (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);




         break;
		  }


      case WM_MOUSEMOVE:
      {

		  break;
	  }

      case WM_COMMAND:
      {

		  break;
	  }


      case WM_PAINT:
      {


         hdc = BeginPaint (hWnd, &ps);



         EndPaint (hWnd, &ps);
         break;
      }

      case WM_KILLFOCUS:
      {

		  break;
	  }

      case WM_NCLBUTTONDOWN:
      {

		  break;
	  }

      case WM_LBUTTONUP:
      {
         //
         // In case the button is released in my client area
         //
//         HWND hp;
//         hp = GetWindow (hWnd, GW_OWNER);
//         PostMessage (hp, msg, wParam, lParam);
         break;
      }
      case WM_CLOSE:
      {

         //
         // cleanup the index pointer
         //
 //        index = (int *)GetWindowLong (hWnd, GWL_USERDATA);
 //        GlobalFree (index);


			EndDialog(hWnd, NULL);


         return DefWindowProc (hWnd, msg, wParam, lParam);
      }
      default:
          return DefWindowProc (hWnd, msg, wParam, lParam);

   }
             return DefWindowProc (hWnd, msg, wParam, lParam);
}





void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
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


	LRESULT CToolBox::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


			EndDialog(0);
			PostQuitMessage(0);
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

	LRESULT CToolBox::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


   // Remove the notification icon from the taskbar
   NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDI_TASK_ICON_N;
	Shell_NotifyIcon(NIM_DELETE, &nid);


 if (NULL!=pIDropTarget)
 { RevokeDragDrop(m_hWnd);
   CoLockObjectExternal(pIDropTarget, FALSE, TRUE);
   pIDropTarget->Release();
   CoDisconnectObject(pIDropTarget,0);
   delete pIDropTarget;  
	pIDropTarget = NULL;


 }

//      ExitProcess(0);


		return 0;
	}


void CToolBox::showButtonPlus(int pIShow,int pIShowActive,int x,int y)
{

	        HBITMAP hBmp;
		    HDC hdc = ::GetWindowDC(this->m_hWnd);

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pIShow));
            DrawTransparentBitmap(hdc,hBmp,x,y,RGB(0,128,0));
			DeleteObject(hBmp);
			::ReleaseDC(this->m_hWnd,hdc);
			dButton[iMaxButton].ID_ShowButton = pIShow;
			dButton[iMaxButton].ID_ShowButtonActive  = pIShowActive;
			dButton[iMaxButton].x = x;
			dButton[iMaxButton].y = y;
			iMaxButton++;
	
}


BOOL boolStartTrackingShow = FALSE;
int gbl_Toolbox_Height;
int gbl_Toolbox_with;



BOOL  CToolBox::CheckProcessWindow()
{
    POINT pt;
    HWND hWnd;        
    DWORD dwThreadID, dwCurrentThreadID;
    HCURSOR hCursor = NULL;
    
    // Find out which window owns the cursor
    GetCursorPos(&pt);
    hWnd = WindowFromPoint(pt);
    
    // Get the thread ID for the cursor owner.
	DWORD dwProcessID;
    dwThreadID = GetWindowThreadProcessId(hWnd, &dwProcessID);
    
    // Get the thread ID for the current thread
    dwCurrentThreadID = GetCurrentProcessId();
    
    // If the cursor owner is not us then we must attach to 
    // the other thread in so that we can use GetCursor() to 
    // return the correct hCursor
	BOOL bRet;
    if (dwCurrentThreadID != dwProcessID) {
        bRet = FALSE;
    } else {
		bRet = TRUE;
	}
    
    return bRet;
} 



VOID CALLBACK
   CToolBox::TrackMouseTimerProc(HWND hWnd,UINT uMsg,UINT idEvent,DWORD dwTime) {


	if (idEvent == TEST_TOOLBAR_HIDE ){
			if ( !CToolBox::CheckProcessWindow() ){
				CMenuOperation::CloseAllMenu();
			}
	}


	if ( !CMenuOperation::isActive()){

bool bStartHide;
bool bStartShow2;
bool bCheckWinRgn;

		     POINT cur_pos;
		     GetCursorPos(&cur_pos);

switch (szDeskPos[0])
{
  case 'R':
	  {
		     long W_wind = GetSystemMetrics(SM_CXSCREEN) ;
			 long W_height = GetSystemMetrics(SM_CYSCREEN) ;
			 int delta_y = (W_height - gbl_Toolbox_Height ) / 2;

			 bStartShow2 = ((cur_pos.x >  W_wind-3 ) && ( cur_pos.y> delta_y) && ( cur_pos.y < gbl_Toolbox_Height + delta_y));


         RECT rect;
		 ::GetWindowRect(hWnd,&rect);


			bStartShow2 = bStartShow2 && (rect.left > W_wind-27); 


		  long W_wind2 = GetSystemMetrics(SM_CXSCREEN)- 26;
		  bStartHide = rect.left < W_wind2 ;	
		  bCheckWinRgn =(cur_pos.x <  W_wind2-26 ) || ( cur_pos.y > gbl_Toolbox_Height + delta_y) || ( cur_pos.y < delta_y-40);

	  }
	  break;
  case 'L':
	  {
		     long W_wind = GetSystemMetrics(SM_CXSCREEN) ;
			 long W_height = GetSystemMetrics(SM_CYSCREEN) ;
			 int delta_y = (W_height - gbl_Toolbox_Height ) / 2;

			 bStartShow2 = ((cur_pos.x < 3  ) && ( cur_pos.y> delta_y) && ( cur_pos.y < gbl_Toolbox_Height + delta_y));



         RECT rect;
		 ::GetWindowRect(hWnd,&rect);



			bStartShow2 = bStartShow2 && (rect.right < 10); 

		  long W_wind2 = GetSystemMetrics(SM_CXSCREEN)- 26;
		  bStartHide = (rect.right > 10) && (cur_pos.x >  26 );	
		  bCheckWinRgn =(cur_pos.x >  26 ) || ( cur_pos.y > gbl_Toolbox_Height + delta_y) || ( cur_pos.y < delta_y-40);

	  }
	break;
  case 'T':
	  {
		     long W_wind = GetSystemMetrics(SM_CXSCREEN) ;
			 long W_height = GetSystemMetrics(SM_CYSCREEN) ;
			 int delta_x = (W_wind - gbl_Toolbox_with ) / 2;

			 bStartShow2 = ((cur_pos.y < 3  ) && ( cur_pos.x> delta_x) && ( cur_pos.x < gbl_Toolbox_with + delta_x));



         RECT rect;
		 ::GetWindowRect(hWnd,&rect);



			bStartShow2 = bStartShow2 && (rect.bottom < 2);

		  long W_wind2 = GetSystemMetrics(SM_CXSCREEN)- 26;
		  bStartHide = (rect.bottom > 0) & (cur_pos.y > 23) ;	
		  bCheckWinRgn =! bStartShow2;

	  }
	break;
}

	   if (idEvent == TEST_TOOLBAR_HIDE ){
		   if (boolStartTrackingShow == FALSE ){	



			 if (bStartShow2){
				 boolStartTrackingShow = TRUE;
				 ::KillTimer(hWnd,TOOLBAR_SHOW);
				 ::SetTimer(hWnd,TOOLBAR_SHOW,50,TrackMouseTimerProc);
			 }


			 if (bCheckWinRgn){

				 
 
		  if (bStartHide){				 
				 
				 boolStartTrackingShow = TRUE;
				 ::KillTimer(hWnd,TOOLBAR_HIDE);
				 ::SetTimer(hWnd,TOOLBAR_HIDE,50,TrackMouseTimerProc);
		  }
			 }


		   }
	   }



int iDeltaX =0;
int iDeltaY = 0;
int newLeft;
          RECT rect;
          ::GetWindowRect(hWnd,&rect);

int rect_left;
int rect_right;
long W_wind_HIDE;
long W_wind_SHOW;
int newLeftStop;
bool bGoHide;
bool bGoShow;
bool bStopShow;
int newTop;
int newTopStop;

switch (szDeskPos[0])
{
  case 'R':

	  iDeltaX = 3;
	  rect_left = rect.left;
	  rect_right = rect.right;
	  W_wind_HIDE = GetSystemMetrics(SM_CXSCREEN)- 26;
	  W_wind_SHOW = GetSystemMetrics(SM_CXSCREEN)-2;
	  newLeftStop = GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left);
      bGoHide = rect_left < W_wind_HIDE ;
	  bGoShow = rect_right > W_wind_SHOW ;
	  bStopShow = rect_right - iDeltaX < GetSystemMetrics(SM_CXSCREEN);


	  newLeft = rect.left  -3;
	  newTop = rect.top ;
	  newTopStop = rect.top;
	  bGoMenu = rect.left < GetSystemMetrics(SM_CXSCREEN) - 40;

	  break;
  case 'L':
	  {
	  iDeltaX = -3;
	  rect_left = rect.left;
	  rect_right = rect.right;
	  W_wind_HIDE = GetSystemMetrics(SM_CXSCREEN)- 26;
	  W_wind_SHOW = GetSystemMetrics(SM_CXSCREEN)-2;
	  newLeftStop = 0;
      bGoHide = rect_right > 2 ;

	  bGoShow = rect_left < 0;
	  bStopShow = rect_left >= 0;


	  newLeft = rect.left  + 3;
	  newTop = rect.top ;
	  newTopStop = rect.top;
	  bGoMenu = rect.left >= -1;
	  }
	break;
  case 'T':
	  {
	  iDeltaY = -3;
	  rect_left = rect.left;
	  rect_right = rect.right;

	  newLeftStop = rect.left;
      bGoHide = rect.bottom > 0 ;

	  bGoShow = rect.top < 0;
	  bStopShow = rect.top >= 0;

				  bGoMenu = rect.bottom > 20;

	  newLeft = rect.left;
	  newTop = rect.top - iDeltaY;
	  newTopStop = 0;

	  }
	break;
}


	   if (idEvent == TOOLBAR_HIDE ){

		  
		  if (bGoHide){

			  ::SetWindowPos(hWnd,HWND_NOTOPMOST, 
            rect.left + iDeltaX ,
            rect.top + iDeltaY ,
            rect.right - rect.left , rect.bottom - rect.top , SWP_NOZORDER) ;
		  } else {
			  ::KillTimer(hWnd,idEvent); 
			 boolStartTrackingShow = FALSE;
		  }
	   }
      if (idEvent == TOOLBAR_SHOW ){


		  if (bGoShow ){
			  if (bStopShow){

				  newLeft = newLeftStop;
				  newTop = newTopStop;
				  ::KillTimer(hWnd,idEvent); 
			 boolStartTrackingShow = FALSE;
			  }
			  ::SetWindowPos(hWnd,HWND_NOTOPMOST, 
            newLeft  ,
            newTop  ,
            rect.right - rect.left , rect.bottom - rect.top , SWP_NOZORDER) ;
		  } else {
			  ::KillTimer(hWnd,idEvent); 
			 boolStartTrackingShow = FALSE;
		  }
	   }
  
	}
//--------- start traching hide


   }



/////////////////////////////////////////////////////////////////////////////
// CToolBox


//int CToolBox::imenuX = 0;
//int CToolBox::imenuY = 0;


void CToolBox::SetWorkWindowRGN_RIGHT(void)
{
		POINT lpptS[30];

		lpptS[0].x = 35; 
		lpptS[0].y = 0;


		lpptS[1].x = 32; 
		lpptS[1].y = 2;


		lpptS[2].x = 32; 
		lpptS[2].y = 42;


		lpptS[3].x = 29; 
		lpptS[3].y = 50;


		lpptS[4].x = 26; 
		lpptS[4].y = 59;


		lpptS[5].x = 24; 
		lpptS[5].y = 70;


		lpptS[6].x = 21; 
		lpptS[6].y = 85;



		lpptS[7].x = 21; 
		lpptS[7].y = 329;


		lpptS[8].x = 24; 
		lpptS[8].y = 345;


		lpptS[9].x = 25; 
		lpptS[9].y = 351;


		lpptS[10].x = 26; 
		lpptS[10].y = 354;


		lpptS[11].x = 27; 
		lpptS[11].y = 357;


		lpptS[12].x = 28; 
		lpptS[12].y = 361;


		lpptS[13].x = 30; 
		lpptS[13].y = 365;


		lpptS[14].x = 32; 
		lpptS[14].y = 371;


		lpptS[15].x = 32; 
		lpptS[15].y = 411;


		lpptS[16].x = 34; 
		lpptS[16].y = 413;


		lpptS[17].x = 40; 
		lpptS[17].y = 413;


		lpptS[18].x = 44; 
		lpptS[18].y = 413;

		lpptS[19].x = 44; 
		lpptS[19].y = 0;


		lpptS[20].x = 35; 
		lpptS[20].y = 0;


		lpptS[21].x = 21; 
		lpptS[21].y = 55;


		lpptS[22].x = 17; 
		lpptS[22].y = 51;


		lpptS[23].x = 17; 
		lpptS[23].y = 31;


		lpptS[24].x = 13; 
		lpptS[24].y = 30;


		lpptS[25].x = 0; 
		lpptS[25].y = 21;


		lpptS[26].x = 7; 
		lpptS[26].y = 0;


		lpptS[27].x = 8; 
		lpptS[27].y = 0;



		lpptS[28].x = 8; 
		lpptS[28].y = 0;



		lpptS[29].x = 8; 
		lpptS[29].y = 0;




			 HRGN rgn4 = CreatePolygonRgn(lpptS,20, ALTERNATE);

/* HRGN rgnE = CreateRoundRectRgn(
  1,      // x-coordinate of upper-left corner
  14,       // y-coordinate of upper-left corner
  36,     // x-coordinate of lower-right corner
  53,    // y-coordinate of lower-right corner
  39,  // height of ellipse
  39  // width of ellipse
);
*/
  
//CombineRgn(rgnE,rgn4,rgnE,RGN_OR);

		    int tmp = SetWindowRgn(rgn4, TRUE);

}




void CToolBox::SetWorkWindowRGN_LEFT(void)
{
		POINT lpptS[30];

		lpptS[0].x = 0; 
		lpptS[0].y = 0;


		lpptS[1].x = 8; 
		lpptS[1].y = 0;


		lpptS[2].x = 11; 
		lpptS[2].y = 3;


		lpptS[3].x = 10; 
		lpptS[3].y = 41;


		lpptS[4].x = 14; 
		lpptS[4].y = 49;


		lpptS[5].x = 18; 
		lpptS[5].y = 62;


		lpptS[6].x = 22; 
		lpptS[6].y = 85;



		lpptS[7].x = 22; 
		lpptS[7].y = 331;


		lpptS[8].x = 19; 
		lpptS[8].y = 343;


		lpptS[9].x = 18; 
		lpptS[9].y = 350;


		lpptS[10].x = 16; 
		lpptS[10].y = 358;


		lpptS[11].x = 10; 
		lpptS[11].y = 372;


		lpptS[12].x = 10; 
		lpptS[12].y = 373;


		lpptS[13].x = 10; 
		lpptS[13].y = 409;


		lpptS[14].x = 8; 
		lpptS[14].y = 413;


		lpptS[15].x = 0; 
		lpptS[15].y = 413;


		lpptS[16].x = 0; 
		lpptS[16].y = 0;


	



			 HRGN rgn4 = CreatePolygonRgn(lpptS,16, ALTERNATE);

/* HRGN rgnE = CreateRoundRectRgn(
  1,      // x-coordinate of upper-left corner
  14,       // y-coordinate of upper-left corner
  36,     // x-coordinate of lower-right corner
  53,    // y-coordinate of lower-right corner
  39,  // height of ellipse
  39  // width of ellipse
);
*/
  
//CombineRgn(rgnE,rgn4,rgnE,RGN_OR);

		    int tmp = SetWindowRgn(rgn4, TRUE);

}



void CToolBox::SetWorkWindowRGN_TOP(void)
{
		POINT lpptS[30];

		lpptS[0].x = 0; 
		lpptS[0].y = 0;


		lpptS[1].x = 0; 
		lpptS[1].y = 7;


		lpptS[2].x = 2; 
		lpptS[2].y = 11;


		lpptS[3].x = 40; 
		lpptS[3].y = 11;


		lpptS[4].x = 51; 
		lpptS[4].y = 15;


		lpptS[5].x = 62; 
		lpptS[5].y = 19;


		lpptS[6].x = 83; 
		lpptS[6].y = 22;



		lpptS[7].x = 330; 
		lpptS[7].y = 22;


		lpptS[8].x = 347; 
		lpptS[8].y = 18;


		lpptS[9].x = 361; 
		lpptS[9].y = 15;


		lpptS[10].x = 371; 
		lpptS[10].y = 11;


		lpptS[11].x = 411; 
		lpptS[11].y = 11;


		lpptS[12].x = 413; 
		lpptS[12].y = 7;


		lpptS[13].x = 413; 
		lpptS[13].y = 0;


		lpptS[14].x = 0; 
		lpptS[14].y = 0;


		lpptS[15].x = 32; 
		lpptS[15].y = 411;


		lpptS[16].x = 34; 
		lpptS[16].y = 413;


		lpptS[17].x = 40; 
		lpptS[17].y = 413;


		lpptS[18].x = 44; 
		lpptS[18].y = 413;

		lpptS[19].x = 44; 
		lpptS[19].y = 0;


		lpptS[20].x = 35; 
		lpptS[20].y = 0;


		lpptS[21].x = 21; 
		lpptS[21].y = 55;


		lpptS[22].x = 17; 
		lpptS[22].y = 51;


		lpptS[23].x = 17; 
		lpptS[23].y = 31;


		lpptS[24].x = 13; 
		lpptS[24].y = 30;


		lpptS[25].x = 0; 
		lpptS[25].y = 21;


		lpptS[26].x = 7; 
		lpptS[26].y = 0;


		lpptS[27].x = 8; 
		lpptS[27].y = 0;



		lpptS[28].x = 8; 
		lpptS[28].y = 0;



		lpptS[29].x = 8; 
		lpptS[29].y = 0;




			 HRGN rgn4 = CreatePolygonRgn(lpptS,14, ALTERNATE);

/* HRGN rgnE = CreateRoundRectRgn(
  1,      // x-coordinate of upper-left corner
  14,       // y-coordinate of upper-left corner
  36,     // x-coordinate of lower-right corner
  53,    // y-coordinate of lower-right corner
  39,  // height of ellipse
  39  // width of ellipse
);
*/
  
//CombineRgn(rgnE,rgn4,rgnE,RGN_OR);

		    int tmp = SetWindowRgn(rgn4, TRUE);

}





LRESULT CToolBox::OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
			 POINT m2Point;
			GetCursorPos(&m2Point);
		    RECT rect;
            GetWindowRect(&rect);

	   if (dwn != TRUE ){
			long lx = rect.right - rect.left;
			long ly = rect.bottom -  rect.top;
         
	   } else {
      
		   dwn = FALSE;
	       ImageList_DragLeave(NULL) ;
	       ImageList_EndDrag() ;

			long lx = rect.right - rect.left;
			long ly = rect.bottom -  rect.top;
            rect.left  = m2Point.x - dx ;
            rect.top   = m2Point.y - dy ;


				::MoveWindow(this->m_hWnd,
            rect.left ,
            rect.top,
            lx,
			ly, TRUE);

		    CRegisterSave mReg;
            ReleaseCapture(); 
	          if (hImageList != NULL) { 
		         ImageList_RemoveAll(hImageList);
		         ImageList_Destroy(hImageList);
			     hImageList = NULL;
			  }

		    mReg.UserKeyStore("EToolbarLeft",&(rect.left),0,CRegisterSave::WRITE);
		    mReg.UserKeyStore("EToolbarTop",&(rect.top),0,CRegisterSave::WRITE);

	 }

		return 0;
	}


 char* CToolBox::strMyDesktopTollboxMainWindow = {"MyDesktopToolbox - www.desk4u.net - main window"};

	   LRESULT CToolBox::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      PAINTSTRUCT ps;

      BeginPaint( &ps );

HDC hDC = GetDC();

	BITMAP bm;
	HBITMAP Bitmap;
	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(CurrentScreenID));
    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(ps.hdc);
    // Select the bitmap into the mem DC.
    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);
   
    // Blt the bits.
    ::BitBlt(ps.hdc,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);
	::DeleteObject(Bitmap);
    ::DeleteDC(hdcMem); 

		iMaxButton = 0;


switch (szDeskPos[0])
{
  case 'R':
	  {

    showButtonPlus(IDB_CLOSE,IDB_CLOSE_ON,26,55);
    showButtonPlus(IDB_HELP,IDB_HELP_ON,26,340);
	showButtonPlus(IDB_WEB_NOTE_OFF,IDB_WEB_NOTE_ON,23,94);
	showButtonPlus(IDB_DESKTOP_OFF,IDB_DESKTOP_ON,23,119);
	showButtonPlus(IDB_WEB_LINK_OFF,IDB_WEB_LINK_ON,23,144);
		showButtonPlus(IDB_TOOLS_OFF,IDB_TOOLS_ON,23,169);
	  }
	break;
  case 'L':
	  {
    showButtonPlus(IDB_CLOSE,IDB_CLOSE_ON,2,55);
    showButtonPlus(IDB_HELP,IDB_HELP_ON,2,340);
	showButtonPlus(IDB_WEB_NOTE_OFF,IDB_WEB_NOTE_ON,2,94);
	showButtonPlus(IDB_DESKTOP_OFF,IDB_DESKTOP_ON,2,119);
	showButtonPlus(IDB_WEB_LINK_OFF,IDB_WEB_LINK_ON,2,144);
		showButtonPlus(IDB_TOOLS_OFF,IDB_TOOLS_ON,2,169);
	  }
	break;
  case 'T':
	  {
    showButtonPlus(IDB_CLOSE,IDB_CLOSE_ON,343,1);
    showButtonPlus(IDB_HELP,IDB_HELP_ON,56,1);
	showButtonPlus(IDB_WEB_NOTE_OFF,IDB_WEB_NOTE_ON,94,1);
	showButtonPlus(IDB_DESKTOP_OFF,IDB_DESKTOP_ON,119,4);
	showButtonPlus(IDB_WEB_LINK_OFF,IDB_WEB_LINK_ON,144,4);
	showButtonPlus(IDB_TOOLS_OFF,IDB_TOOLS_ON,169,2);
	  }
	break;
}












//	showButtonPlus(IDB_WEB_LINK_OFF,IDB_WEB_LINK_ON,23,119); // + 25
//	showButtonPlus(IDB_TOOLS_OFF,IDB_TOOLS_ON,23,144); // + 25
//	showButtonPlus(IDB_SCRIPT_OFF,IDB_SCRIPT_ON,25,172); // + 25
//	showButtonPlus(IDB_WRITE_TOOLS_OFF,IDB_WRITE_TOOLS_ON,24,194); // + 25










//			   DrawTitle(hDC,_T(m_Desktop.szActiveDesktopName),24,320,RGB(85,100,134));
ReleaseDC(hDC);

      EndPaint( &ps );

	  return 0;
	}




	CToolBox::CToolBox()
	{

		bEditNameFlag = FALSE;
		CurrentMenuID = -1;

		iCurrentButton = -1;
		hImageList = NULL;
		dwn = FALSE;
		 CRegisterSave pReg;
		 szDeskPos[0]=0;
		 pReg.UserKeyStore("DeskPosition",szDeskPos,10,CRegisterSave::READ);

		 if (szDeskPos[0]==0) {
			 szDeskPos[0]='R';
		 }


switch (szDeskPos[0])
{
  case 'R':
	CurrentScreenID = IDB_RIGHT_SCREEN;
	break;
  case 'L':
	CurrentScreenID = IDB_LEFT_SCREEN;
	break;
  case 'T':
	CurrentScreenID = IDB_TOP_SCREEN;
	break;
}
		 
	    standard_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_NORMAL));
		select_cursor = LoadCursor(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDC_SELECT));


		// IDB_MAINWINDOW
		iMaxButton = 0;

	}


HWND CToolBox::toolBarhWnd;

	   LRESULT CToolBox::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{




			 RECT rect;
         GetWindowRect(&rect);

		long X = GET_X_LPARAM(lParam); 
		long Y = GET_Y_LPARAM(lParam); 


		   checkButtonList(X,Y);

/*
if (( X  > 24) && (Y  > 197) 
        && ( X  < 38) && (Y  < 320) ){
	CMyDesktop	m_Desktop;
   HDC hDC = GetDC();
   DrawTitle(hDC,_T(m_Desktop.szActiveDesktopName),24,320,RGB(151,14,7));
		bEditNameFlag = TRUE;
   
   ReleaseDC(hDC);
} else {
	CMyDesktop	m_Desktop;
   HDC hDC = GetDC();
   bEditNameFlag = FALSE;
   DrawTitle(hDC,_T(m_Desktop.szActiveDesktopName),24,320,RGB(85,100,134));
   ReleaseDC(hDC);

}
*/


		if (dwn == TRUE ) {
//			if (( X - dx > 80) || (Y - dy > 80) 
//		        || ( X - dx < 80) || (Y - dy < 80) ){

 
			 POINT m2Point;

			GetCursorPos(&m2Point);
				
			 POINT mPoint;
		     mPoint.x = X;
		     mPoint.y = Y;
		     ClientToScreen(&mPoint);
             ImageList_DragMove(m2Point.x,m2Point.y) ;
		}	 
		
		return 0;
	}



LRESULT CToolBox::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

msgRestoreToolbox = RegisterWindowMessage(
  "RestoreToolbox"  // message string
);


  ::SetWindowText(this->m_hWnd,CToolBox::strMyDesktopTollboxMainWindow);

   NOTIFYICONDATA nid;
   nid.cbSize = sizeof(nid);
   nid.hWnd = m_hWnd;        
   nid.uID = IDI_TASK_ICON_N;   
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.uCallbackMessage = UM_DISPRESICONNOTIFY;
   nid.hIcon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON_N));
   lstrcpyn(nid.szTip, "My Desktop Toolbox V3.2", sizeof(nid.szTip) / sizeof(nid.szTip[0]));
   Shell_NotifyIcon(NIM_ADD, &nid);
   SendMessage(m_hWnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) nid.hIcon);








g_ToolboxWindow = this->m_hWnd;


	WNDCLASS wc;

toolBarhWnd = this->m_hWnd;

   wc.style = CS_SAVEBITS;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = wc.cbWndExtra = 0;
   wc.hInstance = _Module.GetModuleInstance();
   wc.hIcon = NULL;
   wc.hCursor = NULL;
   wc.hbrBackground = NULL;
   wc.lpszMenuName		= NULL;
   wc.lpszMenuName = NULL;



   wc.lpfnWndProc = MicroHeloWndProc;
   wc.lpszClassName = szPreviewClass;

 
   if (!RegisterClass(&wc)) {
       int p = 1; 
   }



initPanel();







              pIDropTarget=new CDropTarget;
			  if (NULL!=pIDropTarget) 
			  {    
				  OleInitialize(NULL);
				  pIDropTarget->AddRef();
			    CoLockObjectExternal(pIDropTarget,
				  TRUE, FALSE);
			    RegisterDragDrop(m_hWnd, pIDropTarget);
                CoDisconnectObject(pIDropTarget,0);
			  }






		return 1;  // Let the system set the focus
	}


	LRESULT CToolBox::OnQueryEndSession(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	CRegisterSave mReg;
	
	return TRUE;
	}



	LRESULT CToolBox::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		dx = GET_X_LPARAM(lParam); 
        dy = GET_Y_LPARAM(lParam); 
		POINT mPoint;
		mPoint.x = dx;
		mPoint.y = dy;
		ClientToScreen(&mPoint);
		
		RECT rect;
         GetWindowRect(&rect);
		 long xPos =  mPoint.x - rect.left;
		 long yPos = mPoint.y - rect.top ;



		 //
		 // Move Region
		 //

		 int activButton =  CMenuOperation::getActivButton();

		switch (activButton)
		{
		case 0 :
			{

ShowWindow(SW_HIDE);			
/*				CMyDesktop mDesk;
				if (strcmp(mDesk.szActiveDesktop,"Desktop")==0){ 
		       CExit *pD = new CExit;
               pD->DoModal(GetDesktopWindow());//::GetDesktopWindow());
	           BOOL ret = pD->boolReturnValue;
	           delete pD;
	           if (ret == TRUE ){
		          bExit = TRUE;
		          PostQuitMessage(1);
			   }
				} else {
					::MessageBox(NULL, "Check your current desktop.\n Use the My Desktops option in Start menu to check the main Windows desktop .","Unable to Exit",MB_ICONSTOP | MB_OK);
				}
*/			 }
			 break;

		case 3:
			{

  
     


			}
		  break;

		case 2:
			{

		char szFolderName[MAX_PATH];
		DWORD lpType;
		HKEY hCU;
		ULONG ulSize = MAX_PATH;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, 
			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 
			0,KEY_ALL_ACCESS,
			&hCU) == ERROR_SUCCESS)
		{
			RegQueryValueEx( hCU,
				"Desktop",
				NULL,
				&lpType,
				(unsigned char *)szFolderName,
				&ulSize);
//strcat(szFolderName,"1"); 
//ulSize = strlen(szFolderName);
//		RegSetValueEx(hCU,"Desktop",0,REG_SZ,(const unsigned char *)szFolderName,ulSize);




//			strcat(szFolderName,"\\My Desktop Toolbox\\");

			RegCloseKey(hCU);


/*				  CNewMenu menu;
                  menu.CreatePopupMenu();
				  menu.AppendODMenu("",MF_BYPOSITION , 10000,szFolderName);
  menu.SetMenuTitle(_T("Edit"),MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);

int icur_pos_x=0;
 int icur_pos_y = 0;

CWnd m_W;


m_W.Attach(m_hWnd);

    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,icur_pos_x, icur_pos_y, &m_W);
*/

				}	}


		}


		 if (IDB_RIGHT_SCREEN != CurrentScreenID ){
			if (( yPos  < 29) && (xPos  > 18)){
				 dwn = TRUE;
				 if (hImageList == NULL ) {
                     hImageList = ImageList_LoadImage (_Module.m_hInst,
                                        MAKEINTRESOURCE(CurrentScreenID),
                                        165,
                                        1,
                                        RGB(0,0,0),
                                        IMAGE_BITMAP,
                                        0);
				 }
	       if (hImageList != NULL) { // Just to be sure
						 POINT m2Point;
						 GetCursorPos(&m2Point);

    // Capture the mouse input. 
						 SetCapture(); 
                      ImageList_BeginDrag(hImageList, 0, dx, dy) ;
					  ImageList_DragEnter(::GetDesktopWindow(), m2Point.x, 
				        m2Point.y); 
 
		   }
			}
		 }

		return 0;

	}










void CToolBox::checkButtonList(int x,int y)
{
	int newAction = -1;


	if (bGoMenu){
	for (int ip = 0;ip<iMaxButton;ip++){
      if ((dButton[ip].x < x ) && (dButton[ip].x+ 16 > x ) &&
		  (dButton[ip].y < y ) && (dButton[ip].y+17 > y )){
		newAction = ip;

		break;
	  }
	}
	}



	int activButton = CMenuOperation::getActivButton();
   int iOldWorkPos = activButton;

	if (CurrentMenuID != newAction){

		if (CurrentMenuID >= 0 )
			CMenuOperation::DeActivateMenu(CurrentMenuID,true);
		
		CurrentMenuID = -1;




		if ( newAction > 0){


          RECT rect;
          ::GetWindowRect(this->m_hWnd ,&rect);
		  long W_wind = ::GetSystemMetrics(SM_CXSCREEN)+2;
		  if (rect.right <= W_wind ){
		    CurrentMenuID = newAction;

		POINT pt;
		pt.x = dButton[newAction].x ;
		pt.y = dButton[newAction].y;

		::ClientToScreen(this->m_hWnd,&pt);

/*
switch (szDeskPos[0])
{
  case 'R':
	pt.x +=2;
	break;
  case 'L':
	pt.x +=13;
	break;
  case 'T':
pt.y +=13;
	break;
}
*/

            CMenuOperation::ActivateMenu(newAction, pt.x+8, pt.y+8, this->m_hWnd);
		  }
		}

	}


	if (newAction != activButton ){



	if ( activButton >= 0 ){
	        HBITMAP hBmp;
		    HDC hdc = ::GetWindowDC(this->m_hWnd);

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(dButton[activButton].ID_ShowButton  ));
            DrawTransparentBitmap(hdc,hBmp,dButton[activButton].x,dButton[activButton].y,RGB(0,128,0));
			DeleteObject(hBmp);
			::ReleaseDC(this->m_hWnd,hdc);
	}
activButton = -1;
    activButton = newAction;


	if ( activButton >= 0 ){
	        HBITMAP hBmp;
		    HDC hdc = ::GetWindowDC(this->m_hWnd);

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(dButton[activButton].ID_ShowButtonActive ));
            DrawTransparentBitmap(hdc,hBmp,dButton[activButton].x,dButton[activButton].y,RGB(0,128,0));
			DeleteObject(hBmp);
			
			::ReleaseDC(this->m_hWnd,hdc);
	}
	}

	if ( activButton >= 0 ){
    

		SetCursor(select_cursor); 

	} else {


		SetCursor(standard_cursor);


	}

}

void CToolBox::DrawTitle(HDC hDC, const char *textTitle, int x, int y,COLORREF crText)
{
	LOGFONT lf;
	char textTitle2[255];

	strcpy(textTitle2,textTitle);

	int iLen = strlen(textTitle);
	if (iLen > 27 ){
		iLen = 27;
		textTitle2[27]=0;
		textTitle2[26]='.';
		textTitle2[25]='.';
		textTitle2[24]='.';
	}

  memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
   
  HFONT fontTextTitle;// 

   strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
       lf.lfHeight =  -MulDiv(9, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	   lf.lfCharSet=DEFAULT_CHARSET;
	   lf.lfWeight  = FW_SEMIBOLD;


    lf.lfOrientation = 900;
    lf.lfEscapement = 900;

        fontTextTitle = CreateFontIndirect (&lf); 
HFONT hfontOld = (HFONT)SelectObject(hDC, fontTextTitle);


SetBkMode(hDC, 0);


			RECT rcItem;

			GetClientRect(&rcItem);

//			rcItem.left = 26;

//			DrawText(ps.hdc, m_Desktop.szActiveDesktopName, 
//                lstrlen(m_Desktop.szActiveDesktopName),&rcItem, DT_SINGLELINE|DT_VCENTER|DT_RIGHT); 



			SetTextColor(hDC, RGB(236,239,255));

  
          ExtTextOut(hDC, x+1,y+1, ETO_CLIPPED , 
                &rcItem, textTitle2, 
                iLen, NULL); 

			SetTextColor(hDC,crText );
   


  
          ExtTextOut(hDC, x,y, ETO_CLIPPED , 
                &rcItem, textTitle2, 
                iLen, NULL); 

SelectObject(hDC, hfontOld);
DeleteObject(fontTextTitle);
}

void CToolBox::initPanel()
{


		 CRegisterSave pReg;
		 szDeskPos[0]=0;
		 pReg.UserKeyStore("DeskPosition",szDeskPos,10,CRegisterSave::READ);

		 if (szDeskPos[0]==0) {
			 szDeskPos[0]='R';
		 }


switch (szDeskPos[0])
{
  case 'R':
	CurrentScreenID = IDB_RIGHT_SCREEN;
	break;
  case 'L':
	CurrentScreenID = IDB_LEFT_SCREEN;
	break;
  case 'T':
	CurrentScreenID = IDB_TOP_SCREEN;
	break;
}
		 
		 

		 
		 


		 RECT rcScreen;
         SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);

	BITMAP bm;
	HBITMAP Bitmap;
	Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(CurrentScreenID));


    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);


   
    // Blt the bits.

	bmWidth = bm.bmWidth ; 
	bmHeight = bm.bmHeight;
	gbl_Toolbox_Height = bm.bmHeight;
	gbl_Toolbox_with = bm.bmWidth ; 

         SetWindowPos(HWND_TOPMOST, 
            0 ,
            0 ,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);


		 if (szDeskPos[0]=='R' ){

         SetWindowPos(HWND_TOPMOST, 
            rcScreen.right - bm.bmWidth ,
            (rcScreen.bottom - bm.bmHeight) /2  ,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);
			 SetWorkWindowRGN_RIGHT();
		 }



		 if (szDeskPos[0]=='L' ){

         SetWindowPos(HWND_TOPMOST, 
            0 ,
            (rcScreen.bottom - bm.bmHeight) /2  ,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);
			 SetWorkWindowRGN_LEFT();
		 }

		 if (szDeskPos[0]=='T' ){

         SetWindowPos(HWND_TOPMOST, 
            (rcScreen.right - bm.bmWidth)/2 ,
            0  ,
            bm.bmWidth , bm.bmHeight, SWP_NOZORDER | SWP_DEFERERASE);
			 SetWorkWindowRGN_TOP();
		 }

		 ::KillTimer(m_hWnd, TEST_TOOLBAR_HIDE);

		 ::SetTimer(m_hWnd, TEST_TOOLBAR_HIDE,1000,TrackMouseTimerProc);




	::DeleteObject(Bitmap);


//----------- desktop position



		 long w = 161;
		 long h = 64+2*GetSystemMetrics(SM_CYBORDER);
//
		 long mleft=-1;
		 long mtop= -1;



//-----------


}

LRESULT CToolBox::InitDesktopPanel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
initPanel();
		return 0;
}
