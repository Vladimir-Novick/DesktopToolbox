// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__51BC1565_C971_4965_A598_E00C4904C235__INCLUDED_)
#define AFX_MAINDLG_H__51BC1565_C971_4965_A598_E00C4904C235__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WtlEditBrowserCtrl.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
				 public CMessageFilter, public CIdleHandler
{
private:
	CWtlEditBrowserCtrl m_FilePath;
	CWtlEditBrowserCtrl m_FolderPath;
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_EB_PRESS, OnEditBrowserCtrlPress)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);


		m_FilePath.SubclassWindow( ::GetDlgItem( m_hWnd, IDC_FILEPATH ) );
		m_FolderPath.SubclassWindow( ::GetDlgItem( m_hWnd, IDC_FOLDERPATH ) );


		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);

		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}

	LRESULT OnEditBrowserCtrlPress(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if( (HWND)wParam == m_FilePath.m_hWnd )
		{
			BYTE OFN_Struct[88];
			OPENFILENAME* ofnstruct = (OPENFILENAME*) OFN_Struct;
			memset(ofnstruct, 0, sizeof(OFN_Struct));
			ofnstruct->lStructSize = sizeof(OFN_Struct);

			char filebuffer[255];
			char *sFileName;
			
			memset( filebuffer, 0, sizeof( filebuffer ) );

			ofnstruct->lpstrTitle = "Select one file"; // Caption
			ofnstruct->hwndOwner         = m_hWnd;
			ofnstruct->lpstrFile            = filebuffer;
			ofnstruct->nMaxFile          = 256;
			ofnstruct->lpstrInitialDir = "c:\\";
			ofnstruct->lpstrFilter          = "All files\0*.txt\0text files\0*.txt\0word files\0*.doc\0\0";
			ofnstruct->nFilterIndex      = 1;
			ofnstruct->Flags             = OFN_CREATEPROMPT | OFN_LONGNAMES |OFN_EXPLORER|OFN_ENABLEHOOK;//|OFN_ENABLESIZING ;

			if ( GetOpenFileName( ofnstruct ) )
			{
				sFileName = ofnstruct->lpstrFile;
				SetDlgItemText( IDC_FILEPATH, sFileName );
			}

		}
		else if( (HWND)wParam == m_FolderPath.m_hWnd )
		{
			TCHAR path[MAX_PATH];
			memset(path, 0, MAX_PATH);
			BROWSEINFO bi = { 0 };
			bi.lpszTitle = _T("Folder Location");
			bi.hwndOwner = (HWND)m_hWnd;

			LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
			if ( pidl != 0 )
			{
				// get the name of the folder
				SHGetPathFromIDList ( pidl, path );
				// free memory used
				IMalloc * imalloc = 0;
				if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
				{
					imalloc->Free ( pidl );
					imalloc->Release ( );
				}
				SetDlgItemText( IDC_FOLDERPATH, path );
			}
		}
		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__51BC1565_C971_4965_A598_E00C4904C235__INCLUDED_)
