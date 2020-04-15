#pragma once

#include "common.hpp"
#include "sam_tool.hpp"
#include "lsa_heap_uniform_allocator.hpp"

#include <string>
#include <fstream>
#include <type_traits>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A common allocator for the LSA heap.
        /// </summary>
        class common_allocator : public lsa_heap_uniform_allocator
        {
        public:
            common_allocator(const LSA_SECPKG_FUNCTION_TABLE& table) : common_allocator{ table, default_block_size_ }
            {
            }

            common_allocator(const LSA_SECPKG_FUNCTION_TABLE& table, size_t block_size) : lsa_heap_uniform_allocator{ table, block_size }
            {
            }

            common_allocator(const LSA_SECPKG_FUNCTION_TABLE& table, bool auto_free) : common_allocator{ table, default_block_size_, auto_free }
            {
            }

            common_allocator(const LSA_SECPKG_FUNCTION_TABLE& table, size_t block_size, bool auto_free) : lsa_heap_uniform_allocator{ table, block_size, auto_free }
            {
            }

            virtual ~common_allocator() = default;

            /// <summary>
            /// Allocate a unicode string.
            /// </summary>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            LSA_UNICODE_STRING* allocate_string(const std::wstring& str)
            {
                auto result = allocate_zero_extra<LSA_UNICODE_STRING>((str.size() + 1) * sizeof(wchar_t));
                store_string_core(str.c_str(), result, str.size() * sizeof(wchar_t), (str.size() + 1) * sizeof(wchar_t));

                return result;
            }

            /// <summary>
            /// Allocate a ANSI string.
            /// </summary>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            LSA_STRING* allocate_string(const std::string& str)
            {
                auto result = allocate_zero_extra<LSA_STRING>(str.size() + 1);
                store_string_core(str.c_str(), result, str.size(), str.size() + 1);

                return result;
            }

            /// <summary>
            /// Allocate a string.
            /// </summary>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            template<typename TString>
            TString* clone_string(const TString& str)
            {
                auto result = allocate_zero_extra<TString>(str.MaximumLength);
                store_string_core(str.Buffer, result, str.Length, str.MaximumLength);

                return result;
            }

            /// <summary>
            /// Store a string.
            /// </summary>
            /// <param name="source">The source</param>
            /// <param name="destination">The destination</param>
            void store_string(const std::string& source, LSA_STRING& destination)
            {
                auto buffer = allocate_zero<char>(source.size() + 1);
                store_string_core(source.c_str(), &destination, buffer, source.size(), source.size() + 1);
            }

            /// <summary>
            /// Store a string.
            /// </summary>
            /// <param name="source">The source</param>
            /// <param name="destination">The destination</param>
            void store_string(const std::wstring& source, LSA_UNICODE_STRING& destination)
            {
                auto buffer = allocate_zero<wchar_t>((source.size() + 1) * sizeof(wchar_t));
                store_string_core(source.c_str(), &destination, buffer, source.size() * sizeof(wchar_t), (source.size() + 1) * sizeof(wchar_t));
            }

            /// <summary>
            /// Store a string.
            /// </summary>
            /// <param name="source">The source</param>
            /// <param name="destination">The destination</param>
            template<typename TString>
            void store_string(const TString& source, TString& destination)
            {
                auto buffer = allocate_zero<wchar_t>(source.MaximumLength);
                store_string_core(source.Buffer, &destination, buffer, source.Length, source.MaximumLength);
            }

            /// <summary>
            /// Clone a SID.
            /// </summary>
            /// <param name="sid">The SID to clone</param>
            /// <returns>The clone</returns>
            PSID clone_sid(PSID sid)
            {
                auto size = GetLengthSid(sid);
                auto result = allocate_zero<void>(size);

                memcpy(result, sid, size);

                return result;
            }

            /// <summary>
            /// Clone a SID and attach a new RID.
            /// </summary>
            /// <param name="sid">The SID to clone</param>
            /// <param name="new_rid">A new RID to attach</param>
            /// <returns>The clone</returns>
            PSID clone_sid(PSID sid, uint32_t new_rid)
            {
                int count;
                auto result = clone_sid(sid);

                if ((count = *GetSidSubAuthorityCount(result)) > 1)
                {
                    *GetSidSubAuthority(result, count - 1) = new_rid;
                }

                return result;
            }

            /// <summary>
            /// Convert a LSA_UNICODE_STRING to a LSA_STRING.
            /// </summary>
            /// <param name="str">The LSA_UNICODE_STRING</param>
            /// <returns>The LSA_STRING</returns>
            PLSA_STRING unicode_string_to_string(const LSA_UNICODE_STRING& str)
            {
                auto result = allocate_zero<LSA_STRING>();
                int size_needed = WideCharToMultiByte(CP_GBK, 0, str.Buffer, static_cast<int>(str.Length / sizeof(wchar_t)), nullptr, 0, nullptr, nullptr);
                if (size_needed <= 0)
                {
                    return result;
                }

                result->Buffer = allocate_zero<char>(size_needed + 1);
                result->Length = static_cast<uint16_t>(size_needed);
                result->MaximumLength = result->Length + 1;

                // Convert to std::string encoded in GBK.
                WideCharToMultiByte(CP_GBK, 0, str.Buffer, static_cast<int>(str.Length / sizeof(wchar_t)), result->Buffer, result->Length, nullptr, nullptr);

                return result;
            }

            /// <summary>
            /// Allocate a profile for an interactive logon.
            /// </summary>
            /// <param name="user_name">The user name</param>
            /// <returns>The profile</returns>
            PKERB_INTERACTIVE_PROFILE allocate_interactive_profile(PSID user_sid)
            {
                std::wofstream log{ R"(C:\allocate_interactive_profile.txt)", std::ios::trunc };
                sam_tool sam;

                // Get the user all information.
                auto info = sam.query_user_all_info(user_sid);
                if (!info)
                {
                    return nullptr;
                }

                log << std::wstring{ info->UserName.Buffer, info->UserName.Length / sizeof(wchar_t) } << std::endl;

                // Fill in the profile buffer.
                auto result = allocate_zero<KERB_INTERACTIVE_PROFILE>();
                result->MessageType = KerbInteractiveProfile;
                result->LogonCount = info->LogonCount;
                result->BadPasswordCount = info->BadPasswordCount;
                result->LogonTime = info->LastLogon;
                result->LogoffTime = info->AccountExpires;
                result->KickOffTime = info->AccountExpires;
                result->PasswordLastSet = info->PasswordLastSet;
                result->PasswordCanChange = info->PasswordCanChange;
                result->PasswordMustChange = info->PasswordMustChange;
                result->UserFlags = 0;

                // Copy the string fields.
                store_string(info->ScriptPath, result->LogonScript);
                store_string(info->HomeDirectory, result->HomeDirectory);
                store_string(info->FullName, result->FullName);
                store_string(info->ProfilePath, result->ProfilePath);
                store_string(info->HomeDirectoryDrive, result->HomeDirectoryDrive);

                // Set the computer name.
                store_string(LR"(\\)" + common::get_computer_name(), result->LogonServer);
                log << std::wstring{ result->LogonServer.Buffer, result->LogonServer.Length / sizeof(wchar_t) } << std::endl;

                return result;
            }
        public:
            /// <summary>
            /// Allocate a standalone ANSI string.
            /// </summary>
            /// <param name="table">The LSA function table</param>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            inline static LSA_STRING* standalone_string(const LSA_SECPKG_FUNCTION_TABLE& table, const std::string& str)
            {
                return standalone_string_core<LSA_STRING>(table, str.c_str(), str.size(), str.size() + 1);
            }

            /// <summary>
            /// Allocate a standalone unicode string.
            /// </summary>
            /// <param name="table">The LSA function table</param>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            inline static LSA_UNICODE_STRING* standalone_string(const LSA_SECPKG_FUNCTION_TABLE& table, const std::wstring& str)
            {
                return standalone_string_core<LSA_UNICODE_STRING>(table, str.c_str(), str.size() * sizeof(wchar_t), (str.size() + 1) * sizeof(wchar_t));
            }

            /// <summary>
            /// Allocate a standalone string.
            /// </summary>
            /// <param name="table">The LSA function table</param>
            /// <param name="str">The string</param>
            /// <returns>The allocated string</returns>
            template<typename TString>
            inline static TString* standalone_clone_string(const LSA_SECPKG_FUNCTION_TABLE& table, const TString& str)
            {
                return standalone_string_core<TString>(table, str.Buffer, str.Length, str.MaximumLength);
            }
        private:
            /// <summary>
            /// Allocate a standalone string.
            /// </summary>
            /// <param name="table">The LSA function table</param>
            /// <param name="str">The string</param>
            /// <param name="size">The size of the string, in bytes</param>
            /// <param name="max_size">The max size of the string, in bytes</param>
            /// <returns>The allocated string</returns>
            template<typename TString>
            static TString* standalone_string_core(const LSA_SECPKG_FUNCTION_TABLE& table, const std::remove_reference_t<decltype(*TString::Buffer)>* str, size_t size, size_t max_size)
            {
                // Allocate the string.
                auto result = static_cast<TString*>(table.AllocateLsaHeap(static_cast<uint32_t>(sizeof(TString) + max_size)));
                store_string_core(str, result, size, max_size);

                return result;
            }

            /// <summary>
            /// Store a string.
            /// </summary>
            /// <param name="str">The string</param>
            /// <param name="result">The storage</param>
            /// <param name="size">The size of the string, in bytes</param>
            /// <param name="max_size">The max size of the string, in bytes</param>
            template<typename TString>
            inline static void store_string_core(const std::remove_reference_t<decltype(*TString::Buffer)>* str, TString* result, size_t size, size_t max_size)
            {
                store_string_core(str, result, reinterpret_cast<uint8_t*>(result) + sizeof(TString), size, max_size);
            }

            /// <summary>
            /// Store a string.
            /// </summary>
            /// <param name="str">The string</param>
            /// <param name="result">The storage</param>
            /// <param name="buffer">The buffer to store the string</param>
            /// <param name="size">The size of the string, in bytes</param>
            /// <param name="max_size">The max size of the string, in bytes</param>
            template<typename TString>
            static void store_string_core(const std::remove_reference_t<decltype(*TString::Buffer)>* str, TString* result, void* buffer, size_t size, size_t max_size)
            {
                // Copy the data.
                result->Buffer = static_cast<decltype(TString::Buffer)>(buffer);
                result->Length = static_cast<uint16_t>(size);
                result->MaximumLength = static_cast<uint16_t>(max_size);

                if (result->Buffer != nullptr)
                {
                    memcpy(result->Buffer, str, result->MaximumLength);
                }
            }
        private:
            static constexpr size_t default_block_size_ = 65535;
        };
    }
}
