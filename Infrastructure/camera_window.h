#pragma once

#include "rectangle.hpp"

#include <memory>
#include <vector>
#include <optional>

namespace glasssix
{
    namespace hippogriff
    {
        class net_camera;
        struct decode_data_info;
    }

    namespace ozymandias
    {
        class video_array_renderer;
    }

    namespace hello
    {
        class face_detector;

        /// <summary>
        /// A window rendering the camera.
        /// </summary>
        class camera_window
        {
        public:
            camera_window(HINSTANCE instance, HWND parent);
            virtual ~camera_window();

            void start_camera();
            static void message_loop();
            std::optional<std::vector<float>> wait_for() const;
        private:
            virtual rectangle calculate_appropriate_location_core() const;
            LRESULT wnd_proc(HWND handle, UINT msg, WPARAM param1, LPARAM param2);
            void detection_routine(const glasssix::hippogriff::decode_data_info& info);
            static LRESULT __stdcall wnd_proc_raw(HWND handle, UINT msg, WPARAM param1, LPARAM param2);
        private:
            HWND handle_;
            HWND parent_handle_;
            std::shared_ptr<face_detector> detector_;
            std::optional<std::vector<float>> feature_;
            std::shared_ptr<glasssix::hippogriff::net_camera> camera_;
            std::shared_ptr<glasssix::ozymandias::video_array_renderer> renderer_;
        private:
            static constexpr int account_picture_size_ = 200;
            static constexpr wchar_t window_class_name_[] = L"GlassixCameraWindowClass";
        };
    }
}
