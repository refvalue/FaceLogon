

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for CredentialProviderTest.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CredentialProviderTest_i_h__
#define __CredentialProviderTest_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISampleProvider_FWD_DEFINED__
#define __ISampleProvider_FWD_DEFINED__
typedef interface ISampleProvider ISampleProvider;

#endif 	/* __ISampleProvider_FWD_DEFINED__ */


#ifndef __ISampleCredential_FWD_DEFINED__
#define __ISampleCredential_FWD_DEFINED__
typedef interface ISampleCredential ISampleCredential;

#endif 	/* __ISampleCredential_FWD_DEFINED__ */


#ifndef __SampleProvider_FWD_DEFINED__
#define __SampleProvider_FWD_DEFINED__

#ifdef __cplusplus
typedef class SampleProvider SampleProvider;
#else
typedef struct SampleProvider SampleProvider;
#endif /* __cplusplus */

#endif 	/* __SampleProvider_FWD_DEFINED__ */


#ifndef __SampleCredential_FWD_DEFINED__
#define __SampleCredential_FWD_DEFINED__

#ifdef __cplusplus
typedef class SampleCredential SampleCredential;
#else
typedef struct SampleCredential SampleCredential;
#endif /* __cplusplus */

#endif 	/* __SampleCredential_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "credentialprovider.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_CredentialProviderTest_0000_0000 */
/* [local] */ 

namespace glasssix {
namespace hello {


extern RPC_IF_HANDLE __MIDL_itf_CredentialProviderTest_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CredentialProviderTest_0000_0000_v0_0_s_ifspec;

#ifndef __ISampleProvider_INTERFACE_DEFINED__
#define __ISampleProvider_INTERFACE_DEFINED__

/* interface ISampleProvider */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISampleProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51717537-e400-46ed-97ad-14f80a3e694a")
    ISampleProvider : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ISampleProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISampleProvider * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISampleProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISampleProvider * This);
        
        END_INTERFACE
    } ISampleProviderVtbl;

    interface ISampleProvider
    {
        CONST_VTBL struct ISampleProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISampleProvider_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISampleProvider_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISampleProvider_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISampleProvider_INTERFACE_DEFINED__ */


#ifndef __ISampleCredential_INTERFACE_DEFINED__
#define __ISampleCredential_INTERFACE_DEFINED__

/* interface ISampleCredential */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISampleCredential;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3aaf78d3-9229-4632-ae71-2eb1e6250ee8")
    ISampleCredential : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario,
            /* [in] */ ICredentialProviderUser *user,
            /* [in] */ const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR *descriptors) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISampleCredentialVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISampleCredential * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISampleCredential * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISampleCredential * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ISampleCredential * This,
            /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario,
            /* [in] */ ICredentialProviderUser *user,
            /* [in] */ const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR *descriptors);
        
        END_INTERFACE
    } ISampleCredentialVtbl;

    interface ISampleCredential
    {
        CONST_VTBL struct ISampleCredentialVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISampleCredential_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISampleCredential_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISampleCredential_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISampleCredential_Initialize(This,scenario,user,descriptors)	\
    ( (This)->lpVtbl -> Initialize(This,scenario,user,descriptors) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISampleCredential_INTERFACE_DEFINED__ */



#ifndef __CredentialProviderTestLib_LIBRARY_DEFINED__
#define __CredentialProviderTestLib_LIBRARY_DEFINED__

/* library CredentialProviderTestLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CredentialProviderTestLib;

EXTERN_C const CLSID CLSID_SampleProvider;

#ifdef __cplusplus

class DECLSPEC_UUID("194df9f5-0d5e-4d96-b71c-fb91f2b73225")
SampleProvider;
#endif

EXTERN_C const CLSID CLSID_SampleCredential;

#ifdef __cplusplus

class DECLSPEC_UUID("7c6ca508-fa0e-4126-a2c7-62e4c7e2d498")
SampleCredential;
#endif
#endif /* __CredentialProviderTestLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_CredentialProviderTest_0000_0003 */
/* [local] */ 

}}


extern RPC_IF_HANDLE __MIDL_itf_CredentialProviderTest_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CredentialProviderTest_0000_0003_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


