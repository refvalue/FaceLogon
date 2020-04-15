#include "stdafx.h"
#include "common.hpp"
#include "authentication.h"
#include "common_allocator.hpp"
#include "../Infrastructure/nt_sid.h"
#include "../Infrastructure/simple_face_search.h"
#include "../Infrastructure/database_manipulator.h"
#include "../Infrastructure/glasssix_hello_interactive_logon.hpp"

#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>

namespace glasssix
{
    namespace hello
    {
        void authentication::logon_terminated(PLUID logon_id)
        {
        }

        NTSTATUS authentication::initialize_package(ULONG authentication_package_id, PLSA_DISPATCH_TABLE lsa_dispatch_table, PLSA_STRING database, PLSA_STRING confidentiality, PLSA_STRING* authentication_package_name)
        {
            if (lsa_dispatch_table == nullptr || authentication_package_name == nullptr)
            {
                return STATUS_INVALID_PARAMETER;
            }

            dispatch_table_ = *reinterpret_cast<PLSA_SECPKG_FUNCTION_TABLE>(lsa_dispatch_table);
            // database_path_ = *common::get_enviroment_variable_as_path("ProgramData") / "glasssix" / "hello" / "account.db";

            // Create the package name using a temporary allocator. 
            *authentication_package_name = common_allocator::standalone_string(dispatch_table_, package_name_);

            return STATUS_SUCCESS;
        }

        NTSTATUS authentication::call_package(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
        {
            return STATUS_NOT_IMPLEMENTED;
        }

        NTSTATUS authentication::call_package_untrusted(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
        {
            if (protocol_submit_buffer == nullptr || submit_buffer_length < sizeof(glasssix_hello_interactive_logon))
            {
                return STATUS_INVALID_PARAMETER;
            }

            // Retrieve the call information.
            auto call_info = static_cast<glasssix_hello_interactive_logon*>(protocol_submit_buffer);
            call_info->redirect(protocol_submit_buffer);

            // Query the feature.
            database_manipulator manipulator{ database_path_ };
            auto feature = manipulator.query_feature(*call_info);

            if (!feature || feature->empty())
            {
                return STATUS_NO_SUCH_USER;
            }

            std::vector<float> caller_feature{ static_cast<float*>(call_info->feature_data), static_cast<float*>(call_info->feature_data) + call_info->feature_size / sizeof(float) };

            return simple_face_search::match(*feature, caller_feature) ? STATUS_SUCCESS : STATUS_NO_SUCH_USER;
        }

        NTSTATUS authentication::call_package_passthrough(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
        {
            return STATUS_NOT_IMPLEMENTED;
        }

        NTSTATUS authentication::logon_user(PLSA_CLIENT_REQUEST client_request, SECURITY_LOGON_TYPE logon_type, PVOID authentication_information, PVOID client_authentication_base, ULONG authentication_information_length, PVOID* profile_buffer, PULONG profile_buffer_length, PLUID logon_id, PNTSTATUS sub_status, PLSA_TOKEN_INFORMATION_TYPE token_information_type, PVOID* token_information, PLSA_UNICODE_STRING* account_name, PLSA_UNICODE_STRING* authenticating_authority, PLSA_UNICODE_STRING* machine_name)
        {
            std::wofstream log{ R"(C:\logon_user.txt)", std::ios::trunc };

            // This implementation supports interactive logon and unlock logon initially.
            auto item = std::find_if(std::cbegin(supported_logon_types_), std::cend(supported_logon_types_), [&](SECURITY_LOGON_TYPE item) { return logon_type == item; });
            if (item == std::cend(supported_logon_types_))
            {
                return STATUS_INVALID_LOGON_TYPE;
            }

            if (client_request == nullptr || logon_id == nullptr || sub_status == nullptr || token_information_type == nullptr || token_information == nullptr || account_name == nullptr || authentication_information_length < sizeof(glasssix_hello_interactive_logon))
            {
                return STATUS_INVALID_PARAMETER;
            }

            // Retrieve the logon information.
            auto logon_info = static_cast<glasssix_hello_interactive_logon*>(authentication_information);
            logon_info->redirect(authentication_information);

            log << logon_info->user_name.Buffer << std::endl;

            // Set the necessary account name.
            auto account_info = common::lookup_account(logon_info->user_name);
            if (!account_info)
            {
                return STATUS_NO_SUCH_USER;
            }

            NTSTATUS status = STATUS_SUCCESS;

            log << L"1" << std::endl;

            //// Call the service to authenticate the user.
            //auto status = call_package_untrusted(client_request, authentication_information, client_authentication_base, authentication_information_length, profile_buffer, profile_buffer_length, sub_status);
            //if (!NT_SUCCESS(status))
            //{
            //    return status;
            //}

            *account_name = common_allocator::standalone_clone_string(dispatch_table_, logon_info->user_name);
            *sub_status = STATUS_SUCCESS;

            // Set the optional authority.
            if (authenticating_authority != nullptr)
            {
                *authenticating_authority = common_allocator::standalone_string(dispatch_table_, account_info->domain);
            }

            // Set the machine name.
            if (machine_name != nullptr)
            {
                *machine_name = common_allocator::standalone_string(dispatch_table_, common::get_computer_name());
            }

            // Allocate the client profile buffer.
            if (profile_buffer != nullptr && profile_buffer_length != nullptr)
            {
                status = set_client_profile_core(account_info->sid, client_request, profile_buffer, profile_buffer_length);
                if (!NT_SUCCESS(status))
                {
                    return status;
                }
            }

            log << L"2" << std::endl;

            // Allocate a LUID for the logon ID.
            if (!AllocateLocallyUniqueId(logon_id))
            {
                return STATUS_NO_MEMORY;
            }

            // Get token information V2.
            *token_information_type = LsaTokenInformationV2;
            status = get_token_information_core(*account_info, *logon_info, token_information);
            if (!NT_SUCCESS(status))
            {
                return status;
            }

            log << L"3" << std::endl;

            status = dispatch_table_.CreateLogonSession(logon_id);
            if (!NT_SUCCESS(status))
            {
                return STATUS_LOGON_SESSION_COLLISION;
            }

            log << L"4" << std::endl;

            return STATUS_SUCCESS;
        }

        NTSTATUS authentication::set_client_profile_core(nt_sid& user_sid, PLSA_CLIENT_REQUEST client_request, PVOID* profile_buffer, PULONG profile_buffer_length)
        {
            std::wofstream log{ R"(C:\set_client_profile_core.txt)", std::ios::trunc };
            common_allocator profile_allocator{ dispatch_table_, true };

            *profile_buffer = nullptr;
            *profile_buffer_length = 0;

            log << L"1" << std::endl;

            // Get the user information in SAM.
            auto local_buffer = profile_allocator.allocate_interactive_profile(user_sid);
            if (local_buffer == nullptr)
            {
                return ERROR_NO_SUCH_USER;
            }
            
            auto size = static_cast<uint32_t>(profile_allocator.size());

            log << L"size: " << size << std::endl;

            // Allocate the client buffer.
            auto status = dispatch_table_.AllocateClientBuffer(client_request, size, profile_buffer);
            if (!NT_SUCCESS(status))
            {
                return STATUS_NO_MEMORY;
            }

            log << L"2" << std::endl;

            // Copy data to the client buffer.
            common::fix_up_interactive_profile(*local_buffer, *profile_buffer);
            status = dispatch_table_.CopyToClientBuffer(client_request, size, *profile_buffer, local_buffer);
            if (!NT_SUCCESS(status))
            {
                dispatch_table_.FreeClientBuffer(client_request, *profile_buffer);
                *profile_buffer = nullptr;

                return STATUS_NO_MEMORY;
            }

            log << "3" << std::endl;

            *profile_buffer_length = size;

            return STATUS_SUCCESS;
        }

        void authentication::add_user_groups_core(common_allocator& allocator, const UNICODE_STRING& user_name, PLSA_TOKEN_INFORMATION_V2 info)
        {
            // Retrieve all groups of the account.
            size_t index = 0;
            constexpr uint32_t group_count = 2;

            // Allocate a memory block for the groups.
            info->Groups = allocator.allocate_zero_extra<TOKEN_GROUPS>(sizeof(SID_AND_ATTRIBUTES) * group_count);

            info->Groups->Groups[index].Sid = allocator.clone_sid(info->User.User.Sid, DOMAIN_GROUP_RID_USERS);
            info->Groups->Groups[index].Attributes = SE_GROUP_ENABLED | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_MANDATORY;
            index++;

            // Add the authenticated user.
            nt_sid authenticated_user_sid{ WinAuthenticatedUserSid };
            info->Groups->Groups[index].Sid = allocator.clone_sid(authenticated_user_sid);
            info->Groups->Groups[index].Attributes = SE_GROUP_ENABLED | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_MANDATORY;
            index++;

            info->Groups->GroupCount = static_cast<uint32_t>(index);
        }

        NTSTATUS authentication::get_primary_group_core(common_allocator& allocator, const UNICODE_STRING& user_name, PLSA_TOKEN_INFORMATION_V2 info)
        {
            auto user_info = common::get_user_info(user_name);
            if (!user_info)
            {
                return STATUS_NO_SUCH_USER;
            }

            info->PrimaryGroup.PrimaryGroup = allocator.clone_sid(user_info->usri4_user_sid, user_info->usri4_primary_group_id);

            return STATUS_SUCCESS;
        }

        NTSTATUS authentication::get_token_information_core(account_info& account, glasssix_hello_interactive_logon& logon, void** token_info)
        {
            // Create token information.
            common_allocator token_allocator{ dispatch_table_ };
            auto info = token_allocator.allocate_zero<LSA_TOKEN_INFORMATION_V2>();
            *token_info = info;

            // Set default fields.
            info->Privileges = nullptr;
            info->Owner.Owner = nullptr;
            info->DefaultDacl.DefaultDacl = nullptr;
            info->ExpirationTime.QuadPart = MAXLONGLONG;

            // Copy the user SID to the token information.
            info->User.User.Sid = token_allocator.clone_sid(account.sid);
            info->User.User.Attributes = 0;

            // Set the primary group.
            auto status = get_primary_group_core(token_allocator, logon.user_name, info);
            if (!NT_SUCCESS(status))
            {
                return status;
            }

            // Add user groups.
            add_user_groups_core(token_allocator, logon.user_name, info);

            return STATUS_SUCCESS;
        }
    }
}
