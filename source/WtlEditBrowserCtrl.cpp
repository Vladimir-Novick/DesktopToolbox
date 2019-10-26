#include "stdafx.h"
#include "WtlEditBrowserCtrl.h"
/*
Module : WtlEditBrowserCtrl.cpp
Purpose: Interface for an WTL class which provides a edit control with browse button 
Copyright (c) 2003 by iLYA Solnyshkin. 
E-mail: isolnyshkin@yahoo.com 
All rights reserved.

 Big thanks Pete Arends for your MFC-control( http://www3.telus.net/pja/CFileEditCtrl.htm ).
*/

CWtlEditBrowserCtrl::CWtlEditBrowserCtrl()
{
    m_nButtonState      = BTN_UP;
    m_nButtonWidth      = -1;
    m_rcButtonRect.SetRectEmpty();
    m_bMouseCaptured    = FALSE;
}

BOOL CWtlEditBrowserCtrl::PreTranslateMessage(MSG* pMsg) 
{
	return FALSE;
}

BOOL CWtlEditBrowserCtrl::SubclassWindow( HWND hWnd )
{
	BOOL bRet = CWindowImpl<CWtlEditBrowserCtrl, CEdit>::SubclassWindow( hWnd );

	CRect rectCtl;
	::GetWindowRect(m_hWnd, &rectCtl);
	::MapWindowPoints(NULL, GetParent(), (LPPOINT)&rectCtl, 2);
	SetWindowPos(NULL, &rectCtl, SWP_FRAMECHANGED);

	return bRet;
}

LRESULT CWtlEditBrowserCtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );
	return 0;
}

LRESULT CWtlEditBrowserCtrl::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );
	DrawButton(m_nButtonState);     // draw the button in its current state
	return 0;
}

void CWtlEditBrowserCtrl::DrawButton(int nButtonState)
{   // if the button is too small, do not draw it
    if( m_rcButtonRect.Width() < 3 || m_rcButtonRect.Height() < 3 )
        return;

    // if the control is disabled, ensure the button is drawn disabled
    if ( GetStyle() & WS_DISABLED )
        nButtonState = BTN_DISABLED;

    CRect DrawRect(m_rcButtonRect);
    DrawRect.OffsetRect(0 - m_rcButtonRect.left, 0 - m_rcButtonRect.top);

    CWindowDC WndDC( m_hWnd );     // get the DC for drawing
    // Create a memory DC to prevent flicker
    CDC DC;
    DC.CreateCompatibleDC(WndDC);
    int savedDC = DC.SaveDC();
    CBitmap Bitmap;
    Bitmap.CreateCompatibleBitmap(WndDC, m_rcButtonRect.Width(), m_rcButtonRect.Height());
    DC.SelectBitmap(Bitmap);

    // use HS_DIAGCROSS pattern brush to test brush alignment
    CBrush theBrush;
	theBrush.CreateSolidBrush( GetSysColor(COLOR_3DFACE));     // the colour of the button background
    CPoint BrushOrg;
    CPoint Origin;
	POINT p;
	WndDC.GetBrushOrg( &p );
	Origin = p;
    BrushOrg.x = (BRUSHWIDTH - (m_rcButtonRect.left - Origin.x) % BRUSHWIDTH);
    BrushOrg.y = (BRUSHHEIGHT - (m_rcButtonRect.top - Origin.y) % BRUSHHEIGHT);
    DC.SetBrushOrg(BrushOrg);

    DC.SelectBrush(theBrush);
    DC.FillRect(&DrawRect, theBrush);

    if (nButtonState == BTN_DOWN)
    {
        // draw the border
        CPen thePen;
		thePen.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
        CPen pOldPen = DC.SelectPen(thePen);
        DC.Rectangle(DrawRect);
        DC.SelectPen(pOldPen);
        thePen.DeleteObject();

        DrawDots(DC, GetSysColor(COLOR_BTNTEXT), 1);
    }
    else    // draw button as up
    {
        // draw the border
        if (m_nButtonState & BTN_FLAT)
        {
            CPen thePen;
			thePen.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
            CPen pOldPen = DC.SelectPen(thePen);
            DC.Rectangle(DrawRect);
            DC.SelectPen(pOldPen);
            thePen.DeleteObject();
        }
        else
            DC.DrawEdge(DrawRect, EDGE_RAISED, BF_RECT);

        if (nButtonState & BTN_DISABLED)
        {
            {   // draw the dots
                DrawDots(DC, GetSysColor(COLOR_3DHILIGHT), 1);
                DrawDots(DC, GetSysColor(COLOR_3DSHADOW));
            }
        }
        else if (nButtonState & BTN_UP)
        {
            {
                COLORREF dotcolour = GetSysColor(COLOR_BTNTEXT);
                if ((m_nButtonState & BTN_FLAT))
                {
                    int grayscale = (((GetBValue(dotcolour) * 11) + (GetGValue(dotcolour) * 59) + (GetRValue(dotcolour) * 30)) / 100);
                    dotcolour = RGB(grayscale, grayscale, grayscale);
                }
                DrawDots(DC, dotcolour);
            }
        }
        else
        {
            ATLASSERT(FALSE);  // Invalid nButtonState
        }
    }

    // Blit the button image onto the screen
    WndDC.BitBlt(m_rcButtonRect.left,
        m_rcButtonRect.top,
        m_rcButtonRect.Width(),
        m_rcButtonRect.Height(),
        DC,
        0,
        0,
        SRCCOPY);

    // clean up the memory DC
    DC.RestoreDC(savedDC);
    Bitmap.DeleteObject();

    // update m_nButtonState
    m_nButtonState = m_nButtonState & BTN_FLAT ? nButtonState | BTN_FLAT : nButtonState;
}

void CWtlEditBrowserCtrl::DrawDots(CDC& pDC, COLORREF CR, int nOffset /* = 0 */)
{
    int width = m_rcButtonRect.Width();         // width of the button
    div_t divt = div(width, 4);
    int delta = divt.quot;                      // space between dots
    int left = width / 2 - delta - (divt.rem ? 0 : 1); // left side of first dot
    width = width / 10;                         // width and height of one dot
    int top = m_rcButtonRect.Height() / 2 - width / 2;  // top of dots
    left += nOffset;                            // draw dots shifted? (for button pressed)
    top += nOffset;
    // draw the dots
    if (width < 2)
    {
        pDC.SetPixelV(left, top, CR);
        left += delta;
        pDC.SetPixelV(left, top, CR);
        left += delta;
        pDC.SetPixelV(left, top, CR);
    }
    else
    {
        CPen thePen;
		thePen.CreatePen(PS_SOLID, 1, CR);           // set the dot colour
        CPen pOldPen = pDC.SelectPen(thePen);
        CBrush theBrush;
		theBrush.CreateSolidBrush(CR);
        CBrush pOldBrush = pDC.SelectBrush(theBrush);
        pDC.Ellipse(left, top, left + width, top + width);
        left += delta;
        pDC.Ellipse(left, top, left + width, top + width);
        left += delta;
        pDC.Ellipse(left, top, left + width, top + width);
        pDC.SelectBrush(pOldBrush);           // reset the DC
        theBrush.DeleteObject();
        pDC.SelectPen(pOldPen);
        thePen.DeleteObject();
    }
}

LRESULT CWtlEditBrowserCtrl::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );

	NCCALCSIZE_PARAMS FAR* lpncsp = (NCCALCSIZE_PARAMS FAR*)lParam;
	
	// if m_nButtonWidth is -1, set the button width to 80% of the control height
    // else set the button width to m_nButtonWidth
    int ButtonWidth = (m_nButtonWidth == -1) ? (lpncsp->rgrc[0].bottom - lpncsp->rgrc[0].top) * 8/10 : m_nButtonWidth;
    
    // set button area equal to client area of edit control
    m_rcButtonRect = lpncsp->rgrc[0];
    
    // draw the button on the right side of the control
    // shrink right side of client area by the button width
    // and add a one pixel neutral area between button and client area
    int neutral = /*ButtonWidth > 2 ? 1 :*/ 0;
    lpncsp->rgrc[0].right -= ButtonWidth + neutral;
    // shrink the button so its left side is at the right side of client area
    m_rcButtonRect.left = lpncsp->rgrc[0].right + neutral;

    if ((BOOL)wParam)
        // convert button coordinates from parent client coordinates to control window coordinates
        m_rcButtonRect.OffsetRect(-lpncsp->rgrc[1].left, -lpncsp->rgrc[1].top);
    m_rcButtonRect.NormalizeRect();
	return 0;
}

LRESULT CWtlEditBrowserCtrl::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT where = DefWindowProc( uMsg, wParam, lParam );
    if (where == HTNOWHERE && ScreenPointInButtonRect(CPoint (GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))))
        where = HTBORDER;
    return where;
}

BOOL CWtlEditBrowserCtrl::ScreenPointInButtonRect(CPoint point)
{
    CRect ControlRect;
    GetWindowRect(&ControlRect);
    // convert point from screen coordinates to window coordinates
    point.Offset(-ControlRect.left, -ControlRect.top);
    return m_rcButtonRect.PtInRect(point);
}

LRESULT CWtlEditBrowserCtrl::OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );
	
    if (ScreenPointInButtonRect(CPoint (GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))))
    {
        SetFocus();
        SetCapture();
        m_bMouseCaptured = TRUE;
        DrawButton(BTN_DOWN);
    }
	return 0;
}

LRESULT CWtlEditBrowserCtrl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DefWindowProc( uMsg, wParam, lParam );
    if (m_bMouseCaptured)
    {
		CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        ReleaseCapture();
        m_bMouseCaptured = FALSE;
        if (m_nButtonState != BTN_UP)
            DrawButton(BTN_UP);
        ClientToScreen(&point);
        if (ScreenPointInButtonRect(point))
            ButtonClicked();
    }
	return 0;
}

void CWtlEditBrowserCtrl::ButtonClicked()
{
	SendMessage( GetParent(), WM_EB_PRESS, (LPARAM)m_hWnd, 0 );
}