

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISampleProvider,0x51717537,0xe400,0x46ed,0x97,0xad,0x14,0xf8,0x0a,0x3e,0x69,0x4a);


MIDL_DEFINE_GUID(IID, IID_ISampleCredential,0x3aaf78d3,0x9229,0x4632,0xae,0x71,0x2e,0xb1,0xe6,0x25,0x0e,0xe8);


MIDL_DEFINE_GUID(IID, LIBID_CredentialProviderTestLib,0xe03d8900,0x55b1,0x40b4,0xab,0x5b,0x90,0x9c,0x42,0x9e,0xd5,0xf7);


MIDL_DEFINE_GUID(CLSID, CLSID_SampleProvider,0x194df9f5,0x0d5e,0x4d96,0xb7,0x1c,0xfb,0x91,0xf2,0xb7,0x32,0x25);


MIDL_DEFINE_GUID(CLSID, CLSID_SampleCredential,0x7c6ca508,0xfa0e,0x4126,0xa2,0xc7,0x62,0xe4,0xc7,0xe2,0xd4,0x98);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



