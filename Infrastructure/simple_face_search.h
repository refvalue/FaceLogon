#pragma once

#include <vector>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// A simple wrapper.
        /// </summary>
        class simple_face_search final
        {
        public:
            /// <summary>
            /// Match two features.
            /// </summary>
            /// <param name="left">The first feature array</param>
            /// <param name="right">The second feature array</param>
            /// <returns>True on match</returns>
            static bool match(const std::vector<float>& left, const std::vector<float>& right);

            /// <summary>
            /// Match two features.
            /// </summary>
            /// <param name="left">The first feature array</param>
            /// <param name="right">The second feature array</param>
            /// <param name="threshold">The threshold up to which the features are evaluated to be the same</param>
            /// <returns>True on match</returns>
            static bool match(const std::vector<float>& left, const std::vector<float>& right, float threshold);
        private:
            static constexpr int dimensions_ = 512;
            static constexpr float default_threshold_ = 60.0f;
            inline static thread_local std::vector<std::vector<uint32_t>> return_ids_;
            inline static thread_local std::vector<std::vector<float>> return_percentages_;
            inline static thread_local std::vector<const float*> left_value_ = { nullptr };
            inline static thread_local std::vector<const float*> right_value_ = { nullptr };
        };
    }
}
