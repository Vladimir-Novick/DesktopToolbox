#ifndef _MDRAGTARGET_H
#define _MDRAGTARGET_H

 
#include "resource.h"



class CDropTarget : public IDropTarget
    {
    protected:
        ULONG                m_cRef;
        LPDATAOBJECT         m_pIDataObject;

    public:
		CDropTarget(){

		};

		~CDropTarget(void){

		};

        //IDropTarget interface members
        STDMETHODIMP QueryInterface(REFIID, void**);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP DragEnter(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragOver(DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragLeave(void);
        STDMETHODIMP Drop(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
    };




#endif