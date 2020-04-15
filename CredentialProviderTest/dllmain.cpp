// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "CredentialProviderTest_i.h"
#include "dllmain.h"
#include "xdlldata.h"

namespace glasssix
{
    namespace hello
    {
        HINSTANCE dll_instance_;
    }
}

glasssix::hello::CCredentialProviderTestModule atl_module_;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
    glasssix::hello::dll_instance_ = hInstance;

    return atl_module_.DllMain(dwReason, lpReserved);
}
