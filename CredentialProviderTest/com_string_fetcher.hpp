#pragma once

#include <string>
#include <combaseapi.h>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A helper to store a string and free the allocated memory safely.
        /// </summary>
        class com_string_fetcher
        {
        public:
            com_string_fetcher(HRESULT& hr, std::wstring& storage) : hr_{ hr }, storage_{ storage }, value_{}
            {
            }

            virtual ~com_string_fetcher()
            {
                if (SUCCEEDED(hr_.get()) && value_ != nullptr)
                {
                    storage_.get() = value_;
                    CoTaskMemFree(value_);
                    value_ = nullptr;
                }
            }

            inline operator wchar_t**()
            {
                return &value_;
            }

        private:
            wchar_t* value_;
            std::reference_wrapper<HRESULT> hr_;
            std::reference_wrapper<std::wstring> storage_;
        };
    }
}
