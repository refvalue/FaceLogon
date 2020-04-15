#include "stdafx.h"
#include "common.hpp"
#include "face_detector.h"

#include <algorithm>

#include <cassius.hpp>
#include <LonginusDetector.hpp>

namespace glasssix
{
    namespace hello
    {
        face_detector::face_detector()
        {
            extractor_ = std::make_shared<glasssix::cassius::Cassius>();
            detector_ = std::make_shared<glasssix::longinus::LonginusDetector>();
            detector_->set(glasssix::longinus::FRONTALVIEW_REINFORCE);
        }

        /// <summary>
        /// Detect the largest face in a gray image and retrieve the feature array.
        /// </summary>
        /// <param name="gray_image">The gray image</param>
        /// <param name="width">The width in pixels</param>
        /// <param name="height">The height in pixels</param>
        /// <returns>The feature array</returns>

        std::optional<std::vector<float>> face_detector::largest_feature(const uint8_t * gray_image, int width, int height) const
        {
            // Detect all faces.
            auto faces = detector_->detect(const_cast<uint8_t*>(gray_image), width, height, width, default_min_size_, default_scale_, default_min_neighbors_, 0);
            if (faces.empty())
            {
                return std::nullopt;
            }

            // Get the largest face.
            auto& largest_face = *std::max_element(faces.begin(), faces.end(), [](const glasssix::longinus::FaceRectwithFaceInfo& left, const glasssix::longinus::FaceRectwithFaceInfo& right)
            {
                return left.width * left.height < right.width * right.height;
            });

            // Align the largest face.
            auto aligned_face = detector_->alignFace(
                gray_image,
                1,
                channels_,
                height,
                width,
                { { largest_face.x, largest_face.y, largest_face.height, largest_face.width } },
                { common::x_y_pair_to_int32_array_core(largest_face.pts) });

            // Retrieve the feature array through the aligned face.
            auto features = extractor_->Forward(aligned_face.data(), 1);

            return features.empty() ? std::nullopt : std::make_optional(features.front());
        }
    }
}
