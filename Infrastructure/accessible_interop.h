#pragma once

#include <optional>

struct IAccessible;

namespace glasssix
{
    namespace hello
    {
        struct rectangle;

        /// <summary>
        /// A wrapper for MSAA.
        /// </summary>
        class accessible_interop
        {
        public:
            accessible_interop(HWND handle);
            accessible_interop(IAccessible* obj);
            virtual ~accessible_interop() = default;

            /// <summary>
            /// Get the location of the object.
            /// </summary>
            /// <returns>The location</returns>
            std::optional<rectangle> location() const;

            /// <summary>
            /// Try to get the first child of a specified role as an interop object.
            /// </summary>
            /// <param name="role">The role ID</param>
            /// <returns>The child as an interop object</returns>
            std::optional<accessible_interop> find_first_child_as_interop_by_role(long role);

            /// <summary>
            /// Try to get the first child of a specified role.
            /// </summary>
            /// <param name="role">The role ID</param>
            /// <returns>The child</returns>
            ATL::CComPtr<IAccessible> find_first_child_by_role(long role);
        private:
            ATL::CComPtr<IAccessible> obj_;
        };
    }
}
