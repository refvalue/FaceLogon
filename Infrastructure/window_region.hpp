#pragma once

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A wrapper for a Win32 region.
        /// </summary>
        class window_region
        {
        public:
            window_region(HRGN region) : region_{ region }
            {
            }

            virtual ~window_region()
            {
                if (region_ != nullptr)
                {
                    DeleteObject(region_);
                    region_ = nullptr;
                }
            }

            inline operator HRGN() const
            {
                return region_;
            }

            /// <summary>
            /// Create an inscribedly circle.
            /// </summary>
            /// <param name="x">The X of the top-left cornor</param>
            /// <param name="y">The Y of the top-left cornor</param>
            /// <param name="diameter">The diameter</param>
            /// <returns>The region</returns>
            inline static window_region inscribedly_circle(int x, int y, int diameter)
            {
                return ellipse(x, y, diameter, diameter);
            }

            /// <summary>
            /// Create an ellipse.
            /// </summary>
            /// <param name="x1">The X1</param>
            /// <param name="y1">The Y1</param>
            /// <param name="x2">The X2</param>
            /// <param name="y2">The Y2</param>
            /// <returns>The region</returns>
            inline static window_region ellipse(int x1, int y1, int x2, int y2)
            {
                return window_region{ CreateEllipticRgn(x1, y1, x2, y2) };
            }

            /// <summary>
            /// Apply the region to a window.
            /// </summary>
            /// <param name="handle">The window handle</param>
            inline void apply_to(HWND handle) const
            {
                if (IsWindow(handle))
                {
                    SetWindowRgn(handle, region_, TRUE);
                }
            }
        private:
            HRGN region_;
        };
    }
}
