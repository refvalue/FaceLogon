#pragma once

#include <tuple>
#include <memory>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// An account helper for enumerating information.
        /// </summary>
        class account_helper
        {
        public:
            account_helper() : handle_{}
            {
                LSA_OBJECT_ATTRIBUTES attributes = { sizeof(LSA_OBJECT_ATTRIBUTES) };
                init_success_ = NT_SUCCESS(LsaOpenPolicy(nullptr, &attributes, POLICY_EXECUTE, &handle_));
            }

            virtual ~account_helper()
            {
                if (handle_ != nullptr)
                {
                    LsaClose(handle_);
                    handle_ = nullptr;
                }
            }

            /// <summary>
            /// Enumerate the rights of an account.
            /// </summary>
            /// <param name="sid">The SID</param>
            /// <returns>A tuple including the information and the array size</returns>
            std::tuple<std::shared_ptr<LSA_UNICODE_STRING[]>, size_t> enumerate_rights(PSID sid) const
            {
                if (!init_success_)
                {
                    return { nullptr, 0 };
                }

                ULONG count;
                PLSA_UNICODE_STRING result;
                
                return NT_SUCCESS(LsaEnumerateAccountRights(handle_, sid, &result, &count)) ?
                    std::make_tuple(std::shared_ptr<LSA_UNICODE_STRING[]>(result, LsaFreeMemory), count) :
                    std::make_tuple(nullptr, 0);
            }
        private:
            LSA_HANDLE handle_;
            bool init_success_;
        };
    }
}
