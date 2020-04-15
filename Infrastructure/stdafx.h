// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

using NTSTATUS = long;

#define WIN32_NO_STATUS
#include <windows.h>

#undef WIN32_NO_STATUS
#include <ntstatus.h>

#include <comdef.h>
#include <atlbase.h>

#include <LM.h>
#include <Sspi.h>
#include <sddl.h>
#include <NTSecAPI.h>
#include <NTSecPKG.h>
#include <wincrypt.h>
