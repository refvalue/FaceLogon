#pragma once

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A wrapper for the WIN32 RECT structure with several helper functions.
        /// </summary>
        struct rectangle : RECT
        {
            rectangle(int x, int y, int width, int height)
            {
                left = x;
                top = y;
                right = x + width;
                bottom = y + height;
            }

            rectangle() : rectangle{ 0, 0, 0, 0 }
            {
            }

            /// <summary>
            /// Get the width.
            /// </summary>
            /// <returns>The width</returns>
            inline int width() const
            {
                return right - left;
            }

            /// <summary>
            /// Get the height.
            /// </summary>
            /// <returns>The height</returns>
            inline int height() const
            {
                return bottom - top;
            }

            /// <summary>
            /// Set the position.
            /// </summary>
            /// <param name="x">The X</param>
            /// <param name="y">The Y</param>
            inline void set_position(int x, int y)
            {
                auto old_width = width();
                auto old_height = height();

                right = x + old_width;
                bottom = y + old_height;
                left = x;
                top = y;
            }

            /// <summary>
            /// Set the width.
            /// </summary>
            /// <param name="value">The width</param>
            inline void width(int value)
            {
                right = left + value;
            }

            /// <summary>
            /// Set the height.
            /// </summary>
            /// <param name="value">The height</param>
            inline void height(int value)
            {
                bottom = top + value;
            }

            /// <summary>
            /// Get the intersection of two rectangles.
            /// </summary>
            /// <param name="right">Another rectangle</param>
            /// <returns>The intersection</returns>
            inline rectangle operator^(const rectangle& right) const
            {
                rectangle result;
                IntersectRect(&result, this, &right);

                return result;
            }

            /// <summary>
            /// Get the union of two rectangles.
            /// </summary>
            /// <param name="right">Another rectangle</param>
            /// <returns>The union</returns>
            inline rectangle operator+(const rectangle& right) const
            {
                rectangle result;
                UnionRect(&result, this, &right);

                return result;
            }

            /// <summary>
            /// Inflate the rectangle.
            /// </summary>
            /// <param name="dx">The delta of X</param>
            /// <param name="dy">The delta of Y</param>
            inline void inflate(int dx, int dy)
            {
                InflateRect(this, dx, dy);
            }

            /// <summary>
            /// Check if all the fields of a rectangle are zero.
            /// </summary>
            /// <returns>True or false</returns>
            inline bool empty() const
            {
                return left == 0 && top == 0 && right == 0 && bottom == 0;
            }

            /// <summary>
            /// Get the client rectangle of a window.
            /// </summary>
            /// <param name="handle">The window handle</param>
            /// <returns>The rectangle</returns>
            inline static rectangle client_from(HWND handle)
            {
                rectangle result;
                GetClientRect(handle, &result);

                return result;
            }
        };
    }
}
