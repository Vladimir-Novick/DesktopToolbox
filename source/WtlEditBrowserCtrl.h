#if !defined EDITBROWSERCTRL_H
#define EDITBROWSERCTRL_H

#include <atlapp.h>
#include <AtlCrack.h>
#include <atlmisc.h>
#include <atlctrls.h>

#define BTN_UP          0x01
#define BTN_DOWN        0x02
#define BTN_DISABLED    0x04
#define BTN_FLAT        0x08

// Brush sizes for drawing the button background
#define BRUSHWIDTH      8
#define BRUSHHEIGHT     8

#define FEC_BUTTONLEFT			0x00000010

#define WM_EB_PRESS				WM_USER + 4444
class CWtlEditBrowserCtrl : public CWindowImpl< CWtlEditBrowserCtrl, CEdit, CControlWinTraits>
{
private:
    int				m_nButtonState;        // current button state (up, down, or disabled)
    int             m_nButtonWidth;        // the width of the button (-1 is default)
    CRect           m_rcButtonRect;        // window coordinates of the button
    BOOL            m_bMouseCaptured;      // button has captured the mouse?
public:
	CWtlEditBrowserCtrl();

	typedef CWtlEditBrowserCtrl			thisClass;

	BEGIN_MSG_MAP(CWtlEditBrowserCtrl)
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		MESSAGE_HANDLER( WM_NCLBUTTONDOWN, OnNcLButtonDown )
		MESSAGE_HANDLER( WM_LBUTTONUP, OnLButtonUp )
		MESSAGE_HANDLER( WM_NCCALCSIZE, OnNcCalcSize )
		MESSAGE_HANDLER( WM_NCHITTEST, OnNcHitTest )
		MESSAGE_HANDLER( WM_NCPAINT, OnNcPaint )
	END_MSG_MAP()

	virtual BOOL SubclassWindow( HWND hWnd );
	virtual BOOL PreTranslateMessage(MSG* pMsg);

    void ButtonClicked();                   // handles a mouse click on the button

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	void DrawButton(int nButtonState);
	void DrawDots(CDC& pDC, COLORREF CR, int nOffset = 0);

	BOOL ScreenPointInButtonRect(CPoint point);
};

#endif