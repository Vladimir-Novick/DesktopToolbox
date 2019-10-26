// MyDesktop.cpp: implementation of the CMyDesktop class.
//  
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "MyDesktop.h"
#include "RegisterSave.h"
#include "NLisence.h"
#include "ShareWareMessage.h"
#include "About.h"
#include "RegisterSave.h"
#include <Exdisp.h>
#include "NagScreen.h"


extern char lpCommand[255];
BOOL RefrechDesktop(const char *DeskName1);

HRESULT CreateLink(LPCSTR lpszPathObj,LPCSTR lpszExe, LPCSTR lpszParameters,
    LPCSTR lpszPathLink, LPCSTR lpszDesc,int iconIdx=0) ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDesktop::CMyDesktop()
{
	szBasePeronalFolderName[0]=0;
szActiveDesktopName[0]=0;
szActiveDesktopComment[0]=0;
szActiveDesktop[0]=0;

		GetEnvironmentVariable("SYSTEMROOT",szShell,255);
		strcat(szShell,"\\explorer.exe");

strWorkFolder[0]=0;
	ReadSystemParameters();

}

CMyDesktop::~CMyDesktop()
{

}

//  Header: Declared in Psapi.h.
//  Library: Use Psapi.lib.

#include "Psapi.h"

#include "wininet.h"

#include "shlobj.h"

void CMyDesktop::PrintProcessNameAndID( char szProcessName[MAX_PATH],DWORD processID )
{
    strcpy(szProcessName, "unknown");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if ( hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
//            GetModuleBaseName( hProcess, hMod, szProcessName, 
//                               sizeof(szProcessName) );

			int nSize=255;

			GetModuleFileNameExA(hProcess, hMod, szProcessName, nSize);

        }
    }

    // Print the process name and identifier.

    //printf( "%s (Process ID: %u)\n", szProcessName, processID );

    CloseHandle( hProcess );
}

BOOL CMyDesktop::ExitProcessByName(char *strProcessName){
BOOL return_par = FALSE;

  // Get the list of process identifiers.

    DWORD aProcesses[2048], cbNeeded, cProcesses;
    unsigned int i;
	char szProcessName[MAX_PATH];

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return return_par;

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);





    // Print the name and process identifier for each process.

	char *t ;

    for ( i = 0; i < cProcesses; i++ ){
        PrintProcessNameAndID( szProcessName,aProcesses[i] );
		t = strstr(_strlwr(szProcessName),"\\explorer.exe");
		if (t!=NULL){

   HANDLE hProcess = OpenProcess( PROCESS_TERMINATE | SYNCHRONIZE ,
                                   TRUE, aProcesses[i] );
			TerminateProcess(hProcess,0);


		}
	}



return return_par;
}



void CMyDesktop::SetWallpaper(const char *Desktop1)
{


char Desktop[255];


if (strcmp(Desktop1,"Default") == 0){
  strcpy(Desktop,"Desktop");
}else {
  strcpy(Desktop,Desktop1);
}

char FileName[255];

GetEnvironmentVariable("USERPROFILE",FileName,255);

strcat(FileName,"\\");

strcat(FileName,"MyDesktopToolbox");

strcat(FileName,"\\");


strcat(FileName,Desktop);

strcat(FileName,".");


CRegisterSave m_Reg1;
char key_l[512];


char sp[255];
sp[0]=0;

 strcpy(key_l,"Desktop");

strcat(key_l,"_wallpaper");
m_Reg1.UserKeyStore(key_l,sp,255,CRegisterSave::READ);

if (sp[0]==0){
	return;
}

strcat(FileName,sp);

//	SPI_SETDESKWALLPAPER
HRESULT hr;
IActiveDesktop *pActiveDesktop;


hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
            IID_IActiveDesktop, (void**)&pActiveDesktop);

CComBSTR fn;//= 
fn = FileName;
WALLPAPEROPT pwpo;
pwpo.dwSize = sizeof WALLPAPEROPT;

//WPSTYLE_CENTER 
//WPSTYLE_TILE 
//WPSTYLE_STRETCH
//WPSTYLE_MAX 

pwpo.dwStyle = WPSTYLE_CENTER ;

char szS[20];
szS[0]=0;

char szWall[255];
strcpy(szWall,"W_");
strcat(szWall,Desktop);
CRegisterSave mReg;
mReg.UserKeyStore(szWall,szS,20,CRegisterSave::READ);

if (szS[0]!=0){
  pwpo.dwStyle = atoi(szS);
pActiveDesktop->SetWallpaperOptions(&pwpo,0);
}





pActiveDesktop->SetWallpaper(fn,0);
pActiveDesktop->ApplyChanges(AD_APPLY_ALL );

  

// Call the Release method
pActiveDesktop->Release();

//
//  for BMP file
//
//      int ret = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,FileName, SPIF_UPDATEINIFILE |  SPIF_SENDWININICHANGE);
//
}



void CMyDesktop::GetWallpaper(char *FileName,char *Desktop)
{





//	SPI_SETDESKWALLPAPER
HRESULT hr;
IActiveDesktop *pActiveDesktop;


hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
            IID_IActiveDesktop, (void**)&pActiveDesktop);

CComBSTR fn;//= 
fn = FileName;
WALLPAPEROPT pwpo;
pwpo.dwSize = sizeof WALLPAPEROPT;

//WPSTYLE_CENTER 
//WPSTYLE_TILE 
//WPSTYLE_STRETCH
//WPSTYLE_MAX 

pwpo.dwStyle = WPSTYLE_CENTER ;
pActiveDesktop->GetWallpaperOptions(&pwpo,0);

char szS[20];
szS[0]=0;
sprintf(szS,"%d",pwpo.dwStyle);

CRegisterSave mReg;

char szWall[255];
strcpy(szWall,"W_");
strcat(szWall,Desktop);

mReg.UserKeyStore(szWall,szS,strlen(szS),CRegisterSave::WRITE);


UINT iLen = 255;
DWORD r;

pActiveDesktop->GetWallpaper(fn,iLen,r);

  // Convert from BSTR to char for display.
    UINT length = SysStringLen(fn);
    length = wcstombs(FileName, fn, length);
    FileName[length] = '\0';
  

    

// Call the Release method
pActiveDesktop->Release();

//
//  for BMP file
//
//      int ret = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,FileName, SPIF_UPDATEINIFILE |  SPIF_SENDWININICHANGE);
//
}

void CMyDesktop::RestoreWallpaper(char *DesktopNameOld,char *DesktopNameNew){



//  HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Desktop\General

HRESULT hr;
IActiveDesktop *pActiveDesktop;


hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
            IID_IActiveDesktop, (void**)&pActiveDesktop);

CComBSTR fn;
UINT cchWallpaper;
DWORD dwReserved = 0;

pActiveDesktop->GetWallpaper(
    fn,
    cchWallpaper,
    dwReserved
);




}



void CMyDesktop::GoDesktop(const char *DesktopName,BOOL bMsg)
{


// ------- Save Desktop Configuration -------

/*   HWND hDesktop ;

   hDesktop = FindWindowEx(FindWindowEx(
     FindWindow("Progman", "Program Manager"), NULL,
     "SHELLDLL_DefView", NULL), NULL, "SysListView32", NULL) ;
   PostMessage(hDesktop, WM_KEYDOWN, VK_F5, 0) ;
   PostMessage(hDesktop, WM_KEYUP, VK_F5, 0x0020001) ;
*/



RefrechDesktop(szActiveDesktop);

//--------------


char szReStore[255];

strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\IE");
strcat(szReStore,szActiveDesktop);


char *szRegKey200 ="Software\\Microsoft\\Internet Explorer\\Desktop";
SaveAllSubkey(szRegKey200,szReStore);


strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\BE");
strcat(szReStore,szActiveDesktop);


char *szRegKey2B ="Software\\Microsoft\\Windows\\CurrentVersion\\Explorer";
SaveAllSubkey(szRegKey2B,szReStore,FALSE);




char olgWalpaper[255];
GetWallpaper(olgWalpaper,szActiveDesktop);


char szCopy[512];
char szOldDesktop[512];
strcpy(szOldDesktop,szActiveDesktop);

strcpy(szCopy,szBasePeronalFolderName);
strcat(szCopy,"MyDesktopToolbox");

CreateDirectory(szCopy, NULL);
strcat(szCopy,"\\");
strcat(szCopy,szActiveDesktop);
strcat(szCopy,".");

int il = strlen(olgWalpaper);
char *sp = NULL;
for (int i=il;i>0;i--){
	if (olgWalpaper[i] == '.') break;
	sp = &olgWalpaper[i];
}

strcat(szCopy,sp);

CRegisterSave m_Reg;
char key_l[512];

if (sp != NULL ){

			CopyFile(olgWalpaper, // name of an existing file
                 szCopy,      // name of new file
                 FALSE         // operation if file exists
                  );



strcpy(key_l,szActiveDesktop);
strcat(key_l,"_wallpaper");
m_Reg.UserKeyStore(key_l,sp,strlen(sp),CRegisterSave::WRITE);

} 


if (bMsg == TRUE ){

		int FlgRegister;
           CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
	    delete pLicense;

		if ((FlgRegister == 0) && (strcmp("Desktop",DesktopName)!=0)) {
	       CAbout m_About;
		   m_About.DoModal(::GetDesktopWindow());
		} else {
		  if (FlgRegister != 1)  {
	         CAbout m_About;
		     m_About.DoModal(::GetDesktopWindow());
		  } else {
		   SendMessage(GetDesktopWindow(),WM_NULL,0,0);
		  }
		}
}			
		HKEY hkeyRun;

		char s_cszDebugKey[255];
		char s_ValueName[255];
		char d1[255];
		char d2[255];
		LONG ret;




		strcpy(s_cszDebugKey,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders"));
		strcpy(s_ValueName,"Desktop");
//		strcpy(d1,_T("%USERPROFILE%\\"));
		GetEnvironmentVariable("USERPROFILE",d2,255);
		strcat(d2,"\\");		
		strcat(d2,_T(DesktopName));	
		
		strcpy(d1,_T("%USERPROFILE%\\"));
		strcat(d1,_T(DesktopName));

		
		RegOpenKeyEx(HKEY_CURRENT_USER,s_cszDebugKey,0,KEY_WRITE,&hkeyRun);
		ret = RegSetValueEx(hkeyRun,s_ValueName,0,REG_EXPAND_SZ,(const unsigned char *)d1,strlen(d1));
      RegCloseKey(hkeyRun);


ULONG ulSize = MAX_PATH;
DWORD lpType;

		strcpy(s_cszDebugKey,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"));

		RegOpenKeyEx(HKEY_CURRENT_USER,s_cszDebugKey,0,KEY_WRITE,&hkeyRun);
		strcpy(s_ValueName,"Desktop");
RegQueryValueEx( hkeyRun,
				s_ValueName,
				NULL,
				&lpType,
				(unsigned char *)d1,
				&ulSize);

for (int i1=strlen(d1);i1>0; i1--){
	if (d1[i1]=='\\') break;
	d1[i1]=0;}





CreateDirectory(strWorkFolder, NULL);
	    
		strcat(d1,_T(DesktopName));

CreateDirectory(d2, NULL);
		
		ret = RegSetValueEx(hkeyRun,s_ValueName,0,REG_SZ,(const unsigned char *)d1,strlen(d1));
      RegCloseKey(hkeyRun);
	  if ( ERROR_SUCCESS == ret ){
		  int ip1 = 1;
	  }







		
	



int iLen2 = 255;
olgWalpaper[0]=0;
 strcpy(key_l,DesktopName);
 strcat(key_l,"_wallpaper");

m_Reg.UserKeyStore(key_l,olgWalpaper,iLen2,CRegisterSave::READ);
if (olgWalpaper[0] != 0){

strcpy(szCopy,szBasePeronalFolderName);
strcat(szCopy,"MyDesktopToolbox");

CreateDirectory(szCopy, NULL);
strcat(szCopy,"\\");
strcat(szCopy,DesktopName);
strcat(szCopy,".");
strcat(szCopy,olgWalpaper);









char d3[512];
d3[0]='"';
d3[1]=0;
strcat(d3,d2);
int ik = strlen(d3);
d3[ik]='"';
d3[ik+1]=0;


//HKEY_CURRENT_USER\Control Panel\Desktop

}

// HKEY_CURRENT_USER\Software\Microsoft\Windows\Shell\Bags\1\Desktop  - for Windows XP



char szStore[512];










// ------ windows XP


strcpy(szStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szStore,"\\");
strcat(szStore,szOldDesktop);

strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\");
strcat(szReStore,DesktopName);


SaveAllSubkey("Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop",szStore);
SaveAllSubkey(szReStore,"Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop");

// ------- Windows 2000

strcpy(szStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szStore,"\\2000");
strcat(szStore,szOldDesktop);

strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\2000");
strcat(szReStore,DesktopName);


char *szRegKey2005 ="Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Streams\\Desktop";
SaveAllSubkey(szRegKey2005,szStore);
SaveAllSubkey(szReStore,szRegKey2005);

strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\IE");
strcat(szReStore,DesktopName);


char *szRegKey2000 ="Software\\Microsoft\\Internet Explorer\\Desktop";
SaveAllSubkey(szReStore,szRegKey2000);




strcpy(szReStore,"Software\\NVR Soft\\MyDesktopToolbox");
strcat(szReStore,"\\BE");
strcat(szReStore,DesktopName);


char *szRegKey2B1 ="Software\\Microsoft\\Windows\\CurrentVersion\\Explorer";
SaveAllSubkey(szReStore,szRegKey2B1,FALSE);


if (bMsg == TRUE ){
CRegisterSave mReg;
int lr = strlen(DesktopName);
char szDN[255];
strcpy(szDN,DesktopName);
mReg.UserKeyStore("Active",szDN,lr,CRegisterSave::WRITE);
}



if (strcmp(DesktopName,"Desktop")== 0 ){
	CreateNewDesktop("Default",szShell,NULL,d2);
} else {
	   CreateNewDesktop(DesktopName,szShell,NULL,d2);
}




//		ExitProcessByName(_T("\\explorer.exe"));

/*   HWND hDesktop1 ;

   hDesktop1 = FindWindowEx(FindWindowEx(
     FindWindow("Progman", "Program Manager"), NULL,
     "SHELLDLL_DefView", NULL), NULL, "SysListView32", NULL) ;



SendMessage(FindWindowEx(
     FindWindow("Progman", "Program Manager"), NULL,
     "SHELLDLL_DefView", NULL),WM_PAINT ,NULL,NULL);

*/

//CreateNewDesktop(DesktopName,szShell,NULL,d2);






}

BOOL CMyDesktop::FindDesktop(char *strFolder, char *strDesktopName)
{ 
	char szComment[512];
	WIN32_FIND_DATA FindFileData;
	if (hFind == NULL ){
char strFindDir[255];



strcpy(strFindDir,szBasePeronalFolderName);
strcat(strFindDir,"Desktop*");


  hFind = FindFirstFile(strFindDir, &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE) {
	  hFind = NULL ;
   return FALSE;
  }


  strcpy(strFolder,FindFileData.cFileName);



GetDesktopName(strDesktopName,szComment,FindFileData.cFileName);

	} else {

		if (!FindNextFile(hFind,&FindFileData)){
		FindClose(hFind);
		hFind = NULL ;
		return FALSE;
		}
		  strcpy(strFolder,FindFileData.cFileName);

		  GetDesktopName(strDesktopName,szComment,FindFileData.cFileName);

	}


return TRUE;
}

void CMyDesktop::GetDesktopName(char *szName,char *szComment, const char *szDesktopName)
{
szComment[0]=0;
szName[0]=0;




CRegisterSave m_Reg;

int iLenKey;
m_Reg.UserKeyStore(szDesktopName,szName,iLenKey,CRegisterSave::READ);

char n_Key[255];
strcpy(n_Key,szDesktopName);
strcat(n_Key,"_Comment");


m_Reg.UserKeyStore(n_Key,szComment,iLenKey,CRegisterSave::READ);

if (szName[0]==0){
   strcpy(szName,szDesktopName);
	if (strcmp(szDesktopName,"Desktop") == 0 ){
		   strcpy(szName,"Default Desktop");
	}
}





						
}

void CMyDesktop::SetDesktopName(char *szName,char *szComment, const char *szDesktopName)
{



CRegisterSave m_Reg;

int iLenKey;

iLenKey = strlen(szName);
m_Reg.UserKeyStore(szDesktopName,szName,iLenKey,CRegisterSave::WRITE);

char n_Key[255];
strcpy(n_Key,szDesktopName);
strcat(n_Key,"_Comment");

iLenKey = strlen(szComment);
m_Reg.UserKeyStore(n_Key,szComment,iLenKey,CRegisterSave::WRITE);


}




void CMyDesktop::NewDesktop(char *szName,char *szComment)
{
HANDLE hFind;
  char szNewDesktopName[255];
WIN32_FIND_DATA FindFileData;

  long iDesktop = 0;

CRegisterSave m_Reg;
m_Reg.UserKeyStore("MaxDesktop",&iDesktop,0,CRegisterSave::READ); 
iDesktop++;

while (TRUE){
  sprintf(szNewDesktopName,"Desktop%05d",iDesktop);

char strFindDir[255];



strcpy(strFindDir,szBasePeronalFolderName);
strcat(strFindDir,szNewDesktopName);


  hFind = FindFirstFile(strFindDir, &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE) {
   break;
  }

FindClose(hFind);
iDesktop++;

}
m_Reg.UserKeyStore("MaxDesktop",&iDesktop,0,CRegisterSave::WRITE); 
  SetDesktopName(szName,szComment, szNewDesktopName); 
  GoDesktop(szNewDesktopName);
  	    RestoreStartMenu();
}

void CMyDesktop::DeleteCurrentDestop()
{
	if (!IsDesktopEmpty(szActiveDesktop)){
		MessageBox(NULL,"Current Desktop is Not Empty","Error Operation",MB_OK | MB_ICONSTOP);
	} else {
CRegisterSave m_Reg;


m_Reg.UserKeyStore(szActiveDesktop,"",0,CRegisterSave::ERASE);

char n_Key[255];
strcpy(n_Key,szActiveDesktop);
strcat(n_Key,"_Comment");


m_Reg.UserKeyStore(n_Key,"",0,CRegisterSave::ERASE);


	char CurrntDesktopFoler[255];
	strcpy(CurrntDesktopFoler,szBasePeronalFolderName);
	strcat(CurrntDesktopFoler,szActiveDesktop);
  GoDesktop("Desktop");
  RemoveDirectory(CurrntDesktopFoler);
RestoreStartMenu();
	}
}

BOOL CMyDesktop::IsDesktopEmpty(char *strDesktopName)
{
	char szComment[512];
	WIN32_FIND_DATA FindFileData;

char strFindDir[255];



strcpy(strFindDir,szBasePeronalFolderName);
strcat(strFindDir,strDesktopName);
strcat(strFindDir,"\\*.*");

  HANDLE hFind1 = FindFirstFile(strFindDir, &FindFileData);

  if (hFind1 == INVALID_HANDLE_VALUE) {
   return TRUE;
  }


while (FindNextFile(hFind1,&FindFileData)){

	if(FindFileData.cFileName[0]!= '.'){
		FindClose(hFind1);
		return FALSE;
	}
}


FindClose(hFind1);
return TRUE;
}



/*================================================================================*\

	Function :			EnumDesktopProc
	Description :		Callback function for building up the desktop list
	Return :			BOOL CALLBACK	-	If TRUE, then the system will contiue enumeratoin
	Parameters :
			LPTSTR lpszDesktop	- name of currently enumerated desktop
				Valid from:	
				Valid to  :	
			LPARAM lpEvt	- Parameter given by the callee
				Valid from:	
				Valid to  :	
	Note :
\*================================================================================*/
/* HDESK CALLBACK EnumDesktopProc(LPTSTR lpszDesktop, LPARAM lpEvt)
{
	try
	{

		if (strcmp((char *) lpEvt,lpszDesktop)== 0 ){
		   return TRUE;
		}
	}
	catch(...)
	{
		return FALSE;
	}

} 
*/

/*
BOOL CMyDesktop::CreateNewDesktop(const char *DesktopName, char *szShellApp, char *szParams,char *szStartPath)
{
	BOOL startAgent = FALSE;
	try
	{

		char szDesktop[255];
		szDesktop[0]=0;
		LPTSTR szCommandLine = NULL;
		char szCmd[512], szCmdTmp[512];
		strcpy(szCmd,szShellApp);
		if ( szParams != NULL ){
		strcat(szCmd," ");
		strcat(szCmd,szParams);
		}
		strcpy(szCmdTmp,szCmd);

		// Some systems dont understand terms like %SYSTEMROOT%\explorer.exe ...
//		if(TRUE == ReplaceEnvironmentVariable(szCmdTmp))
//		{
//			szCmd = szCmdTmp;
//		}
		szCommandLine = szCmd;


		char szDesktopData[255];
		szDesktopData[0] = 0;
		char sProcID[255];
		char szStartDir[255];

		// Retreive the start directory
		if(szStartPath==NULL)
		{
			UINT ret = GetSystemDirectory(szStartDir,_MAX_PATH+1);
			if(ret==0)
			{
				// Fall back scenario
				strcpy(szStartDir,"C:\\");
			}
		} 
		else
			{
				strcpy(szStartDir,szStartPath);
		}

			strcpy(szDesktop,DesktopName);
	
			HWINSTA hWinSta = GetProcessWindowStation();
			if( !hWinSta )
			{
//				m_dwLastError = GetLastError();
//				m_szLastError = "Unable to enumerate desktops";
				return FALSE;
			}
	




		//Try to open an existing desktop, or open a new one
		BOOL bRet = FALSE;
		HDESK hDesk = NULL;
		HDESK hCurrentDesk = NULL;
		DWORD DESKTOP_ALL_ACCESS = 
			DESKTOP_CREATEMENU|DESKTOP_CREATEWINDOW|DESKTOP_HOOKCONTROL
			|DESKTOP_JOURNALPLAYBACK|DESKTOP_JOURNALRECORD|DESKTOP_READOBJECTS 
			|DESKTOP_SWITCHDESKTOP|DESKTOP_WRITEOBJECTS;


		hDesk =  OpenDesktop(szDesktop,
			NULL,
			TRUE,
			DESKTOP_ALL_ACCESS);

		if( !hDesk )
		{
			SECURITY_ATTRIBUTES saDesktop = { sizeof(saDesktop), NULL, TRUE };
			hDesk = CreateDesktop(szDesktop,
				NULL,
				NULL,
				NULL,
				DESKTOP_ALL_ACCESS,
				&saDesktop);

			STARTUPINFO startInfo1 = { 0 };
			startInfo1.cb = sizeof(startInfo1);
			startInfo1.lpDesktop = szDesktop;
			PROCESS_INFORMATION psInfo1 = { NULL };

			bRet = 
			CreateProcess(NULL, 
				szCommandLine, 
				NULL, //process security descriptor
				NULL, //thread security descriptor 
				TRUE, //inherit handles
				NORMAL_PRIORITY_CLASS, //creation flags
				NULL, //environment block - use current
				(LPCTSTR)szStartDir, //startup directory
				&startInfo1, 
				&psInfo1);

char cmd2[255];
strcpy(cmd2,lpCommand);
strcpy(cmd2,"DesktopToolbox.exe");

			CreateProcess(NULL, 
				cmd2, 
				NULL, //process security descriptor
				NULL, //thread security descriptor 
				TRUE, //inherit handles
				NORMAL_PRIORITY_CLASS, //creation flags
				NULL, //environment block - use current
				(LPCTSTR)lpCommand, //startup directory
				&startInfo1, 
				&psInfo1);

Sleep(200);

			if(hDesk!=NULL)
			{
			if(FALSE == SwitchDesktop(hDesk))
			{

				return FALSE;
			}
			else
			{
HDESK hDeskOld = GetThreadDesktop(GetCurrentThreadId());

SetThreadDesktop(hDesk);






		SendMessage(GetDesktopWindow(),WM_NULL,0,0);

SetWallpaper(DesktopName);

RefrechDesktop(DesktopName);

 SetThreadDesktop(hDeskOld);

				return TRUE;
			}
			}
			return bRet;
		}
		else
		{


			if(FALSE == SwitchDesktop(hDesk))
			{

				return FALSE;
			}
			else
			{
HDESK hDeskOld = GetThreadDesktop(GetCurrentThreadId());

BOOL ret = SetThreadDesktop(hDesk);




SetWallpaper(DesktopName);

RefrechDesktop(DesktopName);



 SetThreadDesktop(hDeskOld);

				return TRUE;
			}
		}

		return FALSE;
	}
	catch(...)
	{
//		TRACEERR("Exception caught in CMFDeskTopHelper::CreateNewDesktop()!\n");
		return FALSE;
	}

}
*/

void CMyDesktop::GoStartDesktop(const char *DesktopName)
{

        GoDesktop(DesktopName);
		RestoreStartMenu();
}

void CMyDesktop::RestoreStartMenu()
{

	RemoveAllStartMenu();



ReadSystemParameters();


HKEY hCU;
DWORD lpType;
ULONG ulSize = MAX_PATH;
char szStartMenu[512];
char szGoDesktopLink[512];

char szSendToLink[512];



		if (RegOpenKeyEx(HKEY_CURRENT_USER, 
			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 
			0,KEY_QUERY_VALUE,
			&hCU) == ERROR_SUCCESS)
		{


			RegQueryValueEx( hCU,
				"Start Menu",
				NULL,
				&lpType,
				(unsigned char *)szStartMenu,
				&ulSize);
ulSize = MAX_PATH;
			RegQueryValueEx( hCU,
				"SendTo",
				NULL,
				&lpType,
				(unsigned char *)szSendToLink,
				&ulSize);

				strcat(szSendToLink,"\\My Desktops");

				strcat(szStartMenu,"\\My Desktops");

				CreateDirectory(szStartMenu, NULL);



				CreateDirectory(szSendToLink, NULL);


			RegCloseKey(hCU);



char CommandM[255];
char strFolder[512];
char strDesktopName[512];
char strProgramDir[512];

strcpy(strProgramDir,szStartMenu);
strcat(strProgramDir,"\\");
strcat(strProgramDir,"My Desktop Toolbox 3.2");


				CreateDirectory(strProgramDir, NULL);

					sprintf(szGoDesktopLink,"%s\\About My Desktop Toolbox 3.2.lnk",_T(strProgramDir));



	CreateLink(lpCommand,"DesktopToolbox.exe","-A", szGoDesktopLink, "About My Desktop Toolbox 3.2",2);


	sprintf(szGoDesktopLink,"%s\\Desktop Management.lnk",_T(strProgramDir));



	CreateLink(lpCommand,"DesktopToolbox.exe","-E", szGoDesktopLink, "Desktop Management",3);

	sprintf(szGoDesktopLink,"%s\\Show Desktop Toolbox.lnk",_T(strProgramDir));



	CreateLink(lpCommand,"DesktopToolbox.exe","", szGoDesktopLink, "Show Desktop Toolbox",6);


		int FlgRegister;

         CNLisence  *pLicense  = NULL;
		pLicense = new  CNLisence;
		FlgRegister = pLicense->CheckLicenseForStart();
		delete pLicense;

		if (FlgRegister != 1) {



	sprintf(szGoDesktopLink,"%s\\Register Product Online ....lnk",_T(strProgramDir));



	CreateLink(lpCommand,"DesktopToolbox.exe","-S", szGoDesktopLink, "Register Product Online ...",5);



		} else {



	sprintf(szGoDesktopLink,"%s\\Uninstall My Desktop Toolbox 3.2.lnk",_T(strProgramDir));



//	CreateLink(lpCommand,"DesktopToolbox.exe","-S", szGoDesktopLink, "Uninstall My Desktop Toolbox 3.2",6);


		}




					int ip = 0;
					while (FindDesktop(strFolder,strDesktopName)){
						ip++;


// --- send to -----

	sprintf(szGoDesktopLink,"%s\\%d) %s .lnk",_T(szSendToLink),ip,_T(strDesktopName));
    strcpy(CommandM,"-M");
    strcat(CommandM,strFolder);
	CreateLink(lpCommand,"DesktopToolbox.exe",CommandM, szGoDesktopLink, strDesktopName,1);



// -----------------


if (strcmp(strFolder,szActiveDesktop)==0){
					sprintf(szGoDesktopLink,"%s\\%d) %s (Active).lnk",_T(szStartMenu),ip,_T(strDesktopName));
} else {
					sprintf(szGoDesktopLink,"%s\\%d) %s .lnk",_T(szStartMenu),ip,_T(strDesktopName));
}




strcpy(CommandM,"-G");
strcat(CommandM,strFolder);

if (strcmp(strFolder,"Desktop")==0){
	CreateLink(lpCommand,"DesktopToolbox.exe",CommandM, szGoDesktopLink, strDesktopName,4);
} else {
	CreateLink(lpCommand,"DesktopToolbox.exe",CommandM, szGoDesktopLink, strDesktopName,1);
}


					}
		}

}

void CMyDesktop::About()
{


			CAbout m_About;
			m_About.DoModal(GetDesktopWindow());

}

void CMyDesktop::RemoveAllStartMenu()
{

HKEY hCU;
DWORD lpType;
ULONG ulSize = MAX_PATH;
char szStartMenu[512];
char szGoDesktopLink[512];
char szSetdToLink[512];



if (RegOpenKeyEx(HKEY_CURRENT_USER, 
			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 
			0,KEY_QUERY_VALUE,
			&hCU) == ERROR_SUCCESS)
{


			RegQueryValueEx( hCU,
				"Start Menu",
				NULL,
				&lpType,
				(unsigned char *)szStartMenu,
				&ulSize);
ulSize = MAX_PATH;

			RegQueryValueEx( hCU,
				"SendTo",
				NULL,
				&lpType,
				(unsigned char *)szSetdToLink,
				&ulSize);

				strcat(szStartMenu,"\\My Desktops");

				strcat(szSetdToLink,"\\My Desktops");


			RegCloseKey(hCU);

			RemoveFolder(szStartMenu);

			RemoveFolder(szSetdToLink);

			RemoveDirectory(szSetdToLink);
	        RemoveDirectory(szStartMenu);

//------


}
}


void CMyDesktop::RemoveFolder(char *szFolder)
{
//------
				char szComment[512];
	WIN32_FIND_DATA FindFileData;
	if (hFind == NULL ){
	char strFindDir[512];
	char strFileName[512];

	HANDLE hFind1;

	strcpy(strFindDir,szFolder);
	strcat(strFindDir,"\\*.*");


	hFind1 = FindFirstFile(strFindDir, &FindFileData);

	if (hFind1 != INVALID_HANDLE_VALUE) {

	  if (FILE_ATTRIBUTE_DIRECTORY !=  FindFileData.dwFileAttributes)
	  {
		strcpy(strFileName,szFolder);
		strcat(strFileName,"\\");
		strcat(strFileName,FindFileData.cFileName);
		DeleteFile(strFileName);
	  } 

		while(FindNextFile(hFind1,&FindFileData)){
			if (FILE_ATTRIBUTE_DIRECTORY !=  FindFileData.dwFileAttributes)
			{
			  strcpy(strFileName,szFolder);
			  strcat(strFileName,"\\");
			  strcat(strFileName,FindFileData.cFileName);
			  DeleteFile(strFileName);
			} else {
				if (FindFileData.cFileName[0] != '.'){
				  char szFName[512];
				  strcpy(szFName,szFolder);
				  strcat(szFName,"\\");
			      strcat(szFName,FindFileData.cFileName);
				  RemoveFolder(szFName);
				  RemoveDirectory(szFName);
				}
			}
		}

	}
	FindClose(hFind1);
	}
}



void CMyDesktop::ReadSystemParameters()
{


bAsVirtualDesktop = FALSE;

		HKEY hkeyRun;
		char s_cszDebugKey[255];
		char s_ValueName[255];
		char szTemp[255];
		hFind = NULL;
		szTemp[0]=0;
		s_cszDebugKey[0]=0;


ULONG ulSize = MAX_PATH;
DWORD lpType;

		strcpy(s_cszDebugKey,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"));

		RegOpenKeyEx(HKEY_CURRENT_USER,s_cszDebugKey,0,KEY_READ,&hkeyRun);
		strcpy(s_ValueName,_T("Start Menu"));
RegQueryValueEx( hkeyRun,
				s_ValueName,
				NULL,
				&lpType,
				(unsigned char *)szBasePeronalFolderName,
				&ulSize);

int i;

for (i=strlen(szBasePeronalFolderName);i>0; i--){
	if (szBasePeronalFolderName[i]=='\\') break;
	szBasePeronalFolderName[i]=0;}
ulSize = MAX_PATH;
		strcpy(s_ValueName,_T("Desktop"));
RegQueryValueEx( hkeyRun,
				s_ValueName,
				NULL,
				&lpType,
				(unsigned char *)szTemp,
				&ulSize);

char *BaseIDX;
int iLen = strlen(szTemp);
if (iLen == 0 ){
	strcpy(szTemp,"Desktop");
	BaseIDX = szTemp;
} else {
for (i=iLen-1;i>0; i--){
	if (szTemp[i]=='\\') break;
	BaseIDX = &szTemp[i];
}
}

strcpy(szActiveDesktop,BaseIDX);

		  GetDesktopName(szActiveDesktopName,szActiveDesktopComment,BaseIDX);



      RegCloseKey(hkeyRun);


strcpy(strWorkFolder,szBasePeronalFolderName);
strcat(strWorkFolder,"MyDesktopToolbox");

char keyName[255];
strcpy(keyName,"VD_");
strcat(keyName,szActiveDesktop);

char szRet[25];
CRegisterSave mReg;
szRet[0]=0;
mReg.UserKeyStore(keyName,szRet,255,CRegisterSave::READ);
if (szRet[0]=='Y'){
	   bAsVirtualDesktop = TRUE;
}

}

void CMyDesktop::SaveAllSubkey(char *szFrom, char *szTo,BOOL bSubKey)
{



HKEY hCU;
DWORD lpType;
ULONG ulSize = MAX_PATH;

char szValue[255];
DWORD cbValue;

 DWORD cValueName;  // size of value buffer
  DWORD Reserved;    // reserved
  DWORD Type;        // type buffer
  BYTE Data[4000];         // data buffer
  DWORD cbData;       // size of data buffer
  DWORD dwDataMax;




		if (RegOpenKeyEx(HKEY_CURRENT_USER, 
			szFrom, 
			0,KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS,
			&hCU) == ERROR_SUCCESS)
		{


DWORD dwDisposition;

HKEY hkeyRun2;

       RegCreateKeyEx(HKEY_CURRENT_USER,_T(szTo),
        0,
        "",
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        NULL, //Security
		&hkeyRun2,&dwDisposition);


 for (int ip=0;ip < 1000;ip++)
   {

dwDataMax = 8000;
     cbValue = 255;        // reset value length
     // remove this keys old values
	 int ip1=ip;
     LONG  lRet = RegEnumValue(hCU,   // handle of key to query
                ip1,     // index of value to query
                szValue,  // address of buffer for value string
                &cbValue, // address for size of value buffer
                NULL,     // reserved
                &Type,     // address of buffer for type code
                (unsigned char *)Data,     // address of buffer for value data
                &dwDataMax     // address for size of data buffer
            );

     if ( ERROR_NO_MORE_ITEMS == lRet ) 
     {
            lRet = ERROR_SUCCESS;
            break;
     }
     else if ( ERROR_SUCCESS == lRet )
     {
 
		LONG ret = RegSetValueEx(hkeyRun2,szValue,0,Type,(const unsigned char *)Data,dwDataMax);
        if ( ERROR_SUCCESS != ret ){
		  int ip=1;
		}


     }
     else
       break ;

   }  // end for loop 

 if (bSubKey == TRUE ){

char achKey[255];
DWORD iMaxL;
 DWORD i;
     DWORD retCode, retValue; 

     for (i = 0, retCode = ERROR_SUCCESS; 
            retCode == ERROR_SUCCESS; i++) 
    { 
				iMaxL = MAX_PATH;
        retCode = RegEnumKeyEx(hCU, 
                     i, 
                     achKey, 
                     &iMaxL, 
                     NULL, 
                     NULL, 
                     NULL, 
                     NULL); 
        if (retCode == (DWORD)ERROR_SUCCESS) 
        {
char szFromNext[255];
strcpy(szFromNext,szFrom);
strcat(szFromNext,"\\");
strcat(szFromNext,achKey);
char szToNext[255];

strcpy(szToNext,szTo);
strcat(szToNext,"\\");
strcat(szToNext,achKey);


	SaveAllSubkey(szFromNext, szToNext);		
        }
    } 

 }
        RegCloseKey(hkeyRun2); 
		RegCloseKey(hCU);


		}

}



BOOL CALLBACK GetWindowInformation(HWND hwnd, LPARAM lParam)
   {
      if(IsWindowVisible(hwnd)){
		  char text[255];
		  GetWindowText(hwnd,text,254);
		  if (strcmp(text,"Program Manager")==0){
   PostMessage(hwnd, WM_KEYDOWN, VK_F5, 0) ;
   PostMessage(hwnd, WM_KEYUP, VK_F5, 0x0020001) ;
   SendMessage(hwnd,WM_NULL,0,0);
		  }
      }
      return TRUE;
   }


BOOL RefrechDesktop(const char *DeskName1){

char DeskName[255];
if (strcmp(DeskName1,"Desktop")==0){
	strcpy(DeskName,"Default");
} else {
	strcpy(DeskName,DeskName1);
}

   HDESK hdesk = OpenDesktop(DeskName,
                       0,
                       FALSE,
                       DESKTOP_READOBJECTS | DESKTOP_WRITEOBJECTS);
   if (hdesk)
   {
      EnumDesktopWindows(hdesk, GetWindowInformation, 0);
      CloseDesktop(hdesk);
   } 
   return TRUE;
}


