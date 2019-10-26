// DeskEditor1.h : Declaration of the CDeskEditor

#ifndef __DeskEditor_H_
#define __DeskEditor_H_

#include "resource.h"       // main symbol

#define WM_SHOW_EDIT_BOX WM_USER+201
#define  WM_SAVE_TREE WM_USER+202
#define SHOW_EDIT_BOX_MSG 1

#include <atlhost.h>


#include "MEditBox.h"

	#define TCX_ICON  16 
	#define TCY_ICON  16 
	#define TNUM_ICONS 4 


enum TYPESAVE             // type save and export file type
{
   Type_SAVE,
   Type_DHTML
} ;               



/////////////////////////////////////////////////////////////////////////////
// CDeskEditor
class CDeskEditor : 
	public CAxDialogImpl<CDeskEditor>
{
private:
	char lpCommand[255];
    static int iTreeLevel;
	void GetAllTree();
    VOID ExpandAllW(DWORD Key);
    void SaveEnd (char *pFileName);
    void SaveStart (char *pFileName);
    void SaveFolderItem(HTREEITEM retNew,char *pFileName);
	void GetItemAttr(HTREEITEM item,char *strName,char *strUrl,int &iconType);
    void SaveItem (HTREEITEM retNew,char *pFileName);
    void SaveChidren (HTREEITEM retNew,char *pFileName);
    HWND hWndEditBoxName;
	HWND hWndEditBoxURL;
	CMEditBox m_EditControl;

    void SaveTreeToFile(char *pFileName);
    HTREEITEM InsertNewTopItem(LPSTR lpszItem, int IndexFolder,int mi_Document1 = 2);
    HTREEITEM InsertNewTopFolder(LPSTR lpszItem, int IndexFolder);
    HTREEITEM InsertCopyTreeMain(HTREEITEM hSrc);
	HTREEITEM InsertCopy(HTREEITEM hSrc);
    HTREEITEM InsertNewItem(LPSTR lpszItem, int IndexFolder);
    HTREEITEM CopyTreeMain(HTREEITEM hDest, HTREEITEM hSrc);
	BOOL TestNoChildren(HTREEITEM hti);
	BOOL TestNoExpandChildren(HTREEITEM hti);
	BOOL TestNoExpandAll(HTREEITEM hti);
    BOOL TestNoExpaned(HTREEITEM hti);
	void TestChildFolderIcon(HTREEITEM hti);
	VOID TestFolderIcon(HTREEITEM hti);
	VOID SaveRestoreExpand(BOOL SaveFlad);

	BOOL TestFolder(HTREEITEM hDest);
	VOID CopyChildren(HTREEITEM hDest, HTREEITEM hSrc);
	HTREEITEM CopyTree(HTREEITEM hDest, HTREEITEM hSrc);
	HTREEITEM MoveTree(HTREEITEM hDest, HTREEITEM hSrc);
	VOID AddIconsToImageList(DWORD IDI_icon);
		HIMAGELIST hImageList;
		char BufText[255];
		int m_FolderSteck[255];
		int m_LenSteckFolder;
		int m_NewFolderIndex;
		HWND  m_hwndEditCtrl;
		HIMAGELIST m_pImageList;
		long mi_nOpen;
		long mi_MainDesktop;
		long mi_nClose;
		long mi_Document;
		HCURSOR StandardCursor;
		HCURSOR NoCursor;
		HCURSOR YesCursor;
		long mi_RootPersonalLink;
		TYPESAVE m_TypeSave;
		HTREEITEM m_DropItem;
		int m_DragItemIcon;
		HTREEITEM m_CurrentItem;
		HTREEITEM m_EditTreeItem;
		HTREEITEM m_EditItem;

		HTREEITEM m_TargetItem;
		BOOL m_bDragging;
		BOOL m_bDragFolder;
		HWND h_tree;

		int InnerHeight;
		BOOL boolClearAll;
		HTREEITEM SteckItem[20];
		int LenStectItem;
		char BufEdit[255];

private:
	BOOL m_BoolSaveFlag;
	BOOL m_SaveCurrentFolder;
	void WebEncode(char *strSrc);
    char CurrentFileName[255];
	void MSelect(HTREEITEM hti);

	void CaseMenuPopup(DWORD uMenuID);
	HTREEITEM DeleteItem(HTREEITEM hti);
	HTREEITEM InsertNewFolder(LPSTR lpszItem, int IndexFolder);
	BOOL TestExpandAll(HTREEITEM hti);
	VOID ExpandChildren(HTREEITEM hti,DWORD Key);
	VOID ExpandAll(HTREEITEM hti,DWORD Key);
	DWORD GetItemID(HTREEITEM hti,char * Text,int &folder);
	void InsertEndFolder(void){ LenStectItem--;};
	void InsertItem(LPSTR lpstrName, LPSTR IndexFolder,int mi_Document1=2);
void InsertNextFolder(LPSTR lpszItem, int IndexFolder,int iconType=0,LPSTR strURL =NULL);
	void InsertTopLavel(LPSTR lpstritem,int IndexFolder);
public:
	LRESULT OnSaveTree(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnShowEditBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	VOID MyDrawGradient(HDC hDC,RECT rect,COLORREF t_color,COLORREF b_color,BOOL orientation);
	void PaintTop(void);
		VOID ResizeWindowPanel();
				int InnerWidth;
			int iPozDelim ;
	void LoadTreeFromFile(char * FileName);

	CDeskEditor()
	{
		m_BoolSaveFlag = FALSE;
		boolClearAll = TRUE;
		m_SaveCurrentFolder = FALSE;
		m_EditTreeItem = NULL;
        ::SetWindowText(hWndEditBoxName,"");
		strcpy(CurrentFileName,"Untitles.mnu");
		m_bDragging = FALSE;
        hImageList =  ImageList_Create(TCX_ICON, TCY_ICON, ILC_COLOR16  , TNUM_ICONS, 0); 
		mi_nClose = 0 ;
		AddIconsToImageList(IDI_ICON_CLOSE);
		mi_nOpen = 1 ;
		AddIconsToImageList(IDI_ICON_OPEN);
		mi_Document = 2;
		AddIconsToImageList(IDI_ICON_LINK);
		mi_RootPersonalLink = 3;
		AddIconsToImageList(IDI_ICON_PERSONAL_LINK);

		mi_MainDesktop = 4;
		AddIconsToImageList(IDI_ICON_XP);

	}





	~CDeskEditor()
	{
		   		ImageList_Destroy(hImageList);
	}

	enum { IDD = IDD_DeskEditor };

BEGIN_MSG_MAP(CDeskEditor)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_SHOW_EDIT_BOX, OnShowEditBox)
    MESSAGE_HANDLER(WM_SAVE_TREE, OnSaveTree)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUP)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_ITEMEXPANDED, OnItemexpandedTree_ctrl)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_BEGINDRAG, OnBegindragTree_ctrl)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)

	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	NOTIFY_HANDLER(IDC_TREE_CTRL, NM_RCLICK, OnRclickTree_ctrl)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_SELCHANGED, OnSelchangedTree_ctrl)
	COMMAND_HANDLER(IDC_EDIT_NAME, EN_CHANGE, OnChangeEdit_name)
	NOTIFY_HANDLER(IDC_TREE_CTRL, NM_SETFOCUS, OnSetfocusTree_ctrl)
	NOTIFY_HANDLER(IDC_TREE_CTRL, TVN_DELETEITEM, OnDeleteitemTree_ctrl)
	COMMAND_HANDLER(IDC_EDIT_URL, EN_CHANGE, OnChangeEdit_url)
	MESSAGE_HANDLER(WM_COMMAND, OnMenuCommand)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	NOTIFY_HANDLER(IDC_TREE_CTRL, NM_DBLCLK, OnDblclkTree_ctrl)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnItemexpandedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnBegindragTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		InnerWidth = LOWORD(lParam);
		InnerHeight = HIWORD(lParam);

        ResizeWindowPanel();
		return 0;
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnRclickTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnSelchangedTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);




	LRESULT OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChangeEdit_name(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSetfocusTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
				 if (m_EditTreeItem == NULL){
					::SetWindowText(hWndEditBoxName,"");
				 }
		// TODO : Add Code for control notification handler.
		return 0;
	}
	LRESULT OnDeleteitemTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnChangeEdit_url(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDblclkTree_ctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
};

#endif //__DeskEditor_H_
