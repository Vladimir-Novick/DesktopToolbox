// MyDesktop.h: interface for the CMyDesktop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDESKTOP_H__9BC0C358_95D1_449D_BC50_4DDA9280CA56__INCLUDED_)
#define AFX_MYDESKTOP_H__9BC0C358_95D1_449D_BC50_4DDA9280CA56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDesktop  
{
public:
	void SaveAllSubkey(char *szFrom,char *szTo,BOOL bSubKey=TRUE);
BOOL CreateNewDesktop(const char *DesktopName, char *szShellApp, char *szParams=NULL,char *szStartDir=NULL);
	void GetWallpaper(char *FileName,char *Desktop);
	void ReadSystemParameters(void);
	void RemoveFolder(char *szFolder);
	void RemoveAllStartMenu(void);
	void About();
	void RestoreStartMenu();
	void GoStartDesktop(const char *DesktopName);
	BOOL IsDesktopEmpty(char *strDesktopName);
	void DeleteCurrentDestop(void);
	void NewDesktop(char *szName,char *szComment);
void CMyDesktop::SetDesktopName(char *szName,char *szComment, const char *szDesktopName);
	void GetDesktopName(char *szName,char *szComment, const char *szDesktopName);
	BOOL FindDesktop(char *strFolder,char *strDesktopName);
	CMyDesktop();
	virtual ~CMyDesktop();
void PrintProcessNameAndID( char szProcessName[MAX_PATH],DWORD processID );
BOOL ExitProcessByName(char *strProcessName);
void SetWallpaper(const char *Desktop);
void RestoreWallpaper(char *DesktopNameOld,char *DesktopNameNew);
void GoDesktop(const char *DesktopName,BOOL bMsg = TRUE);
	char szBasePeronalFolderName[255];
char szActiveDesktopName[255];
char szActiveDesktopComment[512];
char szActiveDesktop[255];
char szShell[255];
BOOL bAsVirtualDesktop;

private:

	char strWorkFolder[255];
	  HANDLE hFind;


};

#endif // !defined(AFX_MYDESKTOP_H__9BC0C358_95D1_449D_BC50_4DDA9280CA56__INCLUDED_)
