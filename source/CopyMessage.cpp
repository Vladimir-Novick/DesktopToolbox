// CopyMessage.cpp : Implementation of CCopyMessage
#include "stdafx.h"
#include "CopyMessage.h"
#include "NLisence.h"

/////////////////////////////////////////////////////////////////////////////
// CCopyMessage 



HANDLE CCopyMessage::Launch(const char *szDescL, const char *szFolderL)
{
	HANDLE h;
	if (::IsWindow(Win_hWnd)){
		::ShowWindow(Win_hWnd,SW_SHOW);
	} else {
      DWORD dwThreadID;


    strcpy(gbl_szDesc,szDescL);
    strcpy(gbl_szFolder,szFolderL);

      h = CreateThread(NULL, 0, CMyTooltipProc, 0, 0, &dwThreadID);
		
	}
	return h;
}


HWND CCopyMessage::Win_hWnd;
char CCopyMessage::gbl_szDesc[512];
char CCopyMessage::gbl_szFolder[512];
char CCopyMessage::gbl_szActiveDesktop[512];
char CCopyMessage::gbl_szDestDesktopName[512];
char CCopyMessage::szBasePeronalFolderName[512];

DWORD WINAPI CCopyMessage::CMyTooltipProc(void* pv)
{
 HRESULT hRes = CoInitialize(NULL);
    CCopyMessage *p = new CCopyMessage;
    p->DoModal(::GetDesktopWindow());
	delete p;
	CoUninitialize( );
    return 0;
}






DWORD WINAPI CCopyMessage::CopyProcedure(void* pv)
{

 HRESULT hRes = CoInitialize(NULL);
char szDestFolder[512];
strcpy(szDestFolder,szBasePeronalFolderName);
strcat(szDestFolder,gbl_szDesc);

	copyFolder(szDestFolder, gbl_szFolder);
	HWND thWnd = ::GetDlgItem(Win_hWnd,IDCANCEL);
	::SetWindowText(thWnd,"OK");

	CoUninitialize( );
//    ::PostMessage(Win_hWnd,WM_CLOSE, 0,0); 

    return 0;
}

void CCopyMessage::copyFolder(const char *szDesc1_i, const char *szFolder)
{
				char szComment[512];
	WIN32_FIND_DATA FindFileData;
	char strFindDir[512];
	char strFileName[512];
	char szDesc1[512];


	strcpy(szDesc1,szDesc1_i);

	BOOL asFoldes = FALSE;

	HANDLE hFind1;
	char szSourceFolder[512];

	if (szFolder[0]=='"'){
		strcpy(strFindDir,&szFolder[1]);
		strFindDir[strlen(strFindDir)-1]= 0;
	} else {	strcpy(strFindDir,szFolder); }

	strcpy(szSourceFolder,strFindDir);

	DWORD f_attr = GetFileAttributes(strFindDir);
	if (FILE_ATTRIBUTE_DIRECTORY == f_attr){
	  strcat(strFindDir,"\\*.*");
	  asFoldes = TRUE;

char szDName[512];
strcpy(szDName,szDesc1);
strcat(szDName,"\\");

char *startDirName;
for (int j=0;j< strlen(szSourceFolder);j++){
	if ((szSourceFolder[j]=='\\') | (szSourceFolder[j]=='//') | (szSourceFolder[j]==':')){
	startDirName = &szSourceFolder[j+1];
	}
}

strcat(szDName,startDirName);
				  CreateDirectory(szDName, NULL);
				  strcpy(szDesc1,szDName);

	}


	hFind1 = FindFirstFile(strFindDir, &FindFileData);

	if (hFind1 != INVALID_HANDLE_VALUE) {

	  if (FILE_ATTRIBUTE_DIRECTORY !=  FindFileData.dwFileAttributes)
	  {

		strcpy(strFileName,szFolder);
		  if (asFoldes == TRUE ){
		strcat(strFileName,"\\");
		strcat(strFileName,FindFileData.cFileName);
		  } 

ShowMessage(FindFileData.cFileName,gbl_szDestDesktopName);

char szDName[512];
strcpy(szDName,szDesc1);
strcat(szDName,"\\");
strcat(szDName,FindFileData.cFileName);


		CopyFile(strFindDir, // name of an existing file
                 szDName,      // name of new file
                 TRUE         // operation if file exists
                  );
chekError(strFindDir,szDName);
		
	  } 

		while(FindNextFile(hFind1,&FindFileData)){
			if (FILE_ATTRIBUTE_DIRECTORY !=  FindFileData.dwFileAttributes)
			{
			  strcpy(strFileName,szSourceFolder);
			  strcat(strFileName,"\\");
			  strcat(strFileName,FindFileData.cFileName);



ShowMessage(FindFileData.cFileName,gbl_szDestDesktopName);



char szDName[512];
strcpy(szDName,szDesc1);
strcat(szDName,"\\");
strcat(szDName,FindFileData.cFileName);


		CopyFile(strFileName, // name of an existing file
                 szDName,      // name of new file
                 TRUE          // operation if file exists
                  );               
chekError(strFileName,szDName);

			  // .... copy file
			} else {
				if (FindFileData.cFileName[0] != '.'){
				  char szFName[512];
				  char szDesc[512];

				  strcpy(szFName,szSourceFolder);
				  strcat(szFName,"\\");
			      strcat(szFName,FindFileData.cFileName);

				  strcpy(szDesc,szDesc1);



				  copyFolder(szDesc, szFName);
				  
				}
			}

	}
	FindClose(hFind1);
	}
}

	LRESULT CCopyMessage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HICON hIcon = ::LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
	    this->SetIcon(hIcon);
		Win_hWnd = this->m_hWnd;



HWND hwnd_Text = GetDlgItem(IDCANCEL);
RECT rectBut ;
RECT rectButMain ;
::GetWindowRect(this->m_hWnd,&rectButMain);

	int Y = GetSystemMetrics(SM_CYSIZE)+(rectBut.bottom-rectBut.top)*2;
	Y+= bm.bmHeight;
                  ::SetWindowPos(this->m_hWnd, NULL, 
            0 ,
            0 ,
            bm.bmWidth+4 , Y, SWP_NOZORDER | SWP_NOMOVE) ;



::GetWindowRect(hwnd_Text,&rectBut);
                  ::SetWindowPos(hwnd_Text, NULL, 
            345,
            114 ,
            0 , 0, SWP_NOZORDER | SWP_NOSIZE) ;


      DWORD dwThreadID;


      HANDLE h = CreateThread(NULL, 0, CopyProcedure, 0, 0, &dwThreadID);



		return 1;  // Let the system set the focus
	}



CCopyMessage::CCopyMessage()
	{



	      Bitmap = ::LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_TITLE_COPY_TO));
 


    ::GetObject(Bitmap, sizeof(BITMAP), (LPSTR)&bm);

	}



	LRESULT CCopyMessage::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

      PAINTSTRUCT ps;

      BeginPaint( &ps );








    // Create a memory DC.
    HDC hdcMem = ::CreateCompatibleDC(ps.hdc);
    // Select the bitmap into the mem DC.


	HBITMAP bmMemOld    = (HBITMAP)::SelectObject(hdcMem, Bitmap);
   
    // Blt the bits.
    ::BitBlt(ps.hdc,
             0, 0,
             bm.bmWidth , bm.bmHeight,
             hdcMem,
             0, 0,
             SRCCOPY);
    ::SelectObject(hdcMem, bmMemOld);

    ::DeleteDC(hdcMem); 

	      EndPaint( &ps );

		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

void CCopyMessage::ShowMessage(const char *szFrom,const char *szTo)
{

const char *startM = strstr(szFrom,szBasePeronalFolderName);
if (startM == NULL ) {startM = szFrom;}
else {startM += strlen(szBasePeronalFolderName)+1;}
HDC mhDC =::GetWindowDC(Win_hWnd);
TextOut(mhDC,90,70,"From:",5);
TextOut(mhDC,132,70,startM,strlen(startM));

TextOut(mhDC,90,92,"To:",3);
TextOut(mhDC,132,92,szTo,strlen(szTo));



::ReleaseDC(Win_hWnd,mhDC);
}

void CCopyMessage::chekError(char *szDesc,char *szSource)
{
LPVOID lpMsgBuf;
DWORD err = GetLastError();
if (err !=0 ){
FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    err,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL 
);


HDC mhDC =::GetWindowDC(Win_hWnd);

TextOut(mhDC,90,120,"Error:",6);
TextOut(mhDC,132,120,(char *)lpMsgBuf,strlen((char *)lpMsgBuf)-2);

::ReleaseDC(Win_hWnd,mhDC);

// Free the buffer.
LocalFree( lpMsgBuf );
}
}
