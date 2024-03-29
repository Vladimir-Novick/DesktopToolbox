//------------------------------------------------------------------------------
// File    : NewToolBar.cpp 
// Version : 1.10
// Date    : 30. November 2003
// Author  : Bruno Podetti
// Email   : Podetti@gmx.net
// Web     : www.podetti.com/NewMenu 
// Systems : VC6.0/7.0 and VC7.1 (Run under (Window 98/ME), Windows Nt 2000/XP)
//
// For bugreport please add following informations
// - The CNewToolBar version number (Example CNewToolBar 1.10)
// - Operating system Win95 / WinXP and language (English / Japanese / German etc.)
// - Intalled service packs
// - Short description how to reproduce the bug
// - Pictures/Sample are wellcome too
// - You can write in English or German to the above email-address.
// - Have my compiled examples the same effect?
//------------------------------------------------------------------------------
//
// ToDo's
// - Supporting comboboxes
// - Seperator drawing
// - Adding shade to icons
// - Correcting checked state
// - Adding text
//
// 23. November 2003 (1.10)
// - Work with Themes (manifest)
// - Expanded office 2003 look
// - Expanded ICY-Style
// - work also with 16-bit colored toolbar
//
// 12. July 2003 Version 1.0
// - Thanks to Andreas Sch�rer for some hints
// - It works with IE 4.0 and above
// - only a minimal implementation not supported all styles
// - support more than 16 colors for toolbarbitmaps
//
// You are free to use/modify this code but leave this header intact.
// This class is public domain so you are free to use it any of your 
// applications (Freeware, Shareware, Commercial). 
// All I ask is that you let me know so that if you have a real winner I can
// brag to my buddies that some of my code is in your app. I also wouldn't 
// mind if you sent me a copy of your application since I like to play with
// new stuff.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "NewToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_GRIPPER  3
#define CY_GRIPPER  3
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2

// declarations from CNewMenu
extern COLORREF DarkenColorXP(COLORREF color);
extern COLORREF DarkenColor( long lScale, COLORREF lColor);
extern COLORREF MixedColor(COLORREF colorA,COLORREF colorB);
extern COLORREF LightenColor( long lScale, COLORREF lColor);
extern COLORREF GetXpHighlightColor();

extern void DrawGradient(CDC* pDC,CRect& Rect, COLORREF StartColor,COLORREF EndColor, BOOL bHorizontal,BOOL bUseSolid=FALSE);
extern HBITMAP LoadColorBitmap(LPCTSTR lpszResourceName, HMODULE hInst, int* pNumcol);

// CNewToolBar

IMPLEMENT_DYNAMIC(CNewToolBar, CToolBar)
CNewToolBar::CNewToolBar()
{
}

CNewToolBar::~CNewToolBar()
{
}

BEGIN_MESSAGE_MAP(CNewToolBar, CToolBar)
  ON_WM_NCPAINT()
  ON_WM_ERASEBKGND()
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw) 
  ON_WM_CREATE()
  ON_WM_PAINT()
END_MESSAGE_MAP()


COLORREF CNewToolBar::MakeGrayAlphablend(CBitmap* pBitmap, int weighting, COLORREF blendcolor)
{
  CDC myDC;
  // Create a compatible bitmap to the screen
  myDC.CreateCompatibleDC(0);
  // Select the bitmap into the DC
  CBitmap* pOldBitmap = myDC.SelectObject(pBitmap);

  BITMAP myInfo = {0};
  GetObject((HGDIOBJ)pBitmap->m_hObject,sizeof(myInfo),&myInfo);

  for (int nHIndex = 0; nHIndex < myInfo.bmHeight; nHIndex++)
  {
    for (int nWIndex = 0; nWIndex < myInfo.bmWidth; nWIndex++)
    {
      COLORREF ref = myDC.GetPixel(nWIndex,nHIndex);

      // make it gray
      DWORD nAvg =  (GetRValue(ref) + GetGValue(ref) + GetBValue(ref))/3;	

      // Algorithme for alphablending
      //dest' = ((weighting * source) + ((255-weighting) * dest)) / 256
      DWORD refR = ((weighting * nAvg) + ((255-weighting) * GetRValue(blendcolor))) / 256;
      DWORD refG = ((weighting * nAvg) + ((255-weighting) * GetGValue(blendcolor))) / 256;;
      DWORD refB = ((weighting * nAvg) + ((255-weighting) * GetBValue(blendcolor))) / 256;;

      myDC.SetPixel(nWIndex,nHIndex,RGB(refR,refG,refB));
    }
  }
  COLORREF topLeftColor = myDC.GetPixel(0,0);
  myDC.SelectObject(pOldBitmap);
  return topLeftColor;
}

// CNewToolBar message handlers
void CNewToolBar::DrawGripper(CDC* pDC, const CRect& rect)
{
  // only draw the gripper if not floating and gripper is specified
  if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
  {
    // draw the gripper in the border
    if (m_dwStyle & CBRS_ORIENT_HORZ)
    {
      switch (CNewMenu::GetMenuDrawMode())
      {
      case CNewMenu::STYLE_XP:
      case CNewMenu::STYLE_XP_NOBORDER:
        {
          COLORREF col = DarkenColorXP(CNewMenu::GetMenuBarColorXP());
          CPen pen(PS_SOLID,0,col);
          CPen* pOld = pDC->SelectObject(&pen);
          for (int n=rect.top+m_cyTopBorder+2*CY_BORDER_GRIPPER;n<rect.Height()-m_cyTopBorder-m_cyBottomBorder-4*CY_BORDER_GRIPPER;n+=2)
          {
            pDC->MoveTo(rect.left+CX_BORDER_GRIPPER+2,n);
            pDC->LineTo(rect.left+CX_BORDER_GRIPPER+CX_GRIPPER+2,n);
          }
          pDC->SelectObject(pOld);
        }
        break;

      case CNewMenu::STYLE_ICY:
      case CNewMenu::STYLE_ICY_NOBORDER:
        {
          COLORREF color = DarkenColor(100,CNewMenu::GetMenuColor());
          for (int n=rect.top+m_cyTopBorder+2*CY_BORDER_GRIPPER;n<rect.Height()-m_cyTopBorder-m_cyBottomBorder-4*CY_BORDER_GRIPPER;n+=4)
          {
            //pDC->FillSolidRect(rect.left+CX_BORDER_GRIPPER+2,n  +1,2,2,color);
            pDC->FillSolidRect(rect.left+CX_BORDER_GRIPPER+2+m_cxLeftBorder,n  +1,2,2,color);
          }
           // make round corners
          color = GetSysColor(COLOR_3DLIGHT);//CNewMenu::GetMenuBarColor();
          CRect temp(rect);
          temp.InflateRect(-m_cxLeftBorder,-2,-m_cxRightBorder-1,-m_cxRightBorder);
          PaintCorner(pDC,temp,color);
       }
        break;

      case CNewMenu::STYLE_XP_2003_NOBORDER:
      case CNewMenu::STYLE_XP_2003:
        {
          COLORREF color = DarkenColor(10,GetSysColor(COLOR_ACTIVECAPTION));

          for (int n=rect.top+m_cyTopBorder+2*CY_BORDER_GRIPPER;n<rect.Height()-m_cyTopBorder-m_cyBottomBorder-4*CY_BORDER_GRIPPER;n+=4)
          {
            pDC->FillSolidRect(rect.left+CX_BORDER_GRIPPER+3+m_cxLeftBorder,n+1+1,2,2,RGB(255,255,255));
            pDC->FillSolidRect(rect.left+CX_BORDER_GRIPPER+2+m_cxLeftBorder,n  +1,2,2,color);
          }
          // make round corners
          color = CNewMenu::GetMenuBarColor2003();
          CRect temp(rect);
          temp.InflateRect(-m_cxLeftBorder,-2,-m_cxRightBorder-1,-m_cxRightBorder);
          PaintCorner(pDC,temp,color);
        }
        break;

      default:
        CToolBar::DrawGripper(pDC,rect);
        break;
      }
    }
    else
    {
      switch (CNewMenu::GetMenuDrawMode())
      {
      case CNewMenu::STYLE_XP:
      case CNewMenu::STYLE_XP_NOBORDER:
        {
          COLORREF col = DarkenColorXP(CNewMenu::GetMenuBarColorXP());
          CPen pen(PS_SOLID,0,col);
          CPen* pOld = pDC->SelectObject(&pen);
          for (int n=rect.top+m_cxLeftBorder+2*CX_BORDER_GRIPPER;n<rect.Width()-m_cxLeftBorder-m_cxRightBorder-2*CX_BORDER_GRIPPER;n+=2)
          {
            pDC->MoveTo(n,rect.top+CY_BORDER_GRIPPER+2);
            pDC->LineTo(n,rect.top+CY_BORDER_GRIPPER+CY_GRIPPER+2);
          }
          pDC->SelectObject(pOld);
        }
        break;

      case CNewMenu::STYLE_ICY:
      case CNewMenu::STYLE_ICY_NOBORDER:
        {
          COLORREF color = DarkenColor(100,CNewMenu::GetMenuColor());

          for (int n=rect.top+m_cxLeftBorder+2*CX_BORDER_GRIPPER;n<rect.Width()-m_cxRightBorder-2*CX_BORDER_GRIPPER;n+=4)
          {
            //pDC->FillSolidRect(n,  rect.top+CY_BORDER_GRIPPER+2,2,2,color);
            pDC->FillSolidRect(n,  rect.top+CY_BORDER_GRIPPER+2+m_cxLeftBorder,2,2,color);
          }
          // make the corners round
          color = GetSysColor(COLOR_3DLIGHT);//CNewMenu::GetMenuBarColor();
          CRect temp(rect);
          temp.InflateRect(-m_cxLeftBorder+1,-3,-m_cxRightBorder,-m_cxRightBorder-1);
          PaintCorner(pDC,temp,color);
        }
        break;

      case CNewMenu::STYLE_XP_2003_NOBORDER:
      case CNewMenu::STYLE_XP_2003:
        {
          COLORREF color = DarkenColor(10,GetSysColor(COLOR_ACTIVECAPTION)); 
          for (int n=rect.top+m_cxLeftBorder+2*CX_BORDER_GRIPPER;n<rect.Width()-m_cxRightBorder-2*CX_BORDER_GRIPPER;n+=4)
          {
            pDC->FillSolidRect(n+1,rect.top+CY_BORDER_GRIPPER+3+m_cxLeftBorder,2,2,RGB(255,255,255));
            pDC->FillSolidRect(n,  rect.top+CY_BORDER_GRIPPER+2+m_cxLeftBorder,2,2,color);
          }

          // make the corners round
          color = CNewMenu::GetMenuBarColor2003();
          CRect temp(rect);
          temp.InflateRect(-m_cxLeftBorder+1,-3,-m_cxRightBorder,-m_cxRightBorder-1);
          PaintCorner(pDC,temp,color);
        }
        break;

      default:
        CToolBar::DrawGripper(pDC,rect);
        break;
      }
    }
  }
}

void CNewToolBar::OnNcPaint()
{
  EraseNonClient();
}

void CNewToolBar::EraseNonClient()
{
  // get window DC that is clipped to the non-client area
  CWindowDC dc(this);
  CRect rectClient;
  GetClientRect(rectClient);
  CRect rectWindow;
  GetWindowRect(rectWindow);
  ScreenToClient(rectWindow);

  rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
  dc.ExcludeClipRect(rectClient);

  CPoint Offset = rectWindow.TopLeft();

  // draw borders in non-client area
  rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
  DrawBorders(&dc, rectWindow);

  // erase parts not drawn
  dc.IntersectClipRect(rectWindow);

  CPoint oldOffset;
  // correcting offset of the border
  if(!(m_dwStyle & CBRS_FLOATING))
  {
    oldOffset = dc.SetWindowOrg(Offset);
  }
  else
  { 
    oldOffset = dc.GetWindowOrg();
  }
  SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);

  // reset offset
  dc.SetWindowOrg(oldOffset);

  // draw gripper in non-client area
  DrawGripper(&dc, rectWindow);
}

void CNewToolBar::DrawBorders(CDC* pDC, CRect& rect)
{
  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    break;

  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
    break;

  case CNewMenu::STYLE_ICY:
  case CNewMenu::STYLE_ICY_NOBORDER:
   break;

  default:
    CToolBar::DrawBorders(pDC,rect);
    break;
  }
}

BOOL CNewToolBar::OnEraseBkgnd(CDC* pDC)
{
  BOOL bRet = true;//CToolBar::OnEraseBkgnd(pDC);

  CRect rect;
  if(m_dwStyle & CBRS_FLOATING)
  {
    GetClientRect(rect);
  }
  else
  {
    GetWindowRect(rect);
    ScreenToClient(rect);
  }

  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    {
      COLORREF menuColor = CNewMenu::GetMenuBarColorXP();
      pDC->FillSolidRect(rect,MixedColor(menuColor,GetSysColor(COLOR_WINDOW)));
    }
    break;

  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
    {
      COLORREF clrUpperColor, clrMediumColor, clrBottomColor, clrDarkLine;
      COLORREF menuColor = CNewMenu::GetMenuBarColor2003();

      // corrections from Andreas Sch�rer
      switch(menuColor)
      {
      case RGB(163,194,245)://blau
        {
          clrUpperColor = RGB(221,236,254);
          clrMediumColor = RGB(196, 219,249);
          clrBottomColor = RGB(129,169,226);
          clrDarkLine = RGB(59,97,156);
          break;
        }
      case RGB(215,215,229)://silber
        {
          clrUpperColor = RGB(243,244,250);
          clrMediumColor = RGB(225,226,236);
          clrBottomColor = RGB(153,151,181);
          clrDarkLine = RGB(124,124,148);
          break;
        }
      case RGB(218,218,170)://olivgr�n
        {
          clrUpperColor = RGB(244,247,222);
          clrMediumColor = RGB(209,222,172);
          clrBottomColor = RGB(183,198,145);
          clrDarkLine = RGB(96,128,88);
          break;
        }
      default:
        {     
          clrUpperColor = LightenColor(140,menuColor);
          clrMediumColor = LightenColor(115,menuColor);
          clrBottomColor = DarkenColor(40,menuColor);
          clrDarkLine = DarkenColor(110,menuColor);
          break;
        }
      } 

      PaintToolBarBackGnd(pDC);

      if(m_dwStyle & CBRS_ORIENT_HORZ)
      {
        CRect rcToolBar = rect;
        rcToolBar.left += m_cxLeftBorder; 
        rcToolBar.right -= m_cxRightBorder;
        rcToolBar.bottom /= 2;
        rcToolBar.top = rect.top + 2;
        DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,false);

        rcToolBar.top = rcToolBar.bottom;
        if(!(m_dwStyle & CBRS_FLOATING))
        {
          rcToolBar.bottom = rect.bottom - 2;
        }
        else
        {
          rcToolBar.bottom = rect.bottom;
        }
        DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,false);

        if(!(m_dwStyle & CBRS_FLOATING))
        {
          //GetClientRect(rect);
          CRect line(rect.left+m_cxLeftBorder,rect.bottom-3,rect.right-m_cxRightBorder,rect.bottom-2);  
          //dark line on bottom toolbar
          pDC->FillSolidRect(line,clrDarkLine);
        }
        else
        {
          CRect itemRect;
          CRect lastItemRect(0,0,0,0);
          int nCountBtn = (int)SendMessage (TB_BUTTONCOUNT, 0, 0);
          TBBUTTON tbButton;
          for(int i=0;i<nCountBtn;i++)
          {
            if (!SendMessage(TB_GETBUTTON, i, (LPARAM)&tbButton) ||
              (tbButton.fsState & TBSTATE_HIDDEN))
            { // coninue by error or hidden buttons
              continue; 
            }
            GetItemRect(i,itemRect);
            if(itemRect.top==lastItemRect.top &&
               itemRect.bottom==lastItemRect.bottom)
            {
              continue;
            }
            if((tbButton.fsStyle == TBSTYLE_SEP) && (tbButton.fsState & TBSTATE_WRAP) )
            {
              CRect rcToolBar(rect.left,lastItemRect.bottom,rect.right,itemRect.bottom);
              DrawGradient(pDC,rcToolBar,clrBottomColor,clrUpperColor,false);
            }
            else
            {
              CRect rcToolBar(rect.left,itemRect.top,rect.right,(itemRect.bottom+itemRect.top)/2);
              DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,false);

              rcToolBar.top = rcToolBar.bottom;
              rcToolBar.bottom = itemRect.bottom;
              DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,false);
            } 
            lastItemRect = itemRect;
          }
        }
      }
      else
      {
        if(!(m_dwStyle & CBRS_FLOATING))
        {
          //GetClientRect(rect);
          CRect line(rect.right-m_cxRightBorder  ,rect.top+m_cxRightBorder,
                     rect.right-m_cxRightBorder+1,rect.bottom-m_cxRightBorder);  

          //dunkler strich am unteren ende der toolbar
          pDC->FillSolidRect(line,clrDarkLine);
        }
        CRect rcToolBar = rect;
        rcToolBar.top += m_cxLeftBorder;
        rcToolBar.bottom -= m_cxRightBorder;
        rcToolBar.left += m_cxLeftBorder-1;
        rcToolBar.right /= 2;
        DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,true);
        rcToolBar.left = rcToolBar.right;
        rcToolBar.right = rect.right-m_cxRightBorder;
        DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,true);
      }
    }
    break;

  case CNewMenu::STYLE_ICY:
  case CNewMenu::STYLE_ICY_NOBORDER:
    {
      COLORREF menuColor = CNewMenu::GetMenuColor();
      COLORREF colorBack = CNewMenu::GetMenuBarColor();

      COLORREF clrUpperColor = LightenColor(60,menuColor);
      COLORREF clrMediumColor = menuColor;
      COLORREF clrBottomColor = DarkenColor(60,menuColor);
      COLORREF clrDarkLine = DarkenColor(150,menuColor);

      PaintToolBarBackGnd(pDC);
      if(m_dwStyle & CBRS_ORIENT_HORZ)
      {
        CRect rcToolBar = rect;
        rcToolBar.left += m_cxLeftBorder; 
        rcToolBar.right -= m_cxRightBorder;
        rcToolBar.bottom /= 2;
        rcToolBar.top = rect.top + 2;
        DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,false);

        rcToolBar.top = rcToolBar.bottom;
         if(!(m_dwStyle & CBRS_FLOATING))
        {
          rcToolBar.bottom = rect.bottom - 2;
        }
        else
        {
          rcToolBar.bottom = rect.bottom;
        }
        DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,false);

        if(!(m_dwStyle & CBRS_FLOATING))
        {
          CRect topLine(rect.left+m_cxLeftBorder,rect.top+m_cyTopBorder+1,
                        rect.right-m_cxRightBorder,rect.top+m_cyTopBorder+2);
          pDC->FillSolidRect(topLine,LightenColor(125,menuColor));

          CRect line(rect.left+m_cxLeftBorder,rect.bottom-3,rect.right-m_cxRightBorder,rect.bottom-2);  
          //dark line on bottom toolbar
          pDC->FillSolidRect(line,clrDarkLine);
        }
        else
        {
          CRect itemRect;
          CRect lastItemRect(0,0,0,0);
          int nCountBtn = (int)SendMessage (TB_BUTTONCOUNT, 0, 0);
          TBBUTTON tbButton;
          for(int i=0;i<nCountBtn;i++)
          {
            if (!SendMessage(TB_GETBUTTON, i, (LPARAM)&tbButton) ||
              (tbButton.fsState & TBSTATE_HIDDEN))
            { // coninue by error or hidden buttons
              continue; 
            }
            GetItemRect(i,itemRect);
            if(itemRect.top==lastItemRect.top &&
               itemRect.bottom==lastItemRect.bottom)
            {
              continue;
            }
            if((tbButton.fsStyle == TBSTYLE_SEP) && (tbButton.fsState & TBSTATE_WRAP) )
            {
              CRect rcToolBar(rect.left,lastItemRect.bottom,rect.right,itemRect.bottom);

              DrawGradient(pDC,rcToolBar,clrBottomColor,clrUpperColor,false);
            }
            else
            {
              CRect rcToolBar(rect.left,itemRect.top,rect.right,(itemRect.bottom+itemRect.top)/2);

              DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,false);

              rcToolBar.top = rcToolBar.bottom;
              rcToolBar.bottom = itemRect.bottom;
              DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,false);
            } 
            lastItemRect = itemRect;
          }
        }
      }
      else
      {
        if(!(m_dwStyle & CBRS_FLOATING))
        {
          CRect topLine(rect.left+m_cxLeftBorder-1,rect.top+m_cxRightBorder,
                        rect.left+m_cxLeftBorder  ,rect.bottom-m_cxRightBorder);  
          pDC->FillSolidRect(topLine,LightenColor(125,menuColor));

          CRect line(rect.right-m_cxRightBorder  ,rect.top+m_cxRightBorder,
                     rect.right-m_cxRightBorder+1,rect.bottom-m_cxRightBorder);  

          //dunkler strich am unteren ende der toolbar
          pDC->FillSolidRect(line,clrDarkLine);
        }
        CRect rcToolBar = rect;
        rcToolBar.top += m_cxLeftBorder;
        rcToolBar.bottom -= m_cxRightBorder;
        rcToolBar.left += m_cxLeftBorder;
        rcToolBar.right /= 2;
        DrawGradient(pDC,rcToolBar,clrUpperColor,clrMediumColor,true);
        rcToolBar.left = rcToolBar.right;
        rcToolBar.right = rect.right-m_cxRightBorder;
        DrawGradient(pDC,rcToolBar,clrMediumColor,clrBottomColor,true);
      }
    }
    break;

  default:
    {
      pDC->FillSolidRect(rect,GetSysColor(COLOR_3DLIGHT));
    }
    break;
  }
  return bRet;
}

BOOL CNewToolBar::LoadHiColor(LPCTSTR lpszResourceName,COLORREF transparentColor/*=CLR_DEFAULT*/)
{
  int nColors = 0;
  HBITMAP hBitmap = LoadColorBitmap(lpszResourceName,0, &nColors);
  if(hBitmap!=NULL)
  {
    //if(nColors>16)
    {
      CBitmap bitmap;
      bitmap.Attach(hBitmap);

      // Get the color of the top/lef corner
      if(transparentColor==CLR_DEFAULT)
      {
        CDC memDC;
        memDC.CreateCompatibleDC(0);
        CBitmap* pOld = memDC.SelectObject(&bitmap);
        transparentColor = memDC.GetPixel(0,0);
        memDC.SelectObject(pOld);
      }

      if(m_ImageList.GetSafeHandle())
      {
        m_ImageList.DeleteImageList();
      }
      m_ImageList.Create(m_sizeImage.cx,m_sizeImage.cy,ILC_COLORDDB|ILC_MASK,0,10); 
      m_ImageList.Add(&bitmap,transparentColor);

      // todo must the returned handle to be destroyed?? I do not know
      SendMessage(TB_SETIMAGELIST, 0, (LPARAM)m_ImageList.m_hImageList);
      
      COLORREF transparentColor;
      switch (CNewMenu::GetMenuDrawMode())
      {
      case CNewMenu::STYLE_XP_2003:
      case CNewMenu::STYLE_XP_2003_NOBORDER:
        {
          COLORREF blendcolor = LightenColor(115,CNewMenu::GetMenuBarColor2003());
          transparentColor = MakeGrayAlphablend(&bitmap,110, blendcolor); 
        }
        break;

      case CNewMenu::STYLE_XP:
      case CNewMenu::STYLE_XP_NOBORDER:
      default:
        {
          COLORREF blendcolor = LightenColor(115,CNewMenu::GetMenuBarColorXP());
          transparentColor = MakeGrayAlphablend(&bitmap,110, blendcolor); 
        }
        break;
      }

      if(m_ImageListDisabled.GetSafeHandle())
      {
        m_ImageListDisabled.DeleteImageList();
      }
      m_ImageListDisabled.Create(m_sizeImage.cx,m_sizeImage.cy,ILC_COLORDDB|ILC_MASK,0,10); 
      m_ImageListDisabled.Add(&bitmap,transparentColor); 

      return TRUE;
    }
  }
  return FALSE;
}

BOOL CNewToolBar::LoadToolBar(LPCTSTR lpszResourceName)
{
  BOOL bRet = CToolBar::LoadToolBar(lpszResourceName);

  LoadHiColor(lpszResourceName);

  return bRet;
}

BOOL CNewToolBar::LoadToolBar(UINT nIDResource)
{
  return LoadToolBar(MAKEINTRESOURCE(nIDResource));
}

void CNewToolBar::PaintOrangeState(CDC *pDC, CRect rc, bool bHot)
{
  CPen penBlue;
  //dunkelblauer rahmen
  penBlue.CreatePen(PS_INSIDEFRAME,1, RGB(4, 2, 132));
  CPen* pOldPen = pDC->SelectObject(&penBlue);

  pDC->Rectangle(rc);
  rc.DeflateRect(1,1); 

  if(bHot)
  { //heller oranger rahmen 
    DrawGradient(pDC,rc,RGB(250,239,219),RGB(255,212,151),false);
  }
  else
  { //dunkler oranger rahmen
    DrawGradient(pDC,rc,RGB(242,151,107),RGB(249,202,163),false);
  }
  pDC->SelectObject(pOldPen);
}

BOOL CNewToolBar::PaintHotButton(LPNMCUSTOMDRAW lpNMCustomDraw)
{
  CDC* pDC = CDC::FromHandle(lpNMCustomDraw->hdc);

  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    {
      if (lpNMCustomDraw->uItemState&CDIS_CHECKED ||
          lpNMCustomDraw->uItemState&CDIS_HOT)
      {
        COLORREF colorSel = GetXpHighlightColor();
        COLORREF colorBorder = GetSysColor(COLOR_HIGHLIGHT);
        pDC->FillSolidRect(&(lpNMCustomDraw->rc),colorSel);
        pDC->Draw3dRect(&(lpNMCustomDraw->rc),colorBorder,colorBorder);
      }
    }
    break;

    case CNewMenu::STYLE_ICY:
    case CNewMenu::STYLE_ICY_NOBORDER:
      {
        COLORREF colorMid = GetSysColor(COLOR_HIGHLIGHT);
        COLORREF colorSel = LightenColor(60,colorMid);
        COLORREF colorBorder = DarkenColor(60,colorMid);
        CRect rect(lpNMCustomDraw->rc);
        if(lpNMCustomDraw->uItemState == CDIS_HOT)
        { 	 
          DrawGradient(pDC,rect,colorSel,colorMid,false);
          pDC->Draw3dRect(&(lpNMCustomDraw->rc),colorBorder,colorBorder);  
        }
        else if (lpNMCustomDraw->uItemState == (CDIS_HOT | CDIS_SELECTED))
        {
          DrawGradient(pDC,rect,colorMid,colorBorder,false);
          pDC->Draw3dRect(&(lpNMCustomDraw->rc),colorBorder,colorBorder);  
        }
        else if (lpNMCustomDraw->uItemState&CDIS_CHECKED)
        {
          pDC->FillSolidRect(&(lpNMCustomDraw->rc),colorSel);
          pDC->Draw3dRect(&(lpNMCustomDraw->rc),colorBorder,colorBorder);  
        }
      }
      break;

    case CNewMenu::STYLE_XP_2003_NOBORDER:
    case CNewMenu::STYLE_XP_2003: 
    {
      if(lpNMCustomDraw->uItemState == CDIS_HOT)
      { 	 
        PaintOrangeState(pDC,lpNMCustomDraw->rc, true);
      }
      else if (lpNMCustomDraw->uItemState == (CDIS_HOT | CDIS_SELECTED))
      {
        PaintOrangeState(pDC,lpNMCustomDraw->rc, false);
      }
      else if (lpNMCustomDraw->uItemState&CDIS_CHECKED)
      {
        COLORREF colorSel = RGB(255,238,194);
        COLORREF colorBorder = RGB(4, 2, 132);//GetSysColor(COLOR_HIGHLIGHT);
        pDC->FillSolidRect(&(lpNMCustomDraw->rc),colorSel);
        pDC->Draw3dRect(&(lpNMCustomDraw->rc),colorBorder,colorBorder);  
      }
    }
    break;

  default:
    {
      if(lpNMCustomDraw->uItemState == CDIS_HOT)
      { 	 
        pDC->Draw3dRect(&(lpNMCustomDraw->rc),GetSysColor(COLOR_HIGHLIGHTTEXT),GetSysColor(COLOR_BTNSHADOW));
      }
      else if (lpNMCustomDraw->uItemState == (CDIS_HOT | CDIS_SELECTED))
      {
        pDC->Draw3dRect(&(lpNMCustomDraw->rc),GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_HIGHLIGHTTEXT));
      }
      else if (lpNMCustomDraw->uItemState&CDIS_CHECKED)
      { 	 
        pDC->Draw3dRect(&(lpNMCustomDraw->rc),GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_HIGHLIGHTTEXT));
      }
    }
    break;
  }
  return TRUE;
}

void CNewToolBar::PaintTBButton(LPNMCUSTOMDRAW pInfo)
{	
  CImageList* pImgList = (pInfo->uItemState&CDIS_DISABLED)?&m_ImageListDisabled:&m_ImageList;
  CDC *pDC = CDC::FromHandle(pInfo->hdc);
  CPoint ptImage(pInfo->rc.left+3,pInfo->rc.top+3);

  int nIndex = CommandToIndex(pInfo->dwItemSpec);
  UINT nID = 0;
  UINT nStyle = 0;
  int iImage = 0;
  GetButtonInfo(nIndex,nID,nStyle,iImage);

  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    if(pInfo->uItemState&CDIS_HOT && !(pInfo->uItemState&CDIS_SELECTED))
    {
      int cx,cy;
      ::ImageList_GetIconSize(pImgList->GetSafeHandle(),&cx,&cy);
      CSize imgSize(cx,cy);

      ptImage.x = pInfo->rc.left+4;
      ptImage.y = pInfo->rc.top+4;
      // draws the icon blended
      HICON hDrawIcon2 = pImgList->ExtractIcon(iImage);
      pDC->DrawState(ptImage, imgSize, hDrawIcon2, DSS_MONO,(HBRUSH)NULL);
      DestroyIcon(hDrawIcon2);

      ptImage.x = pInfo->rc.left+2;
      ptImage.y = pInfo->rc.top+2;
    }
    break;

  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
    break;

  default:
    if((pInfo->uItemState&CDIS_SELECTED))
    {
      ptImage.x = pInfo->rc.left+4;
      ptImage.y = pInfo->rc.top+4;
    }
    if(m_ImageList.GetSafeHandle())
    {
      int cx=0;
      int cy=0;
      if(::ImageList_GetIconSize(m_ImageList,&cx,&cy))
      {
        HICON hDrawIcon = m_ImageList.ExtractIcon(iImage);
        ::ImageList_GetIconSize(m_ImageList,&cx,&cy);
        CSize size(cx,cy);
        if(pInfo->uItemState&CDIS_DISABLED)
        {
          pDC->DrawState(ptImage, size, hDrawIcon, DSS_DISABLED, (HBRUSH)NULL);
        }
        else
        {
          pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL, (HBRUSH)NULL);
        }
        DestroyIcon(hDrawIcon);
      }
      return;
    }
    break;
  }

  if(pImgList->GetSafeHandle())
  {
    pImgList->Draw(pDC,iImage,ptImage,ILD_TRANSPARENT);
  }
}  

void CNewToolBar::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMCUSTOMDRAW pNMCD = (LPNMCUSTOMDRAW)(pNMHDR);
  LPNMTBCUSTOMDRAW lpNMCustomDraw = (LPNMTBCUSTOMDRAW) pNMHDR;
  *pResult = CDRF_DODEFAULT;

  switch(lpNMCustomDraw->nmcd.dwDrawStage)
  {
  case CDDS_PREPAINT: 
    *pResult = CDRF_NOTIFYITEMDRAW|CDRF_NOTIFYPOSTPAINT|CDRF_SKIPDEFAULT;
    break;

  case CDDS_POSTPAINT:
    *pResult = CDRF_NOTIFYSUBITEMDRAW|CDRF_SKIPDEFAULT;
    // Erase Seperators
    break;

  case CDDS_ITEMPOSTPAINT:
    *pResult = CDRF_NOTIFYSUBITEMDRAW|CDRF_SKIPDEFAULT;
    // Erase Seperators
    break;

  case CDDS_ITEMPREPAINT:
    if(PaintHotButton(pNMCD))
    {
      *pResult = CDRF_DODEFAULT|TBCDRF_NOEDGES;//CDRF_SKIPDEFAULT;
    }
    PaintTBButton(&lpNMCustomDraw->nmcd);
    *pResult = CDRF_SKIPDEFAULT;
    break;

  default:
    break;
  }
}

int CNewToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CToolBar::OnCreate(lpCreateStruct) == -1)
    return -1;

  //typedef HRESULT (WINAPI* FktSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
  //extern FktSetWindowTheme pSetWindowTheme;
  //if(pSetWindowTheme)
  //{ // try do disable thems, but it does not work!!!
  //  pSetWindowTheme(m_hWnd,L" ",L" ");
  //}

  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    {
      COLORSCHEME scheme;
      scheme.dwSize = sizeof(COLORSCHEME);
      scheme.clrBtnHighlight = CLR_DEFAULT;//DarkenColorXP(CNewMenu::GetMenuBarColor());;
      scheme.clrBtnShadow= DarkenColorXP(CNewMenu::GetMenuBarColorXP());

      ::SendMessage(m_hWnd,TB_SETCOLORSCHEME,0,(LPARAM)&scheme);
    }
    break;

  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
    {
      SetBorders(3,1,3,1);

      COLORSCHEME scheme;
      scheme.dwSize = sizeof(COLORSCHEME);
      scheme.clrBtnHighlight = CLR_DEFAULT;//DarkenColorXP(CNewMenu::GetMenuBarColor());;
      scheme.clrBtnShadow= DarkenColorXP(CNewMenu::GetMenuBarColor2003());

      ::SendMessage(m_hWnd,TB_SETCOLORSCHEME,0,(LPARAM)&scheme);
    }
    break;

  default:
    break;
  } 
  return 0;
}
 
void CNewToolBar::OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle)
{
  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
  case CNewMenu::STYLE_ICY:
  case CNewMenu::STYLE_ICY_NOBORDER:
    if(dwNewStyle& CBRS_FLOATING)
    {
      SetBorders(0,0,0,0);
    }
    else
    {
      SetBorders(3,1,3,1);
    }
    break;

  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
  default:
    break;
  }
  CToolBar::OnBarStyleChange(dwOldStyle, dwNewStyle);
}

void CNewToolBar::OnPaint()
{
  CPaintDC dc(this);
  CWnd* pParent = GetParent();

  CFrameWnd* pFrame = GetDockingFrame();
  while(pFrame && pFrame->GetParentFrame())
  { 
    pFrame = pFrame->GetParentFrame();
  }
  BOOL bFocus = pFrame?pFrame->IsChild(GetFocus()):false;

  NMTBCUSTOMDRAW myDraw = {0};
  myDraw.nmcd.hdr.code = NM_CUSTOMDRAW;
  myDraw.nmcd.hdr.hwndFrom = m_hWnd;
  myDraw.nmcd.hdr.idFrom = GetDlgCtrlID();
  CRect client;
  GetClientRect(client);
  myDraw.nmcd.rc = client;
  myDraw.nmcd.hdc = dc.m_hDC;

  myDraw.nmcd.dwDrawStage = CDDS_PREPAINT; 
  LRESULT result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);

  myDraw.nmcd.dwDrawStage = CDDS_PREERASE; 
  result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);

  myDraw.nmcd.dwDrawStage = CDDS_POSTERASE; 
  result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);

  int nCountBtn = (int)SendMessage (TB_BUTTONCOUNT, 0, 0);

  TBBUTTON tbButton;
  CPoint pt;
  GetCursorPos(&pt);
  ScreenToClient(&pt);

  COLORREF clrUpperColor = GetSysColor(COLOR_3DLIGHT);
  COLORREF clrBottomColor = GetSysColor(COLOR_3DDKSHADOW);
  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
    {
      COLORREF menuColor = CNewMenu::GetMenuBarColorXP();
      clrUpperColor = clrBottomColor = DarkenColor(40,menuColor);
    }
    break;

  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003:
    {
      COLORREF menuColor = CNewMenu::GetMenuBarColor2003();
      clrUpperColor = LightenColor(140,menuColor);
      clrBottomColor = DarkenColor(40,menuColor);
    }
    break;

  case CNewMenu::STYLE_ICY:
  case CNewMenu::STYLE_ICY_NOBORDER:
    clrUpperColor = LightenColor(150,clrBottomColor);    
    break;

  //default:
  //  break;
  }

  for(int i=0;i<nCountBtn;i++)
  {
    if (!SendMessage(TB_GETBUTTON, i, (LPARAM)&tbButton) ||
        (tbButton.fsState & TBSTATE_HIDDEN))
    { // coninue by error or hidden buttons
      continue; 
    }

    GetItemRect(i,&myDraw.nmcd.rc);    
    if (tbButton.fsStyle == TBSTYLE_SEP) 
    {
      CRect rect(myDraw.nmcd.rc);
      if (!(tbButton.fsState & TBSTATE_WRAP) || ! IsFloating())
      {
        if (m_dwStyle & CBRS_ORIENT_HORZ)
        {
          rect.left = ((rect.left + rect.right)/2)-1;
          if(clrBottomColor==clrUpperColor)
          {
            rect.right = rect.left + 1;
          }
          else
          {
            rect.right = rect.left + 2;
          }
          rect.top += 3;
          rect.bottom -= 3;
          dc.Draw3dRect(rect,clrBottomColor,clrUpperColor);
        }
        else
        {
          CRect lastRect(0,0,0,0);
          if(i>0)
          {
            GetItemRect(i-1,lastRect);
          }

          rect.top = (rect.bottom + lastRect.bottom)/2;
          if(clrBottomColor==clrUpperColor)
          {
            rect.bottom = rect.top + 1;
          }
          else
          {
            rect.bottom = rect.top + 2;
          }
          rect.right = lastRect.right - 3;
          rect.left += 3;

          dc.Draw3dRect(rect,clrBottomColor,clrUpperColor);
        }
      }
      else if(tbButton.fsState & TBSTATE_WRAP)
      {
        CRect lastRect(0,0,0,0);
        if(i>0)
        {
          GetItemRect(i-1,lastRect);
        }

        rect.top = (rect.bottom + lastRect.bottom)/2-1;
        if(clrBottomColor==clrUpperColor)
        {
          rect.bottom = rect.top + 1;
        }
        else
        {
          rect.bottom = rect.top + 2;
        }
        rect.right = client.right-2;
        rect.left += 2+2;

        dc.Draw3dRect(rect,clrBottomColor,clrUpperColor);
      }
    }
    else
    {
      if(tbButton.idCommand)
      {
        myDraw.nmcd.uItemState = 0;
        myDraw.nmcd.uItemState |= (tbButton.fsState&TBSTATE_CHECKED)?CDIS_CHECKED:0;
        myDraw.nmcd.uItemState |= (tbButton.fsState&TBSTATE_ENABLED)?0:CDIS_DISABLED;
        myDraw.nmcd.uItemState |= (tbButton.fsState&TBSTATE_INDETERMINATE)?CDIS_INDETERMINATE:0;

        if(bFocus && PtInRect (&myDraw.nmcd.rc,pt))
        {
          if(tbButton.fsState&TBSTATE_PRESSED)
            myDraw.nmcd.uItemState |= CDIS_HOT|CDIS_SELECTED;
          else
            myDraw.nmcd.uItemState |= CDIS_HOT;
        }
        else if(tbButton.fsState&TBSTATE_PRESSED)
        {
          myDraw.nmcd.uItemState |= CDIS_HOT;
        }

        myDraw.nmcd.dwItemSpec  = tbButton.idCommand;
        myDraw.nmcd.lItemlParam = tbButton.dwData;

        myDraw.nmcd.dwDrawStage = CDDS_PREPAINT|CDDS_ITEM; 
        result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);

        myDraw.nmcd.dwDrawStage = CDDS_POSTPAINT|CDDS_ITEM; 
        result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);
      }
    }
  }  

  myDraw.nmcd.dwDrawStage = CDDS_POSTPAINT; 
  result = pParent->SendMessage(WM_NOTIFY,myDraw.nmcd.hdr.idFrom,(LPARAM)&myDraw);
}

void CNewToolBar::PaintCorner(CDC *pDC, LPCRECT pRect, COLORREF color)
{
  pDC->SetPixel(pRect->left+1,pRect->top  ,color);
  pDC->SetPixel(pRect->left+0,pRect->top  ,color);
  pDC->SetPixel(pRect->left+0,pRect->top+1,color);

  pDC->SetPixel(pRect->left+0,pRect->bottom  ,color);
  pDC->SetPixel(pRect->left+0,pRect->bottom-1,color);
  pDC->SetPixel(pRect->left+1,pRect->bottom  ,color);

  pDC->SetPixel(pRect->right-1,pRect->top  ,color); 
  pDC->SetPixel(pRect->right  ,pRect->top  ,color); 
  pDC->SetPixel(pRect->right  ,pRect->top+1,color); 

  pDC->SetPixel(pRect->right-1,pRect->bottom  ,color);
  pDC->SetPixel(pRect->right  ,pRect->bottom  ,color);
  pDC->SetPixel(pRect->right  ,pRect->bottom-1,color);  
}

void CNewToolBar::PaintToolBarBackGnd(CDC* pDC)
{
  if((m_dwStyle & CBRS_FLOATING))
  {
    return;
  }

  switch (CNewMenu::GetMenuDrawMode())
  {
  case CNewMenu::STYLE_XP:
  case CNewMenu::STYLE_XP_NOBORDER:
  case CNewMenu::STYLE_XP_2003_NOBORDER:
  case CNewMenu::STYLE_XP_2003: 
  case CNewMenu::STYLE_ICY:
  case CNewMenu::STYLE_ICY_NOBORDER:
    break;

  default:
    return;
  }

  // To eliminate small border between menu and client rect
  MENUINFO menuInfo = {0};
  menuInfo.cbSize = sizeof(menuInfo);
  menuInfo.fMask = MIM_BACKGROUND;
  HWND hParent = ::GetParent(m_hWnd);
  hParent = ::GetParent(hParent);

  CBrush tempBrush;
  if(::GetMenuInfo(::GetMenu(hParent),&menuInfo) && menuInfo.hbrBack)
  {
  }
  else
  {
    switch (CNewMenu::GetMenuDrawMode())
    {
    case CNewMenu::STYLE_XP:
    case CNewMenu::STYLE_XP_NOBORDER:
      tempBrush.CreateSolidBrush(CNewMenu::GetMenuBarColorXP());
      break;

    case CNewMenu::STYLE_XP_2003_NOBORDER:
    case CNewMenu::STYLE_XP_2003: 
      tempBrush.CreateSolidBrush(CNewMenu::GetMenuBarColor2003());
      break;

    case CNewMenu::STYLE_ICY:
    case CNewMenu::STYLE_ICY_NOBORDER:
    default:
      tempBrush.CreateSolidBrush(GetSysColor(COLOR_3DLIGHT));
      break;
    }
    menuInfo.hbrBack = tempBrush;
  }  
  
  {
    CRect clientRect;
    GetWindowRect(clientRect);
    CRect windowRect;
    ::GetWindowRect(hParent,windowRect);
    ScreenToClient(windowRect);

    CBrush *pBrush = CBrush::FromHandle(menuInfo.hbrBack);
    // need for win95/98/me
    VERIFY(pBrush->UnrealizeObject());
    CPoint oldOrg = pDC->SetBrushOrg(windowRect.left,0);
 
    ScreenToClient(clientRect);
    pDC->FillRect(clientRect,pBrush);
    //pDC->FillSolidRect(clientRect,RGB(255,0,0));
    pDC->SetBrushOrg(oldOrg);
  }
}
