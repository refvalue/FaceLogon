#pragma once

#include "rectangle.hpp"

#include <memory>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A helper for making bitmap clippings without support for padding bytes.
        /// </summary>
        class bitmap_clipping
        {
        public:
            bitmap_clipping(std::shared_ptr<uint8_t[]> data, int width, int height, const rectangle& area) : bitmap_clipping{ data, width, height, default_pixel_bytes_, area }
            {

            }

            bitmap_clipping(std::shared_ptr<uint8_t[]> data, int width, int height, int pixel_bytes, const rectangle& area) : pixel_bytes_{ pixel_bytes }, stride_{}
            {
                // Get the intersection.
                clipping_area_ = rectangle{ 0, 0, width, height } ^ area;

                // Make a copy of the clipping data.
                if (!clipping_area_.empty())
                {
                    auto source_stride = pixel_bytes * width;
                    stride_ = pixel_bytes_ * clipping_area_.width();
                    clipping_data_.reset(new uint8_t[stride_ * clipping_area_.height()]);

                    // Copy the clipping data by scanning lines.
                    auto ptr = clipping_data_.get();
                    for (int y = clipping_area_.top; y < clipping_area_.height(); y++, ptr += stride_)
                    {
                        memcpy(ptr, data.get() + source_stride * y + clipping_area_.left * pixel_bytes_, stride_);
                    }
                }
            }

            virtual ~bitmap_clipping() = default;

            /// <summary>
            /// Check if the data is valid.
            /// </summary>
            /// <returns>True on valid</returns>
            inline operator bool() const
            {
                return !clipping_area_.empty() && clipping_data_;
            }

            /// <summary>
            /// Get the start address of the clipping.
            /// </summary>
            /// <returns>The start address of the clipping</returns>
            inline operator uint8_t*() const
            {
                return clipping_data_.get();
            }

            /// <summary>
            /// Get the source_stride (in bytes) of the clipping (maybe zero).
            /// </summary>
            /// <returns>The source_stride of the clipping</returns>
            inline int stride() const
            {
                return stride_;
            }

            /// <summary>
            /// Retrieve the width of the clipping (maybe zero).
            /// </summary>
            /// <returns>The width of the clipping</returns>
            inline int width() const
            {
                return clipping_area_.width();
            }

            /// <summary>
            /// Retrieve the height of the clipping (maybe zero).
            /// </summary>
            /// <returns>The height of the clipping</returns>
            inline int height() const
            {
                return clipping_area_.height();
            }
        private:
            int stride_;
            int pixel_bytes_;
            rectangle clipping_area_;
            std::shared_ptr<uint8_t[]> clipping_data_;
        private:
            /// <summary>
            /// We support gray-8 by default.
            /// </summary>
            static constexpr int default_pixel_bytes_ = 1;
        };
    }
}
