#include "stdafx.h"
#include "common.hpp"
#include "rectangle.hpp"
#include "camera_window.h"
#include "window_region.hpp"
#include "face_detector.h"
#include "accessible_interop.h"

#include <string>
#include <fstream>

#include <Hippogriff/net_camera.h>
#include <Hippogriff/decode_data_info.hpp>
#include <Ozymandias/video_array_renderer.h>

using namespace ATL;

namespace glasssix
{
    namespace hello
    {
        camera_window::camera_window(HINSTANCE instance, HWND parent) : parent_handle_{ parent }
        {
            // Register the window class.
            WNDCLASSEX window_class = {};
            window_class.cbSize = sizeof(WNDCLASSEX);
            window_class.style = CS_HREDRAW | CS_VREDRAW;
            window_class.lpfnWndProc = &camera_window::wnd_proc_raw;
            window_class.hInstance = instance;
            window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
            window_class.lpszClassName = window_class_name_;

            RegisterClassExW(&window_class);

            // Create the window.
            auto client_area = rectangle::client_from(parent_handle_);
            auto bounding_area = calculate_appropriate_location_core();
            auto region = window_region::ellipse(0, 0, bounding_area.width(), bounding_area.height());
            handle_ = CreateWindowExW(0, window_class.lpszClassName, nullptr, WS_CHILD | WS_VISIBLE, (client_area.width() - bounding_area.width()) / 2, bounding_area.top, bounding_area.width(), bounding_area.height(), parent, nullptr, instance, this);
            region.apply_to(handle_);
        }

        camera_window::~camera_window()
        {
        }

        /// <summary>
        /// Start the camera.
        /// </summary>
        void camera_window::start_camera()
        {
            // Initialize the feature detector.
            detector_ = std::make_shared<face_detector>();
            
            // Initialize the USB camera.
            renderer_ = std::make_shared<glasssix::ozymandias::video_array_renderer>(handle_);
            camera_ = std::make_shared<glasssix::hippogriff::net_camera>("USB Camera", "cap:////", 25);
            renderer_->set_array(1, 1);
            renderer_->set_data_provider(*camera_, 0, 0);
            camera_->decode_handler += std::bind(&camera_window::detection_routine, this, std::placeholders::_1);
            camera_->connect();
        }

        void camera_window::message_loop()
        {
            MSG msg;
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }

        std::optional<std::vector<float>> camera_window::wait_for() const
        {
            message_loop();

            return feature_;
        }

        void camera_window::detection_routine(const glasssix::hippogriff::decode_data_info& info)
        {
            // Get the feature array of the largest face.
            auto gray_image = common::rgba_to_gray8(info.data, info.width, info.height);
            feature_ = detector_->largest_feature(gray_image.get(), info.width, info.height);
            
            if (IsWindow(handle_))
            {
                PostMessageW(handle_, WM_CLOSE, 0, 0);
            }
        }

        /// <summary>
        /// Calculate the appropriate location of the picture.
        /// </summary>
        /// <returns>The location</returns>
        rectangle camera_window::calculate_appropriate_location_core() const
        {
            rectangle result{ 0, 0, account_picture_size_, account_picture_size_ };

            // Get the relative element.
            accessible_interop window_interop{ parent_handle_ };
            auto relative_element = window_interop.find_first_child_as_interop_by_role(ROLE_SYSTEM_STATICTEXT);
            if (relative_element)
            {
                auto location = relative_element->location();
                if (location)
                {
                    result.set_position(0, location->top - account_picture_size_ - 10);
                }
            }

            return result;
        }

        LRESULT camera_window::wnd_proc(HWND handle, UINT msg, WPARAM param1, LPARAM param2)
        {
            switch (msg)
            {
            case WM_CLOSE:
                camera_.reset();
                renderer_.reset();
                DestroyWindow(handle_);
                PostQuitMessage(0);

                return 0;
            case WM_PAINT:
            {
                PAINTSTRUCT ps = {};
                BeginPaint(handle, &ps);
                EndPaint(handle, &ps);

                return 0;
            }
            default:
                return DefWindowProc(handle, msg, param1, param2);
            }
        }

        LRESULT __stdcall camera_window::wnd_proc_raw(HWND handle, UINT msg, WPARAM param1, LPARAM param2)
        {
            if (msg == WM_CREATE)
            {
                auto param = reinterpret_cast<LPCREATESTRUCT>(param2);
                auto this_ptr = static_cast<camera_window*>(param->lpCreateParams);
                SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_ptr));

                return 0;
            }

            auto this_ptr = reinterpret_cast<camera_window*>(GetWindowLongPtr(handle, GWLP_USERDATA));

            return this_ptr->wnd_proc(handle, msg, param1, param2);
        }
    }
}
