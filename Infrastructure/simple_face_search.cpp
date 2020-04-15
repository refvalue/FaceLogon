#include "stdafx.h"
#include "simple_face_search.h"

#include <IrisvianSearch.hpp>

namespace  glasssix
{
    namespace hello
    {
        /// <summary>
        /// Match two features.
        /// </summary>
        /// <param name="left">The first feature array</param>
        /// <param name="right">The second feature array</param>
        /// <param name="threshold">The threshold up to which the features are evaluated to be the same</param>
        /// <returns>True on match</returns>
        bool simple_face_search::match(const std::vector<float>& left, const std::vector<float>& right)
        {
            return match(left, right, default_threshold_);
        }

        /// <summary>
        /// Match two features.
        /// </summary>
        /// <param name="left">The first feature array</param>
        /// <param name="right">The second feature array</param>
        /// <returns>True on match</returns>
        bool simple_face_search::match(const std::vector<float>& left, const std::vector<float>& right, float threshold)
        {
            // Use thread-local variables to decrease memory reallocatations.
            left_value_.front() = left.data();
            right_value_.front() = right.data();

            glasssix::Irisvian::IrisvianSearch searcher{ &left_value_, dimensions_ };
            searcher.searchVector(&right_value_, 1, return_ids_, return_percentages_);

            return return_percentages_.front().front() > threshold;
        }
    }
}
