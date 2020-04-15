// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

using NTSTATUS = long;

// Strip out redefinitions of NTSTATUS codes.
#define WIN32_NO_STATUS
#include <windows.h>

#undef WIN32_NO_STATUS
#include <ntstatus.h>

#include <Sspi.h>
#include <sddl.h>
#include <NTSecAPI.h>
#include <NTSecPKG.h>
#include <Shlwapi.h>

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <comdef.h>
#include <credentialprovider.h>
