#include "stdafx.h"
#include "rectangle.hpp"
#include "accessible_interop.h"

#include <memory>
#include <cassert>

namespace glasssix
{
    namespace hello
    {
        accessible_interop::accessible_interop(IAccessible * obj) : obj_{ obj }
        {
        }

        accessible_interop::accessible_interop(HWND handle)
        {
            auto hr = AccessibleObjectFromWindow(handle, OBJID_CLIENT, IID_PPV_ARGS(&obj_));
            assert(SUCCEEDED(hr));
        }

        /// <summary>
        /// Get the location of the object.
        /// </summary>
        /// <returns>The location</returns>
        std::optional<rectangle> accessible_interop::location() const
        {
            if (obj_ == nullptr)
            {
                return std::nullopt;
            }

            long left;
            long top;
            long width;
            long height;
            auto hr = obj_->accLocation(&left, &top, &width, &height, _variant_t{ static_cast<long>(CHILDID_SELF) });

            return SUCCEEDED(hr) ? std::make_optional<rectangle>(left, top, width, height) : std::nullopt;
        }

        /// <summary>
        /// Try to get the first child of a specified role as an interop object.
        /// </summary>
        /// <param name="role">The role ID</param>
        /// <returns>The child as an interop object</returns>
        std::optional<accessible_interop> accessible_interop::find_first_child_as_interop_by_role(long role)
        {
            auto result = find_first_child_by_role(role);

            return result != nullptr ? std::make_optional<accessible_interop>(result) : std::nullopt;
        }

        /// <summary>
        /// Try to get the first child of a specified role.
        /// </summary>
        /// <param name="role">The role ID</param>
        /// <returns>The child</returns>
        ATL::CComPtr<IAccessible> accessible_interop::find_first_child_by_role(long role)
        {
            if (obj_ == nullptr)
            {
                return nullptr;
            }

            // Get the children count.
            long child_count;
            auto hr = obj_->get_accChildCount(&child_count);

            // Get the children.
            std::unique_ptr<_variant_t[]> children;

            if (SUCCEEDED(hr))
            {
                children = std::make_unique<_variant_t[]>(child_count);
                hr = AccessibleChildren(obj_, 0, child_count, children.get(), &child_count);
            }

            if (SUCCEEDED(hr))
            {
                for (long i = 0; i < child_count; i++)
                {
                    if (children[i].vt == VT_DISPATCH)
                    {
                        _variant_t variant_role;
                        ATL::CComPtr<IAccessible> child;
                        ATL::CComPtr<IDispatch> dispatch = children[i].pdispVal;
                        hr = dispatch.QueryInterface(&child);

                        // Get the role.
                        if (SUCCEEDED(hr))
                        {
                            hr = child->get_accRole(_variant_t{ static_cast<long>(CHILDID_SELF) }, &variant_role);
                        }

                        // Check the role. 
                        if (SUCCEEDED(hr) && variant_role.vt == VT_I4 && variant_role.lVal == role)
                        {
                            return child;
                        }
                    }
                }
            }

            return nullptr;
        }
    }
}
