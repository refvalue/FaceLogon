#pragma once

#include "../Infrastructure/glasssix_hello_interactive_logon.hpp"

#include <tuple>
#include <string>
#include <optional>
#include <string_view>

namespace glasssix
{
    namespace hello
    {
        class common final
        {
        public:
            /// <summary>
            /// Duplicate a CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR.
            /// </summary>
            /// <param name="source">The source</param>
            /// <param name="destination">The destination</param>
            /// <returns>The result</returns>
            static HRESULT field_descriptor_copy(const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& source, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& destination)
            {
                // Copy the non-string fields simply.
                destination.cpft = source.cpft;
                destination.dwFieldID = source.dwFieldID;
                destination.guidFieldType = source.guidFieldType;

                // Copy the label if neccessary.
                HRESULT hr = S_OK;
                if (source.pszLabel != nullptr)
                {
                    hr = SHStrDupW(source.pszLabel, &destination.pszLabel);
                }
                else
                {
                    destination.pszLabel = nullptr;
                    hr = S_OK;
                }

                return hr;
            }

            /// <summary>
            /// Clone a CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR using CoTaskMemoryAlloc.
            /// </summary>
            /// <param name="descriptor">The source</param>
            /// <returns>The clone</returns>
            static CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* field_descriptor_clone(const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& descriptor)
            {
                auto result = static_cast<CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR*>(CoTaskMemAlloc(sizeof(CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR)));
                auto hr = field_descriptor_copy(descriptor, *result);

                // Release the allocated memory if failed.
                if (FAILED(hr))
                {
                    CoTaskMemFree(result);
                    result = nullptr;
                }

                return result;
            }

            /// <summary>
            /// Get the user name from a qualified user name such as "DOMAIN\USER".
            /// </summary>
            /// <param name="qualified_user_name">The qualified user name</param>
            /// <returns>The user name</returns>
            inline static std::wstring split_user_name(const std::wstring& qualified_user_name)
            {
                return qualified_user_name.substr(qualified_user_name.find_first_of('\\') + 1);
            }

            /// <summary>
            /// Create a LSA_STRING based on a string literal.
            /// </summary>
            /// <param name="str">The string literal</param>
            /// <returns>The LSA_STRING</returns>
            static LSA_STRING create_const_string(const char* str)
            {
                LSA_STRING result = {};

                if (str != nullptr)
                {
                    result.Buffer = const_cast<char*>(str);
                    result.Length = static_cast<uint16_t>(strlen(str));
                    result.MaximumLength = result.Length + 1;
                }

                return result;
            }

            /// <summary>
            /// Get the identifier of an authentication package.
            /// </summary>
            /// <param name="name">The package name</param>
            /// <returns>The identifier</returns>
            static std::optional<uint32_t> retrieve_authentication_package(const std::string& name)
            {
                HANDLE lsa_handle;
                unsigned long package_id;

                auto hr = HRESULT_FROM_NT(LsaConnectUntrusted(&lsa_handle));

                if (SUCCEEDED(hr))
                {
                    std::shared_ptr<void> lsa_handle_scope{ lsa_handle, LsaDeregisterLogonProcess };

                    // Initialize a LSA string with the package name.
                    auto package_name = create_const_string(name.c_str());

                    hr = HRESULT_FROM_NT(LsaLookupAuthenticationPackage(lsa_handle, &package_name, &package_id));
                }

                if (SUCCEEDED(hr))
                {
                    return package_id;
                }

                return std::nullopt;
            }

            /// <summary>
            /// Allocate a serialization buffer with all logon data.
            /// </summary>
            /// <param name="user_name">The user name</param>
            /// <param name="user_sid">The user SID</param>
            /// <param name="feature_data">The feature data</param>
            /// <param name="feature_size">The feature size</param>
            /// <returns>The serialization buffer</returns>
            static std::tuple<uint8_t*, size_t> allocate_credential_serialization_buffer(const std::wstring& user_name, const std::wstring& user_sid, const void* feature_data, size_t feature_size)
            {
                // Calculate the size of serialization.
                auto user_name_bytes = (user_name.size() + 1) * sizeof(wchar_t);
                auto user_sid_bytes = (user_sid.size() + 1) * sizeof(wchar_t);
                auto size = sizeof(glasssix_hello_interactive_logon) + user_name_bytes + user_sid_bytes + feature_size;

                // Allocate a buffer for serialization.
                auto buffer = static_cast<glasssix_hello_interactive_logon*>(CoTaskMemAlloc(size));
                auto extra_base = reinterpret_cast<uint8_t*>(buffer) + sizeof(glasssix_hello_interactive_logon);

                // Set the base address.
                buffer->original_base_address = buffer;

                // Set the sizes.
                buffer->feature_size = feature_size;
                buffer->user_sid.MaximumLength = static_cast<uint16_t>(user_sid_bytes);
                buffer->user_name.MaximumLength = static_cast<uint16_t>(user_name_bytes);
                buffer->user_sid.Length = static_cast<uint16_t>(user_sid_bytes - sizeof(wchar_t));
                buffer->user_name.Length = static_cast<uint16_t>(user_name_bytes - sizeof(wchar_t));

                // Set the buffers.
                buffer->user_name.Buffer = reinterpret_cast<wchar_t*>(extra_base);
                buffer->user_sid.Buffer = reinterpret_cast<wchar_t*>(extra_base + user_name_bytes);
                buffer->feature_data = extra_base + user_name_bytes + user_sid_bytes;

                // Copy all data.
                memcpy(buffer->user_name.Buffer, user_name.c_str(), user_name_bytes);
                memcpy(buffer->user_sid.Buffer, user_sid.c_str(), user_sid_bytes);
                memcpy(buffer->feature_data, feature_data, buffer->feature_size);

                return { reinterpret_cast<uint8_t*>(buffer), size };
            }
        };
    }
}
