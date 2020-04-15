#pragma once

#include <memory>
#include <vector>

namespace glasssix
{
    namespace hello
    {
        class common final
        {
        public:
            /// <summary>
            /// Convert a RGBA bitmap to gray8.
            /// </summary>
            /// <param name="buffer">The RGBA buffer</param>
            /// <param name="width">The width</param>
            /// <param name="height">The height</param>
            /// <returns>The converted gray bitmap</returns>
            static std::shared_ptr<uint8_t[]> rgba_to_gray8(const uint8_t* buffer, int width, int height)
            {
                // For a RGBA (32-bit) bitmap, it is always 4-byte aligned with no padding bytes.
                auto ptr = buffer;
                std::shared_ptr<uint8_t[]> result{ new uint8_t[width * height], std::default_delete<uint8_t[]>{} };

                for (int y = 0, i = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++, ptr += 4)
                    {
                        result[i++] = ((*ptr * 38 + *(ptr + 1) * 75 + *(ptr + 2) * 15) >> 7);
                    }
                }

                return result;
            }

            /// <summary>
            /// Decode a text encoded in Base64 and align it as TElement.
            /// </summary>
            /// <param name="text">The text encoded in Base64</param>
            /// <param name="size">The size of the text</param>
            /// <returns>The binary data aligned as TElement</returns>
            template<typename TElement>
            static std::vector<TElement> base64_decode_as(const char* text, size_t size)
            {
                DWORD size_needed;
                std::vector<TElement> result;

                // Acquire the actual size of the binary data.
                if (!CryptStringToBinaryA(text, static_cast<uint32_t>(size), CRYPT_STRING_BASE64, nullptr, &size_needed, nullptr, nullptr))
                {
                    return result;
                }

                auto count = size_needed / sizeof(TElement) + (size_needed % sizeof(TElement) == 0 ? 0 : sizeof(TElement));
                result.resize(count);

                // Decode the text.
                if (!CryptStringToBinaryA(text, static_cast<uint32_t>(size), CRYPT_STRING_BASE64, reinterpret_cast<uint8_t*>(result.data()), &size_needed, nullptr, nullptr))
                {
                    result.clear();
                }

                return result;
            }

            /// <summary>
           /// Convert a container consisting of x-y pairs to an Int32 array.
           /// </summary>
           /// <param name="container">The container</param>
           /// <returns>The Int32 array</returns>
            template<typename TContainer>
            static std::vector<int> x_y_pair_to_int32_array_core(TContainer&& container)
            {
                std::vector<int> result;

                for (auto& item : container)
                {
                    result.emplace_back(static_cast<int>(item.x));
                    result.emplace_back(static_cast<int>(item.y));
                }

                return result;
            }
        };
    }
}
