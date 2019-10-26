/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 03 11:11:59 2000
 */
/* Compiler settings for E:\Developer Novick\DeskEditor\Async\Async.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __Async_h__
#define __Async_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IATLAsync_FWD_DEFINED__
#define __IATLAsync_FWD_DEFINED__
typedef interface IATLAsync IATLAsync;
#endif 	/* __IATLAsync_FWD_DEFINED__ */


#ifndef __CATLAsync_FWD_DEFINED__
#define __CATLAsync_FWD_DEFINED__

#ifdef __cplusplus
typedef class CATLAsync CATLAsync;
#else
typedef struct CATLAsync CATLAsync;
#endif /* __cplusplus */

#endif 	/* __CATLAsync_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IATLAsync_INTERFACE_DEFINED__
#define __IATLAsync_INTERFACE_DEFINED__

/* interface IATLAsync */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IATLAsync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("012F24D5-35B0-11D0-BF2D-0000E8D0D146")
    IATLAsync : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR strURL) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATLAsyncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IATLAsync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IATLAsync __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IATLAsync __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IATLAsync __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IATLAsync __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IATLAsync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IATLAsync __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URL )( 
            IATLAsync __RPC_FAR * This,
            /* [in] */ BSTR strURL);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IATLAsync __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrURL);
        
        END_INTERFACE
    } IATLAsyncVtbl;

    interface IATLAsync
    {
        CONST_VTBL struct IATLAsyncVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATLAsync_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATLAsync_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATLAsync_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATLAsync_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATLAsync_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATLAsync_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATLAsync_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATLAsync_put_URL(This,strURL)	\
    (This)->lpVtbl -> put_URL(This,strURL)

#define IATLAsync_get_URL(This,pstrURL)	\
    (This)->lpVtbl -> get_URL(This,pstrURL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IATLAsync_put_URL_Proxy( 
    IATLAsync __RPC_FAR * This,
    /* [in] */ BSTR strURL);


void __RPC_STUB IATLAsync_put_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IATLAsync_get_URL_Proxy( 
    IATLAsync __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrURL);


void __RPC_STUB IATLAsync_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATLAsync_INTERFACE_DEFINED__ */



#ifndef __ASYNCLib_LIBRARY_DEFINED__
#define __ASYNCLib_LIBRARY_DEFINED__

/* library ASYNCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ASYNCLib;

EXTERN_C const CLSID CLSID_CATLAsync;

#ifdef __cplusplus

class DECLSPEC_UUID("012F24D4-35B0-11D0-BF2D-0000E8D0D146")
CATLAsync;
#endif
#endif /* __ASYNCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
