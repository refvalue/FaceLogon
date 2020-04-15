

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#include "ndr64types.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "CredentialProviderTest_i.h"

#define TYPE_FORMAT_STRING_SIZE   63                                
#define PROC_FORMAT_STRING_SIZE   51                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _CredentialProviderTest_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } CredentialProviderTest_MIDL_TYPE_FORMAT_STRING;

typedef struct _CredentialProviderTest_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } CredentialProviderTest_MIDL_PROC_FORMAT_STRING;

typedef struct _CredentialProviderTest_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } CredentialProviderTest_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

static const RPC_SYNTAX_IDENTIFIER  _NDR64_RpcTransferSyntax = 
{{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}};



extern const CredentialProviderTest_MIDL_TYPE_FORMAT_STRING CredentialProviderTest__MIDL_TypeFormatString;
extern const CredentialProviderTest_MIDL_PROC_FORMAT_STRING CredentialProviderTest__MIDL_ProcFormatString;
extern const CredentialProviderTest_MIDL_EXPR_FORMAT_STRING CredentialProviderTest__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISampleProvider_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISampleProvider_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISampleCredential_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISampleCredential_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const CredentialProviderTest_MIDL_PROC_FORMAT_STRING CredentialProviderTest__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Initialize */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter scenario */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter user */

/* 32 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter descriptors */

/* 38 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Return value */

/* 44 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 46 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 48 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const CredentialProviderTest_MIDL_TYPE_FORMAT_STRING CredentialProviderTest__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x13793285 ),	/* 326709893 */
/*  8 */	NdrFcShort( 0x3ea6 ),	/* 16038 */
/* 10 */	NdrFcShort( 0x40fd ),	/* 16637 */
/* 12 */	0xb4,		/* 180 */
			0x20,		/* 32 */
/* 14 */	0x15,		/* 21 */
			0xf4,		/* 244 */
/* 16 */	0x7d,		/* 125 */
			0xa4,		/* 164 */
/* 18 */	0x1f,		/* 31 */
			0xbb,		/* 187 */
/* 20 */	
			0x11, 0x0,	/* FC_RP */
/* 22 */	NdrFcShort( 0x14 ),	/* Offset= 20 (42) */
/* 24 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
/* 28 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 30 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 32 */	NdrFcShort( 0x10 ),	/* 16 */
/* 34 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 36 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 38 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (24) */
			0x5b,		/* FC_END */
/* 42 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 44 */	NdrFcShort( 0x20 ),	/* 32 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0xa ),	/* Offset= 10 (58) */
/* 50 */	0x8,		/* FC_LONG */
			0xe,		/* FC_ENUM32 */
/* 52 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 54 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (30) */
			0x5b,		/* FC_END */
/* 58 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 60 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_CredentialProviderTest_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISampleProvider, ver. 0.0,
   GUID={0x51717537,0xe400,0x46ed,{0x97,0xad,0x14,0xf8,0x0a,0x3e,0x69,0x4a}} */

#pragma code_seg(".orpc")
static const unsigned short ISampleProvider_FormatStringOffsetTable[] =
    {
    0
    };



/* Object interface: ISampleCredential, ver. 0.0,
   GUID={0x3aaf78d3,0x9229,0x4632,{0xae,0x71,0x2e,0xb1,0xe6,0x25,0x0e,0xe8}} */

#pragma code_seg(".orpc")
static const unsigned short ISampleCredential_FormatStringOffsetTable[] =
    {
    0
    };



/* Standard interface: __MIDL_itf_CredentialProviderTest_0000_0003, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


#endif /* defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)




#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif


#include "ndr64types.h"
#include "pshpack8.h"


typedef 
NDR64_FORMAT_CHAR
__midl_frag9_t;
extern const __midl_frag9_t __midl_frag9;

typedef 
struct _NDR64_CONFORMANT_STRING_FORMAT
__midl_frag8_t;
extern const __midl_frag8_t __midl_frag8;

typedef 
struct 
{
    struct _NDR64_STRUCTURE_HEADER_FORMAT frag1;
    struct 
    {
        struct _NDR64_NO_REPEAT_FORMAT frag1;
        struct _NDR64_POINTER_INSTANCE_HEADER_FORMAT frag2;
        struct _NDR64_POINTER_FORMAT frag3;
        NDR64_FORMAT_CHAR frag4;
    } frag2;
}
__midl_frag7_t;
extern const __midl_frag7_t __midl_frag7;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag6_t;
extern const __midl_frag6_t __midl_frag6;

typedef 
struct _NDR64_CONSTANT_IID_FORMAT
__midl_frag5_t;
extern const __midl_frag5_t __midl_frag5;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag4_t;
extern const __midl_frag4_t __midl_frag4;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_PARAM_FORMAT frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
    struct _NDR64_PARAM_FORMAT frag5;
}
__midl_frag2_t;
extern const __midl_frag2_t __midl_frag2;

typedef 
NDR64_FORMAT_UINT32
__midl_frag1_t;
extern const __midl_frag1_t __midl_frag1;

static const __midl_frag9_t __midl_frag9 =
0x5    /* FC64_INT32 */;

static const __midl_frag8_t __midl_frag8 =
{ 
/* *WCHAR */
    { 
    /* *WCHAR */
        0x64,    /* FC64_CONF_WCHAR_STRING */
        { 
        /* *WCHAR */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT16) 2 /* 0x2 */
    }
};

static const __midl_frag7_t __midl_frag7 =
{ 
/* CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR */
    { 
    /* CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR */
        0x31,    /* FC64_PSTRUCT */
        (NDR64_UINT8) 7 /* 0x7 */,
        { 
        /* CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR */
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT8) 0 /* 0x0 */,
        (NDR64_UINT32) 32 /* 0x20 */
    },
    { 
    /*  */
        { 
        /* struct _NDR64_NO_REPEAT_FORMAT */
            0x80,    /* FC64_NO_REPEAT */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT16) 0 /* 0x0 */,
            (NDR64_UINT32) 0 /* 0x0 */
        },
        { 
        /* struct _NDR64_POINTER_INSTANCE_HEADER_FORMAT */
            (NDR64_UINT32) 8 /* 0x8 */,
            (NDR64_UINT32) 0 /* 0x0 */
        },
        { 
        /* *WCHAR */
            0x21,    /* FC64_UP */
            (NDR64_UINT8) 0 /* 0x0 */,
            (NDR64_UINT16) 0 /* 0x0 */,
            &__midl_frag8
        },
        0x93    /* FC64_END */
    }
};

static const __midl_frag6_t __midl_frag6 =
{ 
/* *CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag7
};

static const __midl_frag5_t __midl_frag5 =
{ 
/* struct _NDR64_CONSTANT_IID_FORMAT */
    0x24,    /* FC64_IP */
    (NDR64_UINT8) 1 /* 0x1 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    {
        0x13793285,
        0x3ea6,
        0x40fd,
        {0xb4, 0x20, 0x15, 0xf4, 0x7d, 0xa4, 0x1f, 0xbb}
    }
};

static const __midl_frag4_t __midl_frag4 =
{ 
/* *struct _NDR64_POINTER_FORMAT */
    0x24,    /* FC64_IP */
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag5
};

static const __midl_frag2_t __midl_frag2 =
{ 
/* Initialize */
    { 
    /* Initialize */      /* procedure Initialize */
        (NDR64_UINT32) 786755 /* 0xc0143 */,    /* auto handle */ /* IsIntrepreted, [object], ClientMustSize, HasReturn */
        (NDR64_UINT32) 40 /* 0x28 */ ,  /* Stack size */
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 4 /* 0x4 */,
        (NDR64_UINT16) 0 /* 0x0 */
    },
    { 
    /* scenario */      /* parameter scenario */
        &__midl_frag9,
        { 
        /* scenario */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* user */      /* parameter user */
        &__midl_frag4,
        { 
        /* user */
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* MustSize, MustFree, [in] */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    },
    { 
    /* descriptors */      /* parameter descriptors */
        &__midl_frag7,
        { 
        /* descriptors */
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* MustSize, MustFree, [in], SimpleRef */
        (NDR64_UINT16) 0 /* 0x0 */,
        24 /* 0x18 */,   /* Stack offset */
    },
    { 
    /* HRESULT */      /* parameter HRESULT */
        &__midl_frag9,
        { 
        /* HRESULT */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        32 /* 0x20 */,   /* Stack offset */
    }
};

static const __midl_frag1_t __midl_frag1 =
(NDR64_UINT32) 0 /* 0x0 */;


#include "poppack.h"



/* Standard interface: __MIDL_itf_CredentialProviderTest_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISampleProvider, ver. 0.0,
   GUID={0x51717537,0xe400,0x46ed,{0x97,0xad,0x14,0xf8,0x0a,0x3e,0x69,0x4a}} */

#pragma code_seg(".orpc")
static const FormatInfoRef ISampleProvider_Ndr64ProcTable[] =
    {
    0
    };


static const MIDL_SYNTAX_INFO ISampleProvider_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    &ISampleProvider_FormatStringOffsetTable[-3],
    CredentialProviderTest__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &ISampleProvider_Ndr64ProcTable[-3],
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO ISampleProvider_ProxyInfo =
    {
    &Object_StubDesc,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    &ISampleProvider_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)ISampleProvider_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO ISampleProvider_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    (unsigned short *) &ISampleProvider_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)ISampleProvider_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(3) _ISampleProviderProxyVtbl = 
{
    0,
    &IID_ISampleProvider,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _ISampleProviderStubVtbl =
{
    &IID_ISampleProvider,
    &ISampleProvider_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISampleCredential, ver. 0.0,
   GUID={0x3aaf78d3,0x9229,0x4632,{0xae,0x71,0x2e,0xb1,0xe6,0x25,0x0e,0xe8}} */

#pragma code_seg(".orpc")
static const FormatInfoRef ISampleCredential_Ndr64ProcTable[] =
    {
    &__midl_frag2
    };


static const MIDL_SYNTAX_INFO ISampleCredential_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    &ISampleCredential_FormatStringOffsetTable[-3],
    CredentialProviderTest__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &ISampleCredential_Ndr64ProcTable[-3],
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO ISampleCredential_ProxyInfo =
    {
    &Object_StubDesc,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    &ISampleCredential_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)ISampleCredential_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO ISampleCredential_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CredentialProviderTest__MIDL_ProcFormatString.Format,
    (unsigned short *) &ISampleCredential_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)ISampleCredential_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(4) _ISampleCredentialProxyVtbl = 
{
    &ISampleCredential_ProxyInfo,
    &IID_ISampleCredential,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISampleCredential::Initialize */
};

const CInterfaceStubVtbl _ISampleCredentialStubVtbl =
{
    &IID_ISampleCredential,
    &ISampleCredential_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_CredentialProviderTest_0000_0003, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    CredentialProviderTest__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x2000001, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _CredentialProviderTest_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISampleProviderProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISampleCredentialProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _CredentialProviderTest_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISampleProviderStubVtbl,
    ( CInterfaceStubVtbl *) &_ISampleCredentialStubVtbl,
    0
};

PCInterfaceName const _CredentialProviderTest_InterfaceNamesList[] = 
{
    "ISampleProvider",
    "ISampleCredential",
    0
};

const IID *  const _CredentialProviderTest_BaseIIDList[] = 
{
    0,
    0,
    0
};


#define _CredentialProviderTest_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CredentialProviderTest, pIID, n)

int __stdcall _CredentialProviderTest_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _CredentialProviderTest, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _CredentialProviderTest, 2, *pIndex )
    
}

const ExtendedProxyFileInfo CredentialProviderTest_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CredentialProviderTest_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CredentialProviderTest_StubVtblList,
    (const PCInterfaceName * ) & _CredentialProviderTest_InterfaceNamesList,
    (const IID ** ) & _CredentialProviderTest_BaseIIDList,
    & _CredentialProviderTest_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

