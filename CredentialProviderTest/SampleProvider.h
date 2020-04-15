// SampleProvider.h: CSampleProvider 的声明

#pragma once
#include "resource.h"       // 主符号
#include "credential_definitions.hpp"
#include "CredentialProviderTest_i.h"

#include <Shlguid.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

namespace glasssix
{
    namespace hello
    {
        using namespace ATL;

        class ATL_NO_VTABLE CSampleProvider :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<CSampleProvider, &CLSID_SampleProvider>,
            public ISampleProvider,
            public ICredentialProvider,
            public ICredentialProviderSetUserArray
        {
        public:
            CSampleProvider();

            DECLARE_REGISTRY_RESOURCEID(108)

            BEGIN_COM_MAP(CSampleProvider)
                COM_INTERFACE_ENTRY(ISampleProvider)
                COM_INTERFACE_ENTRY(ICredentialProvider)
                COM_INTERFACE_ENTRY(ICredentialProviderSetUserArray)
            END_COM_MAP()

            DECLARE_PROTECT_FINAL_CONSTRUCT()

            HRESULT FinalConstruct();
            void FinalRelease();
        public:
            // 通过 ICredentialProvider 继承
            virtual HRESULT __stdcall SetUsageScenario(CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario, DWORD flags) override;
            virtual HRESULT __stdcall SetSerialization(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* info) override;
            virtual HRESULT __stdcall Advise(ICredentialProviderEvents* events, UINT_PTR advise_context) override;
            virtual HRESULT __stdcall UnAdvise() override;
            virtual HRESULT __stdcall GetFieldDescriptorCount(DWORD* count) override;
            virtual HRESULT __stdcall GetFieldDescriptorAt(DWORD index, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** descriptor) override;
            virtual HRESULT __stdcall GetCredentialCount(DWORD* count, DWORD* default, BOOL* auto_login_with_default) override;
            virtual HRESULT __stdcall GetCredentialAt(DWORD index, ICredentialProviderCredential** credential) override;

            // 通过 ICredentialProviderSetUserArray 继承
            virtual HRESULT __stdcall SetUserArray(ICredentialProviderUserArray* users) override;
        private:
            uint32_t user_index_;
            uintptr_t advise_context_;
            bool recreate_credentials_;
            CComPtr<ISampleCredential> credential_;
            CComPtr<ICredentialProviderEvents> events_;
            CComPtr<ICredentialProviderUserArray> users_;
            CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario_;
        private:
            inline static const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR field_descriptors_[CREDENTIAL_FIELD_COUNT] =
            {
                { CREDENTIAL_FIELD_LOGO, CPFT_TILE_IMAGE, nullptr, CPFG_CREDENTIAL_PROVIDER_LOGO },
                { CREDENTIAL_FIELD_STATUS_TEXT, CPFT_LARGE_TEXT },
                { CREDENTIAL_FIELD_SUBMIT_BUTTON, CPFT_SUBMIT_BUTTON }
            };
        };

        OBJECT_ENTRY_AUTO(__uuidof(SampleProvider), CSampleProvider)
    }
}
