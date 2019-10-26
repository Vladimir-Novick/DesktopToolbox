#if !defined(CNewLoadLib_H)
#define CNewLoadLib_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000






#include <atlbase.h>

#include "resource.h"

#include <atlapp.h>
//#include "MyDesktop.h"



class CNewLoadLib
{
public:

  HMODULE m_hModule;
  void* m_pProg;

  CNewLoadLib(LPCTSTR pName,LPCSTR pProgName)
  {
    m_hModule = LoadLibrary(pName);
    m_pProg = m_hModule ? (void*)GetProcAddress (m_hModule,pProgName) : NULL;
  }

  ~CNewLoadLib()
  {
    if(m_hModule)
    {
      FreeLibrary(m_hModule);
      m_hModule = NULL;
    }
  }
};


/*
BOOL GetMenuInfo( HMENU hMenu, LPMENUINFO pInfo)
{
  static CNewLoadLib menuInfo(_T("user32.dll"),"GetMenuInfo");
  if(menuInfo.m_pProg)
  {
    typedef BOOL (WINAPI* FktGetMenuInfo)(HMENU, LPMENUINFO);
    return ((FktGetMenuInfo)menuInfo.m_pProg)(hMenu,pInfo);
  }
  return FALSE;
}

BOOL SetMenuInfo( HMENU hMenu, LPCMENUINFO pInfo)
{
  static CNewLoadLib menuInfo(_T("user32.dll"),"SetMenuInfo");
  if(menuInfo.m_pProg)
  {
    typedef BOOL (WINAPI* FktSetMenuInfo)(HMENU, LPCMENUINFO);
    return ((FktSetMenuInfo)menuInfo.m_pProg)(hMenu,pInfo);
  }
  return FALSE;
}
*/

#endif