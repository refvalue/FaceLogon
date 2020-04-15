#pragma once

#include "account_info.h"

#include <tuple>
#include <memory>
#include <optional>
#include <algorithm>
#include <filesystem>
#include <type_traits>

#define CP_GBK 936

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// Some helper functions.
        /// </summary>
        class common final
        {
        public:
            /// <summary>
            /// Create a security string temporarily refering to a std::wstring.
            /// </summary>
            /// <param name="str">The string</param>
            /// <returns>A SECURITY_STRING</returns>
            static SECURITY_STRING make_temporary_security_string(const std::wstring& str)
            {
                SECURITY_STRING result;
                result.Buffer = reinterpret_cast<uint16_t*>(const_cast<wchar_t*>(str.c_str()));
                result.Length = static_cast<uint16_t>(str.size() * sizeof(wchar_t));
                result.MaximumLength = static_cast<uint16_t>(result.Length + sizeof(wchar_t));

                return result;
            }

            /// <summary>
            /// Lookup a account by name.
            /// </summary>
            /// <param name="name">The account name</param>
            /// <returns>The account information</returns>
            static std::optional<account_info> lookup_account(const wchar_t* name)
            {
                DWORD sid_size = 0;
                DWORD domain_size = 0;
                SID_NAME_USE sid_type = SidTypeInvalid;

                LookupAccountNameW(nullptr, name, nullptr, &sid_size, nullptr, &domain_size, nullptr);

                // We consider failure if the size of the SID is zero.
                if (sid_size == 0 || domain_size == 0)
                {
                    return std::nullopt;
                }

                std::wstring domain;
                std::shared_ptr<void> sid{ new uint8_t[sid_size], std::default_delete<uint8_t[]>{} };
                domain.resize(domain_size - 1);

                return LookupAccountNameW(nullptr, name, sid.get(), &sid_size, domain.data(), &domain_size, &sid_type) ?
                    std::make_optional<account_info>(sid_type, domain, sid) :
                    std::nullopt;
            }

            /// <summary>
            /// Lookup a account by name.
            /// </summary>
            /// <param name="name">The account name</param>
            /// <returns>The account information</returns>
            inline static std::optional<account_info> lookup_account(const UNICODE_STRING& name)
            {
                return lookup_account(std::wstring{ name.Buffer, name.Length / sizeof(wchar_t) }.c_str());
            }

            /// <summary>
            /// Get user information.
            /// </summary>
            /// <returns>The user information</returns>
            static std::shared_ptr<USER_INFO_4> get_user_info(const UNICODE_STRING& user_name)
            {
                PUSER_INFO_4 info;
                std::wstring user_name_inner{ user_name.Buffer, user_name.Length / sizeof(wchar_t) };

                return NERR_Success == NetUserGetInfo(nullptr, user_name_inner.c_str(), 4, reinterpret_cast<uint8_t**>(&info)) ?
                    std::shared_ptr<USER_INFO_4>{ info, NetApiBufferFree } :
                    nullptr;
            }

            /// <summary>
            /// Get the global groups of a user.
            /// </summary>
            /// <param name="user_name">The user name</param>
            /// <returns>A tuple including the information and the array size</returns>
            static std::tuple<std::shared_ptr<GROUP_USERS_INFO_0[]>, size_t> get_global_groups(const LSA_UNICODE_STRING& user_name)
            {
                DWORD count_received;
                DWORD count_to_receive;
                PGROUP_USERS_INFO_0 result;
                std::wstring user_name_inner{ user_name.Buffer, user_name.Length / sizeof(wchar_t) };

                return NERR_Success == NetUserGetGroups(nullptr, user_name_inner.c_str(), 0, reinterpret_cast<uint8_t**>(&result), MAX_PREFERRED_LENGTH, &count_received, &count_to_receive) ?
                    std::make_tuple(std::shared_ptr<GROUP_USERS_INFO_0[]>{ result, NetApiBufferFree }, count_received) :
                    std::make_tuple(nullptr, 0);
            }

            /// <summary>
            /// Get the local groups of a user.
            /// </summary>
            /// <param name="user_name">The user name</param>
            /// <returns>A tuple including the information and the array size</returns>
            static std::tuple<std::shared_ptr<LOCALGROUP_USERS_INFO_0[]>, size_t> get_local_groups(const LSA_UNICODE_STRING& user_name)
            {
                DWORD count_received;
                DWORD count_to_receive;
                PLOCALGROUP_USERS_INFO_0 result;
                std::wstring user_name_inner{ user_name.Buffer, user_name.Length / sizeof(wchar_t) };

                return NERR_Success == NetUserGetLocalGroups(nullptr, user_name_inner.c_str(), 0, 0, reinterpret_cast<uint8_t**>(&result), MAX_PREFERRED_LENGTH, &count_received, &count_to_receive) ?
                    std::make_tuple(std::shared_ptr<LOCALGROUP_USERS_INFO_0[]>{ result, NetApiBufferFree }, count_received) :
                    std::make_tuple(nullptr, 0);
            }

            /// <summary>
            /// Lookup the LUID of a privilege name.
            /// </summary>
            /// <param name="name">The privilege name</param>
            /// <returns>The LUID</returns>
            static std::optional<LUID> lookup_privilege_value(const LSA_UNICODE_STRING& name)
            {
                LUID result;
                std::wstring name_inner{ name.Buffer, name.Length / sizeof(wchar_t) };

                return LookupPrivilegeValueW(nullptr, name_inner.c_str(), &result) ? std::make_optional(result) : std::nullopt;
            }

            /// <summary>
            /// Get an environment variable as a path.
            /// </summary>
            /// <param name="name">The name of the environment variable</param>
            /// <returns>The path</returns>
            static std::optional<std::filesystem::path> get_enviroment_variable_as_path(const char* name)
            {
                size_t size;

                // Get the required size of the environment variable.
                if (getenv_s(&size, nullptr, 0, name) != 0 || size == 0)
                {
                    return std::nullopt;
                }

                std::string result;
                result.resize(size);

                // Get the environment variable.
                return getenv_s(&size, result.data(), result.size(), name) == 0 ? std::make_optional<std::filesystem::path>(result) : std::nullopt;
            }

            /// <summary>
            /// Arrange the pointer in a new base address.
            /// </summary>
            /// <param name="ptr">The pointer</param>
            /// <param name="orignal_base">The original base address</param>
            /// <param name="new_base">The new base address</param>
            template<typename TAny>
            inline static void fix_up_pointer(TAny*& ptr, void* orignal_base, void* new_base)
            {
                ptr = ptr != nullptr ?
                    reinterpret_cast<TAny*>(reinterpret_cast<uint8_t*>(new_base) + (reinterpret_cast<uint8_t*>(ptr) - reinterpret_cast<uint8_t*>(orignal_base))) :
                    nullptr;
            }

            /// <summary>
            /// Arrange the pointers in the client's address.
            /// </summary>
            /// <param name="profile">The profile</param>
            /// <param name="new_base">The new base address</param>
            static void fix_up_interactive_profile(KERB_INTERACTIVE_PROFILE& profile, void* new_base)
            {
                fix_up_pointer(profile.LogonScript.Buffer, &profile, new_base);
                fix_up_pointer(profile.HomeDirectory.Buffer, &profile, new_base);
                fix_up_pointer(profile.FullName.Buffer, &profile, new_base);
                fix_up_pointer(profile.ProfilePath.Buffer, &profile, new_base);
                fix_up_pointer(profile.HomeDirectoryDrive.Buffer, &profile, new_base);
                fix_up_pointer(profile.LogonServer.Buffer, &profile, new_base);
            }

            /// <summary>
            /// Get the name of the local computer.
            /// </summary>
            /// <returns>The name of the local computer</returns>
            static std::wstring get_computer_name()
            {
                DWORD size = 0;
                std::wstring result;

                // We consider a fault occurs when the size equals zero.
                // The required size contains the terminating null character.
                auto success = GetComputerNameExW(ComputerNameNetBIOS, nullptr, &size);
                if (!success && ((GetLastError() == ERROR_MORE_DATA && size == 0) || (GetLastError() != ERROR_MORE_DATA)))
                {
                    return result;
                }

                result.resize(size - 1);

                if (!GetComputerNameExW(ComputerNameNetBIOS, result.data(), &size))
                {
                    result.clear();
                }

                return result;
            }
        };
    }
}
