#pragma once

#include <cstdint>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// The interactive logon information.
        /// </summary>
        struct glasssix_hello_interactive_logon
        {
            /// <summary>
            /// Store the original base address within the client process.
            /// </summary>
            void* original_base_address;

            /// <summary>
            /// The user name in string literals.
            /// </summary>
            UNICODE_STRING user_name;

            /// <summary>
            /// The user SID.
            /// </summary>
            UNICODE_STRING user_sid;

            /// <summary>
            /// The feature data.
            /// </summary>
            void* feature_data;

            /// <summary>
            /// The feature size.
            /// </summary>
            size_t feature_size;

            /// <summary>
            /// Redirect the buffers as to the LSA's base address.
            /// </summary>
            /// <param name="old_base_address">The old base address</param>
            void redirect(void* new_base_address)
            {
                auto new_base_address_in_bytes = static_cast<uint8_t*>(new_base_address);
                auto old_base_address_in_bytes = static_cast<uint8_t*>(original_base_address);
                
                feature_data = reinterpret_cast<wchar_t*>(new_base_address_in_bytes + (reinterpret_cast<uint8_t*>(feature_data) - old_base_address_in_bytes));
                user_sid.Buffer = reinterpret_cast<wchar_t*>(new_base_address_in_bytes + (reinterpret_cast<uint8_t*>(user_sid.Buffer) - old_base_address_in_bytes));
                user_name.Buffer = reinterpret_cast<wchar_t*>(new_base_address_in_bytes + (reinterpret_cast<uint8_t*>(user_name.Buffer) - old_base_address_in_bytes));
                original_base_address = new_base_address;
            }
        };
    }
}
