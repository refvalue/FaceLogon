// SampleProvider.cpp: CSampleProvider 的实现

#include "stdafx.h"
#include "common.hpp"
#include "SampleProvider.h"
#include "SampleCredential.h"
#include "com_string_fetcher.hpp"

#include <thread>

#include <propkey.h>

namespace glasssix
{
    namespace hello
    {
        CSampleProvider::CSampleProvider() : scenario_{ CPUS_INVALID }, recreate_credentials_{}, user_index_{}, advise_context_{}
        {

        }

        // CSampleProvider
        HRESULT CSampleProvider::FinalConstruct()
        {
            return S_OK;
        }

        void CSampleProvider::FinalRelease()
        {
        }

        HRESULT __stdcall CSampleProvider::SetUsageScenario(CREDENTIAL_PROVIDER_USAGE_SCENARIO scenario, DWORD flags)
        {
            switch (scenario)
            {
            case CPUS_LOGON:
            case CPUS_UNLOCK_WORKSTATION:
            {
                scenario_ = scenario;
                recreate_credentials_ = true;

                return S_OK;
            }
            case CPUS_CHANGE_PASSWORD:
            case CPUS_CREDUI:
                return E_NOTIMPL;
            default:
                return E_INVALIDARG;
            }
        }

        HRESULT __stdcall CSampleProvider::SetSerialization(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* info)
        {
            return E_NOTIMPL;
        }

        HRESULT __stdcall CSampleProvider::Advise(ICredentialProviderEvents* events, UINT_PTR advise_context)
        {
            events_ = events;
            advise_context_ = advise_context;

            return S_OK;
        }

        HRESULT __stdcall CSampleProvider::UnAdvise()
        {
            events_.Release();
            advise_context_ = 0;

            return S_OK;
        }

        HRESULT __stdcall CSampleProvider::GetFieldDescriptorCount(DWORD* count)
        {
            if (count == nullptr)
            {
                return E_INVALIDARG;
            }

            *count = static_cast<uint32_t>(std::size(field_descriptors_));

            return S_OK;
        }

        HRESULT __stdcall CSampleProvider::GetFieldDescriptorAt(DWORD index, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** descriptor)
        {
            if (index >= std::size(field_descriptors_) || descriptor == nullptr)
            {
                return E_INVALIDARG;
            }

            auto clone = common::field_descriptor_clone(field_descriptors_[index]);
            if (clone == nullptr)
            {
                return E_INVALIDARG;
            }

            *descriptor = clone;

            return S_OK;
        }

        HRESULT __stdcall CSampleProvider::GetCredentialCount(DWORD* count, DWORD* default, BOOL* auto_logon_with_default)
        {
            if (count == nullptr || default == nullptr || auto_logon_with_default == nullptr)
            {
                return E_INVALIDARG;
            }

            *default = CREDENTIAL_PROVIDER_NO_DEFAULT;
            *auto_logon_with_default = FALSE;
            *count = 0;

            DWORD user_count;
            auto hr = users_->GetCount(&user_count);

            if (SUCCEEDED(hr))
            {
                *count = user_count;
            }

            // Create credentials if necessary.
            if (SUCCEEDED(hr) && recreate_credentials_ || credential_ == nullptr)
            {
                CComPtr<ICredentialProviderUser> user;

                recreate_credentials_ = false;
                hr = credential_.CoCreateInstance(CLSID_SampleCredential);

                if (SUCCEEDED(hr))
                {
                    user = [&]
                    {
                        std::wstring user_display_name;
                        CComPtr<ICredentialProviderUser> inner;

                        for (DWORD i = 0; i < user_count; i++)
                        {
                            hr = users_->GetAt(i, &inner);
                            if (SUCCEEDED(hr))
                            {
                                hr = inner->GetStringValue(PKEY_Identity_DisplayName, com_string_fetcher{ hr, user_display_name });
                            }

                            // Glasssix-ZMY
                            if (SUCCEEDED(hr) && user_display_name == L"Administrator")
                            {
                                user_index_ = i;

                                return inner;
                            }
                        }

                        user_index_ = -1;

                        return CComPtr<ICredentialProviderUser>{};
                    }();

                    hr = user != nullptr ? S_OK : E_FAIL;
                }

                if (SUCCEEDED(hr))
                {
                    hr = credential_->Initialize(scenario_, user, field_descriptors_);
                }
            }

            return hr;
        }

        HRESULT __stdcall CSampleProvider::GetCredentialAt(DWORD index, ICredentialProviderCredential** credential)
        {
            // We only support assigning the credential to the first account.
            if (credential == nullptr)
            {
                return E_INVALIDARG;
            }

            HRESULT hr = E_NOTIMPL;

            if (index == user_index_)
            {
                hr = credential_.QueryInterface(credential);
            }

            return hr;
        }

        HRESULT __stdcall CSampleProvider::SetUserArray(ICredentialProviderUserArray* users)
        {
            users_ = users;

            return S_OK;
        }
    }
}
