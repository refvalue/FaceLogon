#pragma once

#include <tuple>
#include <memory>
#include <optional>
#include <functional>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// Support for SIDs.
        /// </summary>
        class nt_sid
        {
        public:
            nt_sid(PSID sid);
            nt_sid(WELL_KNOWN_SID_TYPE type);
            nt_sid(const UNICODE_STRING& string_sid);
            nt_sid(const std::shared_ptr<void>& sid);
            nt_sid(std::initializer_list<uint32_t> sub_authorities);
            virtual ~nt_sid() = default;
            
            operator bool() const;
            operator PSID() const;

            /// <summary>
            /// Split the SID into its domain ID and RID.
            /// </summary>
            /// <returns>The domain ID and RID</returns>
            std::optional<std::tuple<nt_sid, uint32_t>> split();
        private:
            std::shared_ptr<void> sid_;
        };
    }
}
