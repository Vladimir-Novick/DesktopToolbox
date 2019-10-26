#include "stdafx.h"
#include "MDragTarget.h"

//
// A very minimal IDropTarget interface implementation
//

STDMETHODIMP CDropTarget::QueryInterface( REFIID refiid,
                             void** ppvObject )
{
    *ppvObject = 0;

    if ( !IsEqualIID( IID_IUnknown, refiid ) )
        if ( !IsEqualIID( IID_IUnknown, refiid ) )  // Hey!  Identical test!
            return E_NOINTERFACE;

    // If we get here, IID_IUnknown was asked for...
    this->AddRef();
    *ppvObject = this;

    return S_OK;
}

STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
{
    InterlockedIncrement( (long *)(&this->m_cRef) );
    return this->m_cRef;
}

STDMETHODIMP_(ULONG)  CDropTarget::Release(void)
{
    if ( 0 == InterlockedDecrement(  (long *)(&this->m_cRef )) )
    {
        // If we got here, the reference count dropped to zero...
        if ( this )
            delete this;
        
        return S_OK;
    }

    return this->m_cRef;
}

STDMETHODIMP CDropTarget::DragEnter( IDataObject * pDataObject,
                        DWORD grfKeyState,
                        POINTL pt,
                        DWORD * pdwEffect )
{
    *pdwEffect = 0   ;
    return S_OK;
}

STDMETHODIMP CDropTarget::DragOver( DWORD grfKeyState,
                       POINTL pt,
                       DWORD * pdwEffect )
{
    *pdwEffect = 0;
	*pdwEffect = DROPEFFECT_COPY;
    return S_OK;
}

STDMETHODIMP CDropTarget::DragLeave(void)
{
    return S_OK;
}




STDMETHODIMP CDropTarget::Drop( IDataObject * pIDataObj,
                   DWORD grfKeyState,
                   POINTL pt,
                   DWORD * pdwEffect )
{   

   char *pTextBuff;
   pTextBuff = NULL;

    STGMEDIUM stgMedium;

    HRESULT		 hr;
	LPVOID		 pGlobMem;
    DWORD		 sizeGlobBuff;
  
  
    FORMATETC  formatETC;
 	formatETC.cfFormat = CF_TEXT;
 	formatETC.ptd      = NULL;
 	formatETC.dwAspect = DVASPECT_CONTENT;
 	formatETC.lindex   = -1;
 	formatETC.tymed    = TYMED_HGLOBAL;
 
 	hr = pIDataObj->GetData( &formatETC, &stgMedium );
 	pGlobMem = GlobalLock( stgMedium.hGlobal );
 	if ( NULL != pGlobMem )
 	{
 		if ( NULL != pTextBuff )
    		{
 			free( pTextBuff );
 		}
 
 		sizeGlobBuff = GlobalSize( stgMedium.hGlobal );
 		pTextBuff = (char*)malloc( sizeGlobBuff + 1 );
 		ZeroMemory( pTextBuff, sizeGlobBuff + 1 );
 
 		memcpy( pTextBuff, pGlobMem, sizeGlobBuff );
		GlobalUnlock( stgMedium.hGlobal );
//
//						HWND thwnd = ::GetDlgItem(m_SaveToolBar->m_hWnd,IDC_EDIT_TEXT);


//------- unicode ------
						if (pTextBuff[0]=='?'){

						    free(pTextBuff);
    FORMATETC  formatETC;
 	formatETC.cfFormat = CF_UNICODETEXT;//CF_TEXT;
 	formatETC.ptd      = NULL;
 	formatETC.dwAspect = DVASPECT_CONTENT;
 	formatETC.lindex   = -1;
 	formatETC.tymed    = TYMED_HGLOBAL;
 
 	hr = pIDataObj->GetData( &formatETC, &stgMedium );
 	pGlobMem = GlobalLock( stgMedium.hGlobal );
 	if ( NULL != pGlobMem )
 	{
 
 		sizeGlobBuff = GlobalSize( stgMedium.hGlobal );
 		pTextBuff = (char*)malloc( sizeGlobBuff + 1 );
 		ZeroMemory( pTextBuff, sizeGlobBuff + 1 );
		WORD *pTextInt = (WORD *)malloc( sizeGlobBuff+2);
 		memcpy( pTextInt, pGlobMem, sizeGlobBuff );
 	    GlobalUnlock( stgMedium.hGlobal );
		unsigned int ity;
		for (ity=0; ity < sizeGlobBuff; ity++){
			if ((pTextInt[ity] >= 0x0410)&& (pTextInt[ity] <= 0x044F)) {
			  pTextBuff[ity]=pTextInt[ity]-0x0410+192;
			} else {
			  pTextBuff[ity]=pTextInt[ity];
			}
		}
		pTextBuff[ity]= 0;
		free(pTextInt);
//						::SetWindowText(thwnd,pTextBuff);
//					     PostMessage(m_SaveToolBar->m_hWnd, WM_GO, 
//							0, 0);
	}

	}else {
//----------------------
//						::SetWindowText(thwnd,pTextBuff);
//					     PostMessage(m_SaveToolBar->m_hWnd, WM_GO, 
//							0, 0);
						}


   	}
    

  
    free(pTextBuff);



	*pdwEffect = 0;
    return S_OK;
}
