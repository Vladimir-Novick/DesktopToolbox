// NLisence.h: interface for the CNLisence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_)
#define AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNLisence  
{
public:
	BOOL SetProtectGetDate(void);
	BOOL CheckGetTempDate(void);
	void GetStartDate(char *strStart);
	void mycrypt(char *src,char *desc);
	int CheckLicenseForStart(VOID);
	int CheckLicense( char *strBuffer);
	VOID GetComputerCode(char *strBuffer);
	CNLisence();
	virtual ~CNLisence();
	BOOL CheckFullTrial();
private:

/*BOOL RegisterString (
   LPSTR pszKey, 
   LPSTR pszValue, 
   LPSTR pszData
   );
*/
/*
BOOL GetRegString (
  LPSTR pszKey,
  LPSTR pszValue,
  LPSTR pszData
  );
*/
};

#endif // !defined(AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_)
