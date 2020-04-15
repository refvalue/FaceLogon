#pragma once

#include <string>
#include <memory>

#include "../Infrastructure/nt_sid.h"

namespace glasssix
{
    namespace hello
    {
        class nt_sid;

        /// <summary>
        /// Account information.
        /// </summary>
        struct account_info
        {
            /// <summary>
            /// The SID type.
            /// </summary>
            SID_NAME_USE type;

            /// <summary>
            /// The domain name of the account.
            /// </summary>
            std::wstring domain;

            /// <summary>
            /// The SID.
            /// </summary>
            nt_sid sid;

            account_info(SID_NAME_USE type, const std::wstring& domain, const std::shared_ptr<void>& sid) : type{ type }, domain{ domain }, sid{ sid }
            {
            }
        };
    }
}
