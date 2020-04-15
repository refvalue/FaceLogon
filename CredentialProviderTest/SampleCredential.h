// SampleCredential.h: SampleCredentialImpl 的声明

#pragma once
#include "resource.h"       // 主符号
#include "credential_definitions.hpp"
#include "CredentialProviderTest_i.h"

#include <string>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

namespace glasssix
{
    namespace hello
    {
        using namespace ATL;

        class ATL_NO_VTABLE SampleCredentialImpl :
            public CComObjectRootEx<CComSingleThreadModel>,
            public CComCoClass<SampleCredentialImpl, &CLSID_SampleCredential>,
            public ISampleCredential,
            public ICredentialProviderCredential2
        {
        public:
            SampleCredentialImpl();

            DECLARE_REGISTRY_RESOURCEID(109)

            BEGIN_COM_MAP(SampleCredentialImpl)
                COM_INTERFACE_ENTRY(ISampleCredential)
                COM_INTERFACE_ENTRY(ICredentialProviderCredential)
                COM_INTERFACE_ENTRY(ICredentialProviderCredential2)
            END_COM_MAP()

            DECLARE_PROTECT_FINAL_CONSTRUCT()

            HRESULT FinalConstruct();

            void FinalRelease();

        public:
            // 通过 ICredentialProviderCredential2 继承
            virtual HRESULT __stdcall Advise(ICredentialProviderCredentialEvents* events) override;
            virtual HRESULT __stdcall UnAdvise() override;
            virtual HRESULT __stdcall SetSelected(BOOL* auto_logon) override;
            virtual HRESULT __stdcall SetDeselected() override;
            virtual HRESULT __stdcall GetFieldState(DWORD field_id, CREDENTIAL_PROVIDER_FIELD_STATE* field_state, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* field_interactive_state) override;
            virtual HRESULT __stdcall GetStringValue(DWORD field_id, LPWSTR* value) override;
            virtual HRESULT __stdcall GetBitmapValue(DWORD field_id, HBITMAP* bitmap) override;
            virtual HRESULT __stdcall GetCheckboxValue(DWORD field_id, BOOL* checked, LPWSTR* value) override;
            virtual HRESULT __stdcall GetSubmitButtonValue(DWORD field_id, DWORD* adjacent_to) override;
            virtual HRESULT __stdcall GetComboBoxValueCount(DWORD field_id, DWORD* count, DWORD* selected_index) override;
            virtual HRESULT __stdcall GetComboBoxValueAt(DWORD field_id, DWORD index, LPWSTR* value) override;
            virtual HRESULT __stdcall SetStringValue(DWORD field_id, LPCWSTR value) override;
            virtual HRESULT __stdcall SetCheckboxValue(DWORD field_id, BOOL checked) override;
            virtual HRESULT __stdcall SetComboBoxSelectedValue(DWORD field_id, DWORD selected_index) override;
            virtual HRESULT __stdcall CommandLinkClicked(DWORD field_id) override;
            virtual HRESULT __stdcall GetSerialization(CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* response, CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* serialization, LPWSTR* optional_status_text, CREDENTIAL_PROVIDER_STATUS_ICON* optional_status_icon) override;
            virtual HRESULT __stdcall ReportResult(NTSTATUS status, NTSTATUS substatus, LPWSTR* optional_status_text, CREDENTIAL_PROVIDER_STATUS_ICON* optional_status_icon) override;
            virtual HRESULT __stdcall GetUserSid(LPWSTR* sid) override;

            // 通过 ISampleCredential 继承
            virtual HRESULT __stdcall Initialize(CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario, ICredentialProviderUser* user, const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* descriptors);
        private:
            bool detect_face_core();
        private:
            std::wstring user_sid_;
            std::wstring user_display_name_;
            std::wstring qualified_user_name_;
            CComPtr<ICredentialProviderCredentialEvents2> events_;
            credential_field_state field_states_[CREDENTIAL_FIELD_COUNT] =
            {
                { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE },
                { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE },
                { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE }
            };
            CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR field_descriptors_[CREDENTIAL_FIELD_COUNT];
        };

        OBJECT_ENTRY_AUTO(__uuidof(SampleCredential), SampleCredentialImpl)
    }
}
