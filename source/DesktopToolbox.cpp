// DesktopToolbox.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f DesktopToolboxps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "DesktopToolbox.h"
#include "MainWindow.h"
#include "ToolBox.h"
#include "MyMenu.h"
#include <shlobj.h>
#include "About.h"

#include "About25.h"
#include "CopyMessage.h"
#include "Psapi.h"
#include "Winbase.h"
#include <shlguid.h>



int gbl_FlgRegister;


// Variables shared across all instances of our application which ensure
// that only one instance of this application  will run at a given time.
#pragma data_seg("Shared")
 static LONG g_lInstanceCount = -1;
#pragma data_seg()

#pragma data_seg(".drectve")
 static char szShared[] = "-section:Shared,rws";
#pragma data_seg()


      static char szLink[MAX_PATH];
	  static char szProgLink[MAX_PATH];
	  char strFileLink[MAX_PATH];
	  char lpCommand[255];
  char *szDesc = "My Desktop Toolbox V3.2";
  char g_szAppName[] = "My Desktop Toolbox V3.2";

  char fileNameDictionary[255];

#include "DesktopToolbox_i.c"


#define IDI_DISPRES                     103
#define UM_DISPRESICONNOTIFY     (WM_USER + 100)



HWND g_MainWindow = NULL;

HWND g_ToolboxWindow = NULL;

HANDLE threadDDToolbar = NULL;


DWORD threadIDToolBar = NULL;


HRESULT CreateLink(LPCSTR lpszPathObj,LPCSTR lpszExe,LPCSTR lpszParameters, 
    LPCSTR lpszPathLink, LPCSTR lpszDesc,int iconIdx=0) 
{ 
    HRESULT hres; 
    IShellLink* psl; 
	char strFullName[512];
 
    // Get a pointer to the IShellLink interface. 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, 
        CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl); 
    if (SUCCEEDED(hres)) { 
        IPersistFile* ppf; 
 
        // Set the path to the shortcut target and add the 
        // description.
		strcpy(strFullName,lpszPathObj);
		if (strFullName[strlen(strFullName)-1]!='\\')
		     strcat(strFullName,"\\");
		strcat(strFullName,lpszExe);





        psl->SetPath(strFullName); 
		psl->SetWorkingDirectory(lpszPathObj);
        psl->SetDescription(lpszDesc); 
		psl->SetArguments(lpszParameters);
		if (iconIdx > 0 ){
		   psl->SetIconLocation(strFullName, iconIdx);
		}
 
       // Query IShellLink for the IPersistFile interface for saving the 
       // shortcut in persistent storage. 
        hres = psl->QueryInterface(IID_IPersistFile, 
            (LPVOID*)&ppf); 
 
        if (SUCCEEDED(hres)) { 
            WCHAR wsz[MAX_PATH]; 
 
            // Ensure that the string is Unicode. 
            MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, 
                wsz, MAX_PATH); 
 
            // Save the link by calling IPersistFile::Save. 
            hres = ppf->Save(wsz, TRUE); 
            ppf->Release(); 
        } 
        psl->Release(); 
    } 
    return hres; 
} 



const DWORD dwTimeOut = 5000; // time for EXE to be idle before shutting down
const DWORD dwPause = 1000; // time to wait for threads to finish up



   VOID ThreadFuncToolBar(LPVOID){
	   CToolBox m_Toolbox;
	   m_Toolbox.DoModal(g_MainWindow); 	
   }


LRESULT  DispRes_OnActivate (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify ){
		if (hwndCtl == WA_INACTIVE ){
			::ShowWindow(hwnd, SW_HIDE);
		}
		return 0;
}

void DispRes_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {
      case IDOK:
      case IDCANCEL:
         ShowWindow(hwnd, SW_HIDE);
         break;
   }
}







BOOL WINAPI DispRes_WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {




   switch (uMsg) {



        case WM_INITDIALOG:
            {
   NOTIFYICONDATA nid;
   nid.cbSize = sizeof(nid);
   nid.hWnd = hwnd;        
   nid.uID = IDI_DISPRES;   
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.uCallbackMessage = UM_DISPRESICONNOTIFY;
   nid.hIcon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_TASK_ICON));
   lstrcpyn(nid.szTip, "My Desktop Toolbox", sizeof(nid.szTip) / sizeof(nid.szTip[0]));
   Shell_NotifyIcon(NIM_ADD, &nid);
   SendMessage(hwnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) nid.hIcon);
			}
			break;

        case WM_DESTROY:
            {
   NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = IDI_DISPRES;
	Shell_NotifyIcon(NIM_DELETE, &nid);
	               PostQuitMessage(1);
			}
			break;

        case WM_COMMAND:
            {
   switch ((UINT)wParam) {

      case IDOK:
      case IDCANCEL:
         ShowWindow(hwnd, SW_HIDE);
         break;
   }
			}
			break;

        case WM_ACTIVATE:
            {
			::ShowWindow(hwnd, SW_HIDE);
			}
			break;

   }
      return(FALSE);
}

// Passed to CreateThread to monitor the shutdown event
static DWORD WINAPI MonitorProc(void* pv)
{
    CExeModule* p = (CExeModule*)pv;
    p->MonitorShutdown();
    return 0;
}

LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        bActivity = true;
        SetEvent(hEventShutdown); // tell monitor that we transitioned to zero
    }
    return l;
}

//Monitors the shutdown event
void CExeModule::MonitorShutdown()
{
    while (1)
    {
        WaitForSingleObject(hEventShutdown, INFINITE);
        DWORD dwWait=0;
        do
        {
            bActivity = false;
            dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
        } while (dwWait == WAIT_OBJECT_0);
        // timed out
        if (!bActivity && m_nLockCnt == 0) // if no activity let's really bail
        {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
            CoSuspendClassObjects();
            if (!bActivity && m_nLockCnt == 0)
#endif
                break;
        }
    }
    CloseHandle(hEventShutdown);
    PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
    hEventShutdown = CreateEvent(NULL, false, false, NULL);
    if (hEventShutdown == NULL)
        return false;
    DWORD dwThreadID;
    HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
    return (h != NULL);
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)

END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}




int lastIndexOf( const   char* const     toSearch
                            , const char            ch
                            , const unsigned int    fromIndex
                            )
{
    const int len = strlen(toSearch);


    for (int i = (int)fromIndex; i >= 0; i--)
    {
        if (toSearch[i] == ch)
            return i;
    }
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
//


extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE , LPTSTR lpCmdLine, int )
{





    lpCmdLine = GetCommandLine(); 

	// & defined(_ATL_FREE_THREADED)

//#if _WIN32_WINNT >= 0x0400 
//    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
// #else
    HRESULT hRes = CoInitialize(NULL);
//#endif


    LPTSTR lpCmdLine1;
    lpCmdLine1 = GetCommandLine(); 
	strcpy(szLink,lpCmdLine1);


//	if (lpCmdLine1[0] == '"') {strcpy(lpCommand,lpCmdLine+1);}
//	else {strcpy(lpCommand,lpCmdLine1);}

	int l = lastIndexOf(lpCmdLine1,'\\',strlen(lpCmdLine1));
	int l2 = lastIndexOf(lpCmdLine1,'"',strlen(lpCmdLine1));
	if (l2 < 0 ) l2=strlen(lpCmdLine1)+1;
	
	char taskName[100];
	strncpy(taskName,&lpCmdLine1[l+1],l2-l);
	taskName[l2-l-1] =0;

	int nSize = 255;
	char szProcessName[255];
	szProcessName[0]=0;


	HANDLE hProcess1 = GetCurrentProcess();

	        HMODULE hMod;
        DWORD cbNeeded;

    EnumProcessModules( hProcess1, &hMod, sizeof(hMod), 
             &cbNeeded);
	GetModuleFileNameExA(hProcess1, hMod, szProcessName, nSize);

	strcpy(lpCommand,szProcessName);


	for (int lp = strlen(lpCommand)-1; lp >=0; lp--){
	  lpCommand[lp]=0; 
	  if (lpCommand[lp-1]=='\\') break;
	  if (lpCommand[lp-1]==':') break;
	}


    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_DESKTOPTOOLBOXLib);
    _Module.dwThreadID = GetCurrentThreadId();
    TCHAR szTokens[] = _T("-/");

    int nRet = 0;
    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_DesktopToolbox, FALSE);
            nRet = _Module.UnregisterServer(TRUE);
            bRun = FALSE;
            break;
        }

        if (lpszToken[0] == 'G')
        {

            break;
        }

        if (lpszToken[0] == 'A')
        {

            CAbout m_About;
			m_About.DoModal(GetDesktopWindow());
            bRun = FALSE;
            break;
        }






        if (lpszToken[0] == 'S')
        {

            CAbout25 m_About25;
			m_About25.DoModal(GetDesktopWindow());
								Sleep(5000);
            bRun = FALSE;
            break;
        }


        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_DesktopToolbox, TRUE);
            nRet = _Module.RegisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    if (bRun)
    {


		HWND old = ::FindWindow(NULL,CToolBox::strMyDesktopTollboxMainWindow);

     CMenuOperation::Initialize();
		if (old != NULL){
      MessageBox(NULL, __TEXT("The My Desktop Toolbox V3.2 is already running"), 
         g_szAppName, MB_ICONINFORMATION | MB_OK);

   } else {

        _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hRes = CoResumeClassObjects();
#else
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hRes));




DWORD dwDisposition;
HKEY hkeyRun2;

       RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\NVR Soft\\MyDesktopToolbox"),
        0,
        "",
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        NULL, //Security
		&hkeyRun2,&dwDisposition);
        RegCloseKey(hkeyRun2); 

//----------------------

HKEY hCU;
DWORD lpType;
ULONG ulSize = MAX_PATH;



		if (RegOpenKeyEx(HKEY_CURRENT_USER, 
			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 
			0,KEY_QUERY_VALUE,
			&hCU) == ERROR_SUCCESS)
		{
			RegQueryValueEx( hCU,
				"Startup",
				NULL,
				&lpType,
				(unsigned char *)szLink,
				&ulSize);


ulSize = MAX_PATH;
			RegQueryValueEx( hCU,
				"Personal",
				NULL,
				&lpType,
				(unsigned char *)CMyMenu::szMyDesktopToolbarFolder,
				&ulSize);
//				strcat(CMyMenu::szMyDesktopToolbarFolder,"\\My Tools");

//				CreateDirectory(CMyMenu::szMyDesktopToolbarFolder, NULL);




			RegCloseKey(hCU);





	        strcpy(strFileLink,szLink);
	        strcat(strFileLink,"\\");
	        strcat(strFileLink,szDesc);
	        strcat(strFileLink,".lnk");

	CreateLink(lpCommand,taskName,"", strFileLink, szDesc);

		}


DWORD dwVersion = GetVersion();
 

if (dwVersion >= 0x80000000)                
{
       RegCreateKeyEx(HKEY_CURRENT_USER,_T("Environment"),
        0,
        "",
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        NULL, //Security
		&hkeyRun2,&dwDisposition);
        RegCloseKey(hkeyRun2); 
}


//----------------------




//      g_MainWindow = CreateDialog(_Module.GetModuleInstance(), "IDD_MAINWINDOW", 
//         NULL, DispRes_WndProc);


//	        threadDDToolbar = CreateThread(0, 0,(LPTHREAD_START_ROUTINE) ThreadFuncToolBar,
//                    0, 0, &threadIDToolBar);


	   CToolBox m_Toolbox;
	   m_Toolbox.DoModal(g_MainWindow); 	
			


        _Module.RevokeClassObjects();
        Sleep(dwPause); 
    }
	




}
    _Module.Term();
    CoUninitialize();
    return nRet;
}

