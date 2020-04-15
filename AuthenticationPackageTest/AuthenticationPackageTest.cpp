/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1987 - 2000.  Microsoft Corporation.  All rights reserved.

Module Name:
    subauth.c

Abstract:
    Sample SubAuthentication Package.

Environment:
    User mode only.
    Contains NT-specific code.
    Requires ANSI C extensions: slash-slash comments, long external names.

--*/

#include "stdafx.h"
#include "authentication.h"

namespace glasssix
{
    namespace hello
    {
        extern "C"
        {
            void NTAPI LsaApLogonTerminated(PLUID logon_id)
            {
                authentication::logon_terminated(logon_id);
            }

            NTSTATUS NTAPI LsaApInitializePackage(ULONG authentication_package_id, PLSA_DISPATCH_TABLE lsa_dispatch_table, PLSA_STRING database, PLSA_STRING confidentiality, PLSA_STRING* authentication_package_name)
            {
                return authentication::initialize_package(authentication_package_id, lsa_dispatch_table, database, confidentiality, authentication_package_name);
            }

            NTSTATUS NTAPI LsaApCallPackage(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
            {
                return authentication::call_package(client_request, protocol_submit_buffer, client_buffer_base, submit_buffer_length, protocol_return_buffer, return_buffer_length, protocol_status);
            }

            NTSTATUS NTAPI LsaApCallPackageUntrusted(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID* protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
            {
                return authentication::call_package_untrusted(client_request, protocol_submit_buffer, client_buffer_base, submit_buffer_length, protocol_return_buffer, return_buffer_length, protocol_status);
            }

            NTSTATUS NTAPI LsaApCallPackagePassthrough(PLSA_CLIENT_REQUEST client_request, PVOID protocol_submit_buffer, PVOID client_buffer_base, ULONG submit_buffer_length, PVOID *protocol_return_buffer, PULONG return_buffer_length, PNTSTATUS protocol_status)
            {
                return authentication::call_package_passthrough(client_request, protocol_submit_buffer, client_buffer_base, submit_buffer_length, protocol_return_buffer, return_buffer_length, protocol_status);
            }

            NTSTATUS NTAPI LsaApLogonUserEx(PLSA_CLIENT_REQUEST client_request, SECURITY_LOGON_TYPE logon_type, PVOID authentication_information, PVOID client_authentication_base, ULONG authentication_information_length, PVOID* profile_buffer, PULONG profile_buffer_length, PLUID logon_id, PNTSTATUS sub_status, PLSA_TOKEN_INFORMATION_TYPE token_information_type, PVOID* token_information, PLSA_UNICODE_STRING* account_name, PLSA_UNICODE_STRING* authenticating_authority, PLSA_UNICODE_STRING* machine_name)
            {
                return authentication::logon_user(client_request, logon_type, authentication_information, client_authentication_base, authentication_information_length, profile_buffer, profile_buffer_length, logon_id, sub_status, token_information_type, token_information, account_name, authenticating_authority, machine_name);
            }
        }
    }
}
