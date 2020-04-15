// SampleCredential.cpp: SampleCredentialImpl 的实现

#include "stdafx.h"
#include "common.hpp"
#include "SampleCredential.h"
#include "com_string_fetcher.hpp"
#include "../Infrastructure/camera_window.h"
#include "../Infrastructure/glasssix_hello_interactive_logon.hpp"

#include <fstream>
#include <string_view>

#include <propkey.h>

namespace glasssix
{
    namespace hello
    {
        extern HINSTANCE dll_instance_;

        SampleCredentialImpl::SampleCredentialImpl() : field_descriptors_{}
        {
        }

        HRESULT SampleCredentialImpl::FinalConstruct()
        {
            return S_OK;
        }

        void SampleCredentialImpl::FinalRelease()
        {
            for (auto& item : field_descriptors_)
            {
                if (item.pszLabel != nullptr)
                {
                    CoTaskMemFree(item.pszLabel);
                    item.pszLabel = nullptr;
                }
            }
        }

        HRESULT __stdcall SampleCredentialImpl::Advise(ICredentialProviderCredentialEvents* events)
        {
            events_.Release();

            // Get the event object.
            return events->QueryInterface(IID_PPV_ARGS(&events_));
        }

        HRESULT __stdcall SampleCredentialImpl::UnAdvise()
        {
            events_.Release();

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::SetSelected(BOOL* auto_logon)
        {
            if (auto_logon == nullptr)
            {
                return E_INVALIDARG;
            }

            *auto_logon = FALSE;

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::SetDeselected()
        {
            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::GetFieldState(DWORD field_id, CREDENTIAL_PROVIDER_FIELD_STATE* field_state, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* field_interactive_state)
        {
            if (field_id >= std::size(field_states_) || field_state == nullptr || field_interactive_state == nullptr)
            {
                return E_INVALIDARG;
            }

            *field_state = field_states_[field_id].state;
            *field_interactive_state = field_states_[field_id].interactive_state;

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::GetStringValue(DWORD field_id, LPWSTR* value)
        {
            if (field_id >= std::size(field_states_) || value == nullptr)
            {
                return E_INVALIDARG;
            }

            *value = nullptr;

            return SHStrDupW(field_states_[field_id].value.c_str(), value);
        }

        HRESULT __stdcall SampleCredentialImpl::GetBitmapValue(DWORD field_id, HBITMAP* bitmap)
        {
            *bitmap = LoadBitmapW(dll_instance_, MAKEINTRESOURCE(IDB_BITMAP1));

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::GetCheckboxValue(DWORD field_id, BOOL* checked, LPWSTR* value)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::GetSubmitButtonValue(DWORD field_id, DWORD* adjacent_to)
        {
            if (field_id == CREDENTIAL_FIELD_SUBMIT_BUTTON && adjacent_to != nullptr)
            {
                *adjacent_to = CREDENTIAL_FIELD_STATUS_TEXT;

                return S_OK;
            }

            return E_INVALIDARG;
        }

        HRESULT __stdcall SampleCredentialImpl::GetComboBoxValueCount(DWORD field_id, DWORD* count, DWORD* selected_index)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::GetComboBoxValueAt(DWORD field_id, DWORD index, LPWSTR* value)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::SetStringValue(DWORD field_id, LPCWSTR value)
        {
            auto type = field_descriptors_[field_id].cpft;
            if (field_id >= std::size(field_states_) || (type != CPFT_EDIT_TEXT && type != CPFT_PASSWORD_TEXT))
            {
                return E_INVALIDARG;
            }

            field_states_[field_id].value = value;

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::SetCheckboxValue(DWORD field_id, BOOL checked)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::SetComboBoxSelectedValue(DWORD field_id, DWORD selected_index)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::CommandLinkClicked(DWORD field_id)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall SampleCredentialImpl::GetSerialization(CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* response, CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* serialization, LPWSTR* optional_status_text, CREDENTIAL_PROVIDER_STATUS_ICON* optional_status_icon)
        {
            if (response == nullptr || serialization == nullptr || optional_status_text == nullptr || optional_status_icon == nullptr)
            {
                return E_INVALIDARG;
            }

            // Get the authentication package.
            auto package_id = common::retrieve_authentication_package("GlasssixAuthHelloFace");
            if (!package_id)
            {
                return E_UNEXPECTED;
            }

            // Set the initial states.
            *response = CPGSR_NO_CREDENTIAL_NOT_FINISHED;
            *optional_status_text = nullptr;
            *optional_status_icon = CPSI_NONE;
            memset(serialization, 0, sizeof(*serialization));

            if (/*detect_face_core()*/true)
            {
                // Get the serialization buffer.
                auto user_name = common::split_user_name(qualified_user_name_);
                auto[buffer, size] = common::allocate_credential_serialization_buffer(user_name, user_sid_, std::vector<int>{1}.data(), sizeof(int));

                // Set the authentication package.
                serialization->ulAuthenticationPackage = *package_id;
                serialization->clsidCredentialProvider = __uuidof(SampleProvider);
                serialization->rgbSerialization = buffer;
                serialization->cbSerialization = static_cast<uint32_t>(size);

                *response = CPGSR_RETURN_CREDENTIAL_FINISHED;
            }

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::ReportResult(NTSTATUS status, NTSTATUS substatus, LPWSTR* optional_status_text, CREDENTIAL_PROVIDER_STATUS_ICON* optional_status_icon)
        {
            if (optional_status_text == nullptr || optional_status_icon == nullptr)
            {
                return E_INVALIDARG;
            }

            *optional_status_text = nullptr;
            *optional_status_icon = CPSI_NONE;

            return S_OK;
        }

        HRESULT __stdcall SampleCredentialImpl::GetUserSid(LPWSTR* sid)
        {
            if (sid == nullptr)
            {
                return E_INVALIDARG;
            }

            *sid = nullptr;

            if (!user_sid_.empty())
            {
                return SHStrDupW(user_sid_.c_str(), sid);
            }

            return E_UNEXPECTED;
        }

        HRESULT __stdcall SampleCredentialImpl::Initialize(CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario, ICredentialProviderUser* user, const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* descriptors)
        {
            HRESULT hr = S_OK;

            // Duplicate the field descriptors.
            // The size of the descriptors is guaranteed to be the same.
            auto ptr = descriptors;
            for (auto& item : field_descriptors_)
            {
                hr = common::field_descriptor_copy(*(ptr++), item);

                if (FAILED(hr))
                {
                    break;
                }
            }

            if (SUCCEEDED(hr))
            {
                // Get the user SID.
                hr = user->GetSid(com_string_fetcher{ hr, user_sid_ });
            }

            if (SUCCEEDED(hr))
            {
                // Get the qualified user name.
                hr = user->GetStringValue(PKEY_Identity_QualifiedUserName, com_string_fetcher{ hr, qualified_user_name_ });
            }

            if (SUCCEEDED(hr))
            {
                // Get the user display name.
                hr = user->GetStringValue(PKEY_Identity_DisplayName, com_string_fetcher{ hr, user_display_name_ });
            }

            if (SUCCEEDED(hr))
            {
                field_states_[CREDENTIAL_FIELD_STATUS_TEXT].value = user_sid_ + L"，请正视摄像头。";
            }

            return hr;
        }

        bool SampleCredentialImpl::detect_face_core()
        {
            HWND parent;
            auto hr = events_->OnCreatingWindow(&parent);
            if (SUCCEEDED(hr))
            {
                camera_window window{ GetModuleHandleW(nullptr), parent };
                window.start_camera();

                return static_cast<bool>(window.wait_for());
            }

            return false;
        }
    }
}
