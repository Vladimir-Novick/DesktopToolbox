// About25.cpp : Implementation of CAbout25
#include "stdafx.h"
#include "About25.h"
#include <Windowsx.h>
#include "omputerID.h"
#include "RegisterSave.h"
#include "NLisence.h"
#include <math.h>
#include <time.h>



/////////////////////////////////////////////////////////////////////////////
// CAbout25

#define ABOUT25W 305
#define ABOUT25H 185

#define START_X_TRAINING 25
#define START_TRAINING_Y 135
#define START_X_TRAINING_WIDTH 67
#define START_TRAINING_Y_H 20

#define RAND_MAX 10

extern int gbl_FlgRegister;


extern void mytrim(char *str,char *dest);
extern void base64_encode(const unsigned char *str, int length,unsigned char *result, int *ret_length);
extern void base64_decode(const unsigned char *str, int length,unsigned char *result, int *ret_length);

	LRESULT CAbout25::OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DWORD dx = GET_X_LPARAM(lParam); 
        DWORD dy = GET_Y_LPARAM(lParam); 
		int pLen;
		POINT mPoint;
		mPoint.x = dx;
		mPoint.y = dy;
		ClientToScreen(&mPoint);
		
		RECT rect;
         GetWindowRect(&rect);
		 long xPos =  mPoint.x - rect.left;
		 long yPos = mPoint.y - rect.top ;
		char strInpKey[512];

		 if ((xPos > 227 && yPos > 27) && (xPos < 294 && yPos < 44 )){
		    ShellExecute(NULL, "open", "http://www.http://www.desk4u.net", NULL, NULL, SW_SHOWNORMAL);
		    EndDialog(0);
			return 0;
		 }


		 if ((xPos > START_X_TRAINING && yPos > START_TRAINING_Y) && (xPos < START_X_TRAINING+START_X_TRAINING_WIDTH && yPos < START_TRAINING_Y+START_TRAINING_Y_H)){

		ComputerID pID;

		char comstr[512];

/*		{


			  char *src="aHR0cDovL3d3dy5kZWx0YWNvbS5jby5pbC9kaWMvcmVnLnBocD9yPQ--"; //"http://www.deltacom.co.il/dic/en/index.html?2.9"
			  int il;
			  base64_decode((const unsigned char *)src,strlen(src),(unsigned char *)comstr,&il);

		}


*/
//		strcpy(comstr,"http://localhost/register/reg.php?r=");

		  char temp22[512];

		 CRegisterSave *mReg;
          mReg = new CRegisterSave;

		  char strUserID[512];
		  char temp2[512];
		  pID.GetComuterID(strInpKey);

      pLen = 0;
      base64_encode((unsigned char *)strInpKey,strlen(strInpKey),(unsigned char *)temp22,&pLen);
	  temp22[pLen] = 0;




		  char temp21[512];

		  HWND thWnd;

		  thWnd = ::GetDlgItem(this->m_hWnd,IDC_EDIT_USER_ID);
		  char strUserID1[512];
		  strUserID1[0] = 0;
		  ::GetWindowText(thWnd,strUserID1,255);
		  mytrim(strUserID1,strUserID);

      pLen = 0;
      base64_encode((unsigned char *)strUserID,strlen(strUserID),(unsigned char *)temp21,&pLen);
	  temp21[pLen] = 0;


   srand( (unsigned)time( NULL ) );

div_t dM =  div( rand(), 2 );



/*if (dM.rem == 0 ){ 
		  strcpy(comstr,"r=");
		  strcat(comstr,temp22);


		  strcat(comstr,"&l=");
		  strcat(comstr,temp21);

} else {
*/
		  strcpy(comstr,"l=");
		  strcat(comstr,temp21);

		  strcat(comstr,"&r=");
		  strcat(comstr,temp22);

//}








		 char strKey1[255];
		 		 char strKey[255];
		  thWnd = ::GetDlgItem(this->m_hWnd,IDC_EDIT_KEY);
		  strKey1[0] = 0;
		  ::GetWindowText(thWnd,strKey1,255);
		  mytrim(strKey1,strKey);

		 mReg->UserKeyStore("UserID",strUserID,strlen(strUserID),CRegisterSave::WRITE);



		 mReg->UserKeyStore("Key",strKey,strlen(strKey),CRegisterSave::WRITE);

		delete mReg;
		pLen = 0;

      base64_encode((unsigned char *)strKey,strlen(strKey),(unsigned char *)temp2,&pLen);
	  temp2[pLen] = 0;


	    strcat(comstr,"&k=");
		strcat(comstr,temp2);


		strcat(comstr,"&s=");

		char strKeyN[5];


		strcat(strInpKey,strUserID);
		{
		int FlgRegister;

         CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
		delete pLicense;

		if (FlgRegister == 1 ){
		   strcpy(strKey,"Yes");
		       strcpy(strKeyN,"Y");
		} else {
			if (FlgRegister == 2 ){
		       strcpy(strKey,"Trial");
		       strcpy(strKeyN,"T");
			} else {
		       strcpy(strKey,"No");
		       strcpy(strKeyN,"N");
			}
		}
		}

     base64_encode((unsigned char *)strKey,strlen(strKey),(unsigned char *)temp2,&pLen);

		   strcat(comstr,temp2);
SYSTEMTIME SystemTimeStart;

//
	GetSystemTime(
  &SystemTimeStart   // system time
);


// {D2C8128C-D2DF-430A-889B-9C1C1D8764F2}

// HKEY_CURRENT_USER

	 char source1[512];
 char str[512];
 int rett;
 	 sprintf(source1,"%d/%d %d %d:%d",SystemTimeStart.wDay,SystemTimeStart.wMonth,SystemTimeStart.wYear,SystemTimeStart.wHour,SystemTimeStart.wMinute);
		     strcat(source1,strKeyN);
	 base64_encode((unsigned char *)source1,strlen(source1),(unsigned char *)str,&rett);
	 str[rett]=0;

//
		strcat(comstr,"&tr=");
		strcat(comstr,str);

		char strLine[512];
		strcpy(strLine,"http://www.mydesktoptoolbox.com/register/reg3.php?sl=");

		base64_encode((unsigned char *)comstr,strlen(comstr),(unsigned char *)str,&rett);
	    str[rett]=0;
		strcat(strLine,str);


	       ShellExecute(NULL, "open",strLine, NULL, NULL, SW_SHOWNORMAL);



		
		CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		gbl_FlgRegister = pLicense->CheckLicenseForStart();
	    delete pLicense;


  		    EndDialog(0);
			 return 0;
         }



//  exit  ==============================

		 if ((xPos > 258 && yPos > 2) && (xPos < 278 && yPos < 18)){

		 RECT rcScreen;
         SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);



	int mleft = rcScreen.right-ABOUT25W;
	int mtop = rcScreen.bottom-ABOUT25H;

         SetWindowPos(HWND_NOTOPMOST, 
            mleft ,
            mtop ,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);

		EndDialog(0);
		return 0;
	 }


		return 0;
	}




	LRESULT CAbout25::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

PAINTSTRUCT ps;


HDC t_hDC = ::BeginPaint(m_hWnd, &ps);

		DrawBitmap(t_hDC,IDB_SCREEN_25,0,0);

        DrawBitmap(t_hDC,IDB_OK_OF,22,135);

		{
		int FlgRegister;

         CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
		delete pLicense;

		if (FlgRegister == 0) {
           DrawBitmap(t_hDC,IDB_KEY_LOCK,112,132);
//           DrawBitmap(t_hDC,IDB_NETWORK,155,132);
		} else {


		if (FlgRegister == 2) {
           DrawBitmap(t_hDC,IDB_TRIAL_KEY_UNLOCK,112,132);
		} else {
           DrawBitmap(t_hDC,IDB_KEY_UNLOCK,112,132);
		}
//           DrawBitmap(t_hDC,IDB_NETWORK,155,132);
		}




		}





		::ReleaseDC(this->m_hWnd,t_hDC);
 

		::EndPaint(m_hWnd, &ps);

 	bTraining_on = FALSE;
		return 0;
	}



	LRESULT CAbout25::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{


		long xPos = GET_X_LPARAM(lParam); 
		long yPos = GET_Y_LPARAM(lParam); 




		 if ((xPos > START_X_TRAINING && yPos > START_TRAINING_Y) && (xPos < START_X_TRAINING+START_X_TRAINING_WIDTH && yPos < START_TRAINING_Y+START_TRAINING_Y_H)){
			 HDC t_hDC = ::GetWindowDC(this->m_hWnd);
             DrawBitmap(t_hDC,IDB_OK_ON,22,135);
		    ::ReleaseDC(this->m_hWnd,t_hDC);

         } else {
			 HDC t_hDC = ::GetWindowDC(this->m_hWnd);
             DrawBitmap(t_hDC,IDB_OK_OF,22,135);
		    ::ReleaseDC(this->m_hWnd,t_hDC);
		 }


		return 0;
	}



LRESULT CAbout25::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		 RECT rcScreen;
         SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);

         SetWindowText("MyDesktopToolbox registration");

	int mleft = (rcScreen.right-ABOUT25W)/2 ;
	int mtop = (rcScreen.bottom-ABOUT25H)/2 ;

	SetWindowPos(HWND_TOPMOST, 
            mleft ,
            mtop ,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);
                 ::SetWindowPos(this->m_hWnd, NULL, 
            mleft ,
            mtop ,
            ABOUT25W , ABOUT25H, SWP_NOZORDER) ;





	POINT lpptS[8];

		lpptS[0].x = 132; 
		lpptS[0].y = 18;


		lpptS[1].x = 132; 
		lpptS[1].y = 9;


		lpptS[2].x = 140; 
		lpptS[2].y = 1;


		lpptS[3].x = 293; 
		lpptS[3].y = 1;


		lpptS[4].x = 301; 
		lpptS[4].y = 8;


		lpptS[5].x = 301; 
		lpptS[5].y = 23;


		lpptS[6].x = 132; 
		lpptS[6].y = 23;



		lpptS[7].x = 132; 
		lpptS[7].y = 18;












HRGN rgn = CreatePolygonRgn(lpptS,8, ALTERNATE);




			 HRGN rgn2 = CreateRoundRectRgn(0, 22,
				 ABOUT25W,ABOUT25H, 8, 8);

			 HRGN rgnc = CreateRoundRectRgn(0, 22,
				 ABOUT25W,ABOUT25H, 8, 8);

			 CombineRgn(rgnc,rgn,rgn2,RGN_OR);
  


// 109 41
			    int tmp = SetWindowRgn(rgnc, TRUE);


                  ::SetWindowPos(this->m_hWnd, NULL, 
            mleft ,
            mtop ,
            ABOUT25W , ABOUT25H, SWP_NOZORDER) ;


				  HWND thWnd = ::GetDlgItem(this->m_hWnd,IDC_EDIT_COMUTERID);
				  ComputerID *pID ;
				  pID = new ComputerID;
				  char strDat[256];
				  strDat[0]=0;
				  pID->GetComuterID(strDat);
				  ::SetWindowText(thWnd,strDat);
				  delete pID;

				  HDC hdc= ::GetDC(thWnd);
			SIZE size1;
			GetTextExtentPoint32(hdc, "A", 
                1, &size1); 
			::ReleaseDC(thWnd,hdc);

		int w =170;
		int h= size1.cy*1.4;
		int idelta = 5;
                   ::SetWindowPos(thWnd, NULL, 
            109 ,
            62-h/2 ,
            w , h, SWP_NOZORDER) ;


		 CRegisterSave *mReg;
          mReg = new CRegisterSave;

		  char strUserID[255];




				   thWnd = ::GetDlgItem(this->m_hWnd,IDC_EDIT_USER_ID);
               ::SetWindowPos(thWnd, NULL, 
            109 ,
            90 -h/2,
            w , h, SWP_NOZORDER) ;



		  strUserID[0]=0;
		 mReg->UserKeyStore("UserID",strUserID,255,CRegisterSave::READ);

		 ::SetWindowText(thWnd,strUserID);


				   thWnd = ::GetDlgItem(this->m_hWnd,IDC_EDIT_KEY);
               ::SetWindowPos(thWnd, NULL, 
            109 ,
            120 -h/2,
            w , h, SWP_NOZORDER) ;
		  strUserID[0] = 0;
		 mReg->UserKeyStore("Key",strUserID,255,CRegisterSave::READ);
		 ::SetWindowText(thWnd,strUserID);


		 

		delete mReg;





 
		return 1;  // Let the system set the focus
	}

		LRESULT CAbout25::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	int mleft = GetSystemMetrics(SM_CXSCREEN)-ABOUT25W-10;
	int mtop = GetSystemMetrics(ARW_TOPLEFT)-ABOUT25H-10;
         SetWindowPos(HWND_NOTOPMOST, 
            mleft ,
            mtop ,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);

		EndDialog(wID);
		return 0;
	}



HWND CAbout25::hWnd_MyTooltip;


DWORD WINAPI CAbout25::CMyTooltipProc(void* pv)
{
	    HRESULT hRes = CoInitialize(NULL);
    CAbout25 *p = new CAbout25;
    p->DoModal();
	delete p;
    CoUninitialize( );
    return 0;
}


void CAbout25::Launch()
{
	if (::IsWindow(hWnd_MyTooltip)){
		::ShowWindow(hWnd_MyTooltip,SW_SHOW);
	} else {
      DWORD dwThreadID;
      HANDLE h = CreateThread(NULL, 0, CMyTooltipProc, 0, 0, &dwThreadID);
	}
}

void CAbout25::DrawBitmap(HDC hDC, long ID_Bitmap, long x, long y)
{
	HBITMAP	  hBitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(ID_Bitmap));

	BITMAP bm;
    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(hDC);
    // Select the bitmap into the mem DC.
    ::GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, hBitmap);
   
    // Blt the bits.
    ::BitBlt(hDC,
             x, y,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);
    ::DeleteDC(hdcMem); 
	::DeleteObject(hBitmap);
}
