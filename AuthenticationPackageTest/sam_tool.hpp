#pragma once

#include "../Infrastructure/nt_sid.h"

#include <functional>

// SAM access masks.
#define SAM_SERVER_CONNECT              0x00000001
#define SAM_SERVER_SHUTDOWN             0x00000002
#define SAM_SERVER_INITIALIZE           0x00000004
#define SAM_SERVER_CREATE_DOMAIN        0x00000008
#define SAM_SERVER_ENUMERATE_DOMAINS    0x00000010
#define SAM_SERVER_LOOKUP_DOMAIN        0x00000020

#define SAM_SERVER_READ                (STANDARD_RIGHTS_READ | SAM_SERVER_ENUMERATE_DOMAINS)
#define SAM_SERVER_WRITE               (STANDARD_RIGHTS_WRITE | SAM_SERVER_SHUTDOWN | SAM_SERVER_INITIALIZE | SAM_SERVER_CREATE_DOMAIN)
#define SAM_SERVER_EXECUTE             (STANDARD_RIGHTS_EXECUTE | SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN)
#define SAM_SERVER_ALL_ACCESS          (STANDARD_RIGHTS_REQUIRED | SAM_SERVER_CONNECT | SAM_SERVER_SHUTDOWN | SAM_SERVER_INITIALIZE | SAM_SERVER_CREATE_DOMAIN | SAM_SERVER_ENUMERATE_DOMAINS | SAM_SERVER_LOOKUP_DOMAIN)

// Domain access masks.
#define DOMAIN_READ_PASSWORD_PARAMETERS 0x00000001
#define DOMAIN_WRITE_PASSWORD_PARAMS    0x00000002
#define DOMAIN_READ_OTHER_PARAMETERS    0x00000004
#define DOMAIN_WRITE_OTHER_PARAMETERS   0x00000008
#define DOMAIN_CREATE_USER              0x00000010
#define DOMAIN_CREATE_GROUP             0x00000020
#define DOMAIN_CREATE_ALIAS             0x00000040
#define DOMAIN_GET_ALIAS_MEMBERSHIP     0x00000080
#define DOMAIN_LIST_ACCOUNTS            0x00000100
#define DOMAIN_LOOKUP                   0x00000200
#define DOMAIN_ADMINISTER_SERVER        0x00000400

#define DOMAIN_READ                    (STANDARD_RIGHTS_READ | DOMAIN_READ_OTHER_PARAMETERS | DOMAIN_GET_ALIAS_MEMBERSHIP)
#define DOMAIN_WRITE                   (STANDARD_RIGHTS_WRITE | DOMAIN_WRITE_PASSWORD_PARAMS | DOMAIN_WRITE_OTHER_PARAMETERS | DOMAIN_CREATE_USER | DOMAIN_CREATE_GROUP | DOMAIN_CREATE_ALIAS | DOMAIN_ADMINISTER_SERVER)
#define DOMAIN_EXECUTE                 (STANDARD_RIGHTS_EXECUTE | DOMAIN_READ_PASSWORD_PARAMETERS | DOMAIN_LIST_ACCOUNTS | DOMAIN_LOOKUP)
#define DOMAIN_ALL_ACCESS              (STANDARD_RIGHTS_REQUIRED | DOMAIN_READ_PASSWORD_PARAMETERS | DOMAIN_WRITE_PASSWORD_PARAMS | DOMAIN_READ_OTHER_PARAMETERS | DOMAIN_WRITE_OTHER_PARAMETERS | DOMAIN_CREATE_USER | DOMAIN_CREATE_GROUP | DOMAIN_CREATE_ALIAS | DOMAIN_GET_ALIAS_MEMBERSHIP | DOMAIN_LIST_ACCOUNTS | DOMAIN_LOOKUP |  DOMAIN_ADMINISTER_SERVER)

// User access masks.
#define USER_READ_GENERAL               0x00000001
#define USER_READ_PREFERENCES           0x00000002
#define USER_WRITE_PREFERENCES          0x00000004
#define USER_READ_LOGON                 0x00000008
#define USER_READ_ACCOUNT               0x00000010
#define USER_WRITE_ACCOUNT              0x00000020
#define USER_CHANGE_PASSWORD            0x00000040
#define USER_FORCE_PASSWORD_CHANGE      0x00000080
#define USER_LIST_GROUPS                0x00000100
#define USER_READ_GROUP_INFORMATION     0x00000200
#define USER_WRITE_GROUP_INFORMATION    0x00000400

#define USER_READ                      (STANDARD_RIGHTS_READ | USER_READ_PREFERENCES | USER_READ_LOGON | USER_READ_ACCOUNT | USER_LIST_GROUPS | USER_READ_GROUP_INFORMATION)
#define USER_WRITE                     (STANDARD_RIGHTS_WRITE | USER_WRITE_PREFERENCES | USER_CHANGE_PASSWORD)
#define USER_EXECUTE                   (STANDARD_RIGHTS_EXECUTE | USER_READ_GENERAL | USER_CHANGE_PASSWORD)
#define USER_ALL_ACCESS                (STANDARD_RIGHTS_REQUIRED | USER_READ_GENERAL | USER_READ_PREFERENCES | USER_WRITE_PREFERENCES | USER_READ_LOGON | USER_READ_ACCOUNT | USER_WRITE_ACCOUNT | USER_CHANGE_PASSWORD | USER_FORCE_PASSWORD_CHANGE | USER_LIST_GROUPS | USER_READ_GROUP_INFORMATION | USER_WRITE_GROUP_INFORMATION)

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// Possible values of the SAM functions.
        /// </summary>
        enum USER_INFORMATION_CLASS
        {
            UserGeneralInformation = 1,
            UserPreferencesInformation = 2,
            UserLogonInformation = 3,
            UserLogonHoursInformation = 4,
            UserAccountInformation = 5,
            UserNameInformation = 6,
            UserAccountNameInformation = 7,
            UserFullNameInformation = 8,
            UserPrimaryGroupInformation = 9,
            UserHomeInformation = 10,
            UserScriptInformation = 11,
            UserProfileInformation = 12,
            UserAdminCommentInformation = 13,
            UserWorkStationsInformation = 14,
            UserControlInformation = 16,
            UserExpiresInformation = 17,
            UserInternal1Information = 18,
            UserParametersInformation = 20,
            UserAllInformation = 21,
            UserInternal4Information = 23,
            UserInternal5Information = 24,
            UserInternal4InformationNew = 25,
            UserInternal5InformationNew = 26
        };

        typedef struct
        {
            uint16_t Length;
            uint16_t MaximumLength;
            uint16_t* Buffer;
        } RPC_SHORT_BLOB, *PRPC_SHORT_BLOB;

        typedef struct
        {
            uint16_t UnitsPerWeek;
            uint8_t* LogonHours;
        } SAMPR_LOGON_HOURS, *PSAMPR_LOGON_HOURS;

        typedef struct
        {
            uint32_t Length;
            uint8_t* SecurityDescriptor;
        } SAMPR_SR_SECURITY_DESCRIPTOR, *PSAMPR_SR_SECURITY_DESCRIPTOR;

        typedef struct
        {
            LARGE_INTEGER LastLogon;
            LARGE_INTEGER LastLogoff;
            LARGE_INTEGER PasswordLastSet;
            LARGE_INTEGER AccountExpires;
            LARGE_INTEGER PasswordCanChange;
            LARGE_INTEGER PasswordMustChange;
            UNICODE_STRING UserName;
            UNICODE_STRING FullName;
            UNICODE_STRING HomeDirectory;
            UNICODE_STRING HomeDirectoryDrive;
            UNICODE_STRING ScriptPath;
            UNICODE_STRING ProfilePath;
            UNICODE_STRING AdminComment;
            UNICODE_STRING WorkStations;
            UNICODE_STRING UserComment;
            UNICODE_STRING Parameters;
            RPC_SHORT_BLOB LmOwfPassword;
            RPC_SHORT_BLOB NtOwfPassword;
            UNICODE_STRING PrivateData;
            SAMPR_SR_SECURITY_DESCRIPTOR SecurityDescriptor;
            unsigned long UserId;
            unsigned long PrimaryGroupId;
            unsigned long UserAccountControl;
            unsigned long WhichFields;
            SAMPR_LOGON_HOURS LogonHours;
            uint16_t BadPasswordCount;
            uint16_t LogonCount;
            uint16_t CountryCode;
            uint16_t CodePage;
            uint8_t LmPasswordPresent;
            uint8_t NtPasswordPresent;
            uint8_t PasswordExpired;
            uint8_t PrivateDataSensitive;
        } SAMPR_USER_ALL_INFORMATION, *PSAMPR_USER_ALL_INFORMATION;

        using SAMPR_HANDLE = void*;
        using sam_free_memory_ptr = NTSTATUS(NTAPI*)(void* buffer);
        using sam_close_handle_ptr = NTSTATUS(NTAPI*)(SAMPR_HANDLE handle);
        using sam_query_information_user_ptr = NTSTATUS(NTAPI*)(SAMPR_HANDLE user_handle, USER_INFORMATION_CLASS type, void* buffer);
        using sam_connect_ptr = NTSTATUS(NTAPI*)(wchar_t* server_name, SAMPR_HANDLE* server_handle, ACCESS_MASK desired_access, BOOLEAN trusted);
        using sam_open_user_ptr = NTSTATUS(NTAPI*)(SAMPR_HANDLE domain_handle, ACCESS_MASK desired_access, ULONG user_id, SAMPR_HANDLE* user_handle);
        using sam_open_domain_ptr = NTSTATUS(NTAPI*)(SAMPR_HANDLE server_handle, ACCESS_MASK desired_access, PSID domain_id, SAMPR_HANDLE* domain_handle);
        /// <summary>
        /// A wrapper for SAM functions.
        /// </summary>
        class sam_tool
        {
        public:

        public:
            sam_tool() : loaded_{}, sam_connect_{}, sam_open_user_{}, sam_open_domain_{}, sam_free_memory_{}, sam_close_handle_{}, query_user_information_{}
            {
                module_ = LoadLibraryW(L"samlib.dll");

                if (module_ != nullptr)
                {
                    loaded_ = true;
                    fetch_function_address_core(sam_connect_, "SamConnect");
                    fetch_function_address_core(sam_open_user_, "SamOpenUser");
                    fetch_function_address_core(sam_open_domain_, "SamOpenDomain");
                    fetch_function_address_core(sam_free_memory_, "SamFreeMemory");
                    fetch_function_address_core(sam_close_handle_, "SamCloseHandle");
                    fetch_function_address_core(query_user_information_, "SamQueryInformationUser");
                }
            }

            virtual ~sam_tool()
            {
                if (module_ != nullptr)
                {
                    FreeLibrary(module_);
                    module_ = nullptr;
                }
            }

            /// <summary>
            /// Query the user all information.
            /// </summary>
            /// <param name="user_sid">The user SID</param>
            /// <returns>The information</returns>
            std::shared_ptr<SAMPR_USER_ALL_INFORMATION> query_user_all_info(PSID user_sid)
            {
                if (!loaded_)
                {
                    return nullptr;
                }

                // Create a SID wrapper for this.
                nt_sid sid{ user_sid };
                if (!sid)
                {
                    return nullptr;
                }

                // Split the SID into its domain ID and RID.
                auto pair = sid.split();
                if (!pair)
                {
                    return nullptr;
                }

                auto[domain_id, rid] = *pair;

                // Connect to the local SAM server.
                SAMPR_HANDLE sam_handle;
                auto status = sam_connect_(nullptr, &sam_handle, SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN, TRUE);
                if (!NT_SUCCESS(status))
                {
                    return nullptr;
                }

                std::shared_ptr<void> sam_handle_scope{ sam_handle, sam_close_handle_ };

                // Open the SAM domain.
                SAMPR_HANDLE domain_handle;
                status = sam_open_domain_(sam_handle, DOMAIN_LOOKUP, domain_id, &domain_handle);
                if (!NT_SUCCESS(status))
                {
                    return nullptr;
                }

                std::shared_ptr<void> domain_handle_scope{ domain_handle, sam_close_handle_ };

                // Open the SAM user.
                SAMPR_HANDLE user_handle;
                status = sam_open_user_(domain_handle, USER_READ_GENERAL | USER_READ_LOGON | USER_READ_ACCOUNT | USER_READ_PREFERENCES, rid, &user_handle);
                if (!NT_SUCCESS(status))
                {
                    return nullptr;
                }

                std::shared_ptr<void> user_handle_scope{ user_handle, sam_close_handle_ };

                // Get the user all information.
                PSAMPR_USER_ALL_INFORMATION result;
                status = query_user_information_(user_handle, UserAllInformation, &result);

                return NT_SUCCESS(status) ?
                    std::shared_ptr<SAMPR_USER_ALL_INFORMATION>{ result, sam_free_memory_ } :
                    nullptr;
            }
        private:
            /// <summary>
            /// Fetch the address of a function within samsrv.dll.
            /// </summary>
            /// <param name="ptr">A pointer to store the address</param>
            /// <param name="name">The name to find</param>
            template<typename TFunctionPointer>
            void fetch_function_address_core(TFunctionPointer& ptr, const char* name)
            {
                ptr = reinterpret_cast<TFunctionPointer>(GetProcAddress(module_, name));
                loaded_ &= (ptr != nullptr);
            }
        private:
            bool loaded_;
            HMODULE module_;
            sam_connect_ptr sam_connect_;
            sam_open_user_ptr sam_open_user_;
            sam_open_domain_ptr sam_open_domain_;
            sam_free_memory_ptr sam_free_memory_;
            sam_close_handle_ptr sam_close_handle_;
            sam_query_information_user_ptr query_user_information_;
        };
    }
}
