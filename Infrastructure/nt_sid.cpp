#include "stdafx.h"
#include "nt_sid.h"

namespace glasssix
{
    namespace hello
    {
        nt_sid::nt_sid(PSID sid)
        {
            sid_.reset(sid, [](void* inner) {});
        }

        nt_sid::nt_sid(WELL_KNOWN_SID_TYPE type)
        {
            DWORD size = SECURITY_MAX_SID_SIZE;
            std::shared_ptr<void> sid{ new uint8_t[size], std::default_delete<uint8_t[]>{} };

            // Create a well-known SID.
            if (CreateWellKnownSid(type, nullptr, sid.get(), &size))
            {
                sid_ = sid;
            }
        }

        nt_sid::nt_sid(const UNICODE_STRING& string_sid)
        {
            PSID sid;
            std::wstring sid_clone{ string_sid.Buffer, string_sid.Length / sizeof(wchar_t) };

            // Convert the string SID to a PSID.
            if (ConvertStringSidToSidW(sid_clone.c_str(), &sid))
            {
                sid_.reset(sid, LocalFree);
            }
        }

        nt_sid::nt_sid(const std::shared_ptr<void>& sid) : sid_{ sid }
        {
        }

        nt_sid::nt_sid(std::initializer_list<uint32_t> sub_authorities)
        {
            PSID sid;
            size_t index = 0;
            uint32_t sub_authority_entries[8] = {};
            SID_IDENTIFIER_AUTHORITY nt_authority = SECURITY_NT_AUTHORITY;

            // Apply the sub-authorities.
            for (auto& item : sub_authorities)
            {
                if (index >= std::size(sub_authority_entries))
                {
                    break;
                }

                sub_authority_entries[index++] = item;
            }

            // Allocate a new SID.
            if (AllocateAndInitializeSid(&nt_authority, static_cast<uint8_t>(index), sub_authority_entries[0], sub_authority_entries[1], sub_authority_entries[2], sub_authority_entries[3], sub_authority_entries[4], sub_authority_entries[5], sub_authority_entries[6], sub_authority_entries[7], &sid))
            {
                sid_.reset(sid, FreeSid);
            }
        }

        nt_sid::operator bool() const
        {
            return static_cast<bool>(sid_);
        }

        nt_sid::operator PSID() const
        {
            return sid_.get();
        }

        /// <summary>
        /// Split the SID into its domain ID and RID.
        /// </summary>
        /// <returns>The domain ID and RID</returns>
        std::optional<std::tuple<nt_sid, uint32_t>> nt_sid::split()
        {
            if (!sid_)
            {
                return std::nullopt;
            }

            // An incompelete or irregular SID.
            auto size = GetLengthSid(sid_.get());
            auto count = *GetSidSubAuthorityCount(sid_.get());
            if (size == 0 || count < 1)
            {
                return std::nullopt;
            }

            // Get the RID.
            auto rid = *GetSidSubAuthority(sid_.get(), count - 1);

            // Create the doamin ID and fill in it.
            auto domain_id_size = GetSidLengthRequired(count - 1);
            std::shared_ptr<void> domain_id{ new uint8_t[domain_id_size], std::default_delete<uint8_t[]>{} };
            memcpy(domain_id.get(), sid_.get(), domain_id_size);

            // Set the new sub-authority count.
            (*GetSidSubAuthorityCount(domain_id.get()))--;

            return std::make_tuple(domain_id, rid);
        }
    }
}
