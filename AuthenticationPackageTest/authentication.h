#pragma once

#include "common.hpp"
#include "common_allocator.hpp"

#include <filesystem>

namespace glasssix
{
    namespace hello
    {
        class nt_sid;
        struct account_info;
        struct glasssix_hello_interactive_logon;

        /// <summary>
        /// The authentication major routines.
        /// </summary>
        class authentication final
        {
        public:
            static NTSTATUS NTAPI initialize_package(ULONG authentication_package_id, PLSA_DISPATCH_TABLE lsa_dispatch_table, PLSA_STRING database, PLSA_STRING confidentiality, PLSA_STRING* authentication_package_name);
            static NTSTATUS NTAPI call_package(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status);
            static NTSTATUS NTAPI call_package_untrusted(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status);
            static NTSTATUS NTAPI call_package_passthrough(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID *protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status);
            static NTSTATUS NTAPI logon_user(PLSA_CLIENT_REQUEST client_request, SECURITY_LOGON_TYPE logon_type, PVOID authentication_information, PVOID client_authentication_base, ULONG authentication_information_length, PVOID* profile_buffer, PULONG profile_buffer_length, PLUID logon_id, PNTSTATUS sub_status, PLSA_TOKEN_INFORMATION_TYPE token_information_type, PVOID* token_information, PLSA_UNICODE_STRING* account_name, PLSA_UNICODE_STRING* authenticating_authority, PLSA_UNICODE_STRING* machine_name);
            static void NTAPI logon_terminated(PLUID logon_id);
        private:
            static void add_user_groups_core(common_allocator& allocator, const UNICODE_STRING& user_name, PLSA_TOKEN_INFORMATION_V2 info);
            static NTSTATUS get_token_information_core(account_info& account, glasssix_hello_interactive_logon& logon, void** token_info);
            static NTSTATUS get_primary_group_core(common_allocator& allocator, const UNICODE_STRING& user_name, PLSA_TOKEN_INFORMATION_V2 info);
            static NTSTATUS set_client_profile_core(nt_sid& user_sid, PLSA_CLIENT_REQUEST client_request, PVOID* profile_buffer, PULONG profile_buffer_length);
        private:
            inline static std::filesystem::path database_path_;
            inline static LSA_SECPKG_FUNCTION_TABLE dispatch_table_;
        private:
            static constexpr size_t small_block_size_ = 128;
            static constexpr uint32_t client_buffer_size_ = 32;
            static constexpr char package_name_[] = "GlasssixAuthHelloFace";
            static constexpr SECURITY_LOGON_TYPE supported_logon_types_[] =
            {
                Interactive,
                RemoteInteractive
            };
        };
    }
}
