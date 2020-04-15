#pragma once

#include <memory>
#include <vector>
#include <optional>

namespace glasssix
{
    namespace cassius
    {
        class Cassius;
    }

    namespace longinus
    {
        class LonginusDetector;
    }

    namespace hello
    {
        /// <summary>
        /// A service for face detection.
        /// </summary>
        class face_detector
        {
        public:
            face_detector();

            virtual ~face_detector() = default;

            /// <summary>
            /// Detect the largest face in a gray image and retrieve the feature array.
            /// </summary>
            /// <param name="gray_image">The gray image</param>
            /// <param name="width">The width in pixels</param>
            /// <param name="height">The height in pixels</param>
            /// <returns>The feature array</returns>
            std::optional<std::vector<float>> largest_feature(const uint8_t* gray_image, int width, int height) const;
        private:
            std::shared_ptr<glasssix::cassius::Cassius> extractor_;
            std::shared_ptr<glasssix::longinus::LonginusDetector> detector_;
        private:
            static constexpr int channels_ = 1;
            static constexpr float default_scale_ = 1.1f;
            static constexpr int default_min_size_ = 24;
            static constexpr int default_min_neighbors_ = 3;
        };
    }
}
