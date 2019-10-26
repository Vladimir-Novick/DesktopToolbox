/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jul 14 11:04:02 2007
 */
/* Compiler settings for F:\DesktopToolbox\DesktopToolbox.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DesktopToolbox_h__
#define __DesktopToolbox_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ImyButton_FWD_DEFINED__
#define __ImyButton_FWD_DEFINED__
typedef interface ImyButton ImyButton;
#endif 	/* __ImyButton_FWD_DEFINED__ */


#ifndef __myButton_FWD_DEFINED__
#define __myButton_FWD_DEFINED__

#ifdef __cplusplus
typedef class myButton myButton;
#else
typedef struct myButton myButton;
#endif /* __cplusplus */

#endif 	/* __myButton_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ImyButton_INTERFACE_DEFINED__
#define __ImyButton_INTERFACE_DEFINED__

/* interface ImyButton */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ImyButton;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3AB45C7F-2B38-4E32-A15C-FF4DD3AC4829")
    ImyButton : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ImyButtonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ImyButton __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ImyButton __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ImyButton __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ImyButton __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ImyButton __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ImyButton __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ImyButton __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ImyButtonVtbl;

    interface ImyButton
    {
        CONST_VTBL struct ImyButtonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImyButton_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ImyButton_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ImyButton_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ImyButton_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ImyButton_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ImyButton_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ImyButton_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ImyButton_INTERFACE_DEFINED__ */



#ifndef __DESKTOPTOOLBOXLib_LIBRARY_DEFINED__
#define __DESKTOPTOOLBOXLib_LIBRARY_DEFINED__

/* library DESKTOPTOOLBOXLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DESKTOPTOOLBOXLib;

EXTERN_C const CLSID CLSID_myButton;

#ifdef __cplusplus

class DECLSPEC_UUID("B7F99F4D-6D27-4D66-AB6A-D6E5207945F2")
myButton;
#endif
#endif /* __DESKTOPTOOLBOXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
