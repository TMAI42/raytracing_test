//
// Created by tmai42 on 12/7/23.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "hittables/IHittable.hpp"
#include "TimeTracker.hpp"
#include "Ray.hpp"
#include "ColorRGB.hpp"

#include <mutex>

//TODO: optimize camera, cause after separation into own class we get +0.10s performance loss
class Camera {

public:
    static Camera* GetCamera() {
        std::lock_guard<std::mutex> lock_guard(m_mutex);
        return (ptr_camera_instance) ? ptr_camera_instance : new Camera();

    }

    void Render(const IHittable& scene){
        std::lock_guard<std::mutex> lock_guard(m_mutex);

        ScopeTimeTracker rendering_time_tracker("Rendering");

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Point3D pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                Vector3D ray_direction = pixel_center - camera_center;
                Ray ray(camera_center, ray_direction);

                ColorRGB pixel_color = CalculateRayColor(ray, scene);
                write_color(std::cout, pixel_color);

                std::cout << '\t';
            }
            std::cout << '\n';
        }
        std::clog << "\rDone.                 \n";

    }

    Camera(Camera& other) = delete;
    Camera operator=(Camera& other) = delete;

protected:
    Camera() = default;
    ~Camera() = default;

    ColorRGB CalculateRayColor(const Ray& ray, const IHittable& scene) {

        HitResult hit_result;
        if (scene.CheckHit(ray, Interval{0.0, 100.0}, hit_result)) { //TODO: add Interval as parameter
            return 0.5 * (hit_result.hit_normal + ColorRGB(1, 1, 1));
        }

        //TODO: add gradient as brush
        const Vector3D unit_direction = unit_vector(ray.GetDirection());
        const double a = 0.5*(unit_direction.Y() + 1.0);
        return (1.0-a) * ColorRGB(1.0, 1.0, 1.0) + a * ColorRGB(0.5, 0.7, 1.0);
    }

protected:
    double aspect_ratio = 16.0 / 9.0;
    u_int32_t image_width = 2160;
    u_int32_t image_height = [this]() constexpr {
        auto _image_height = static_cast<u_int32_t>(image_width / aspect_ratio);
        return (_image_height < 1) ? 1 : _image_height;
    }();

    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    double focal_length = 1.0;
    Point3D camera_center {0, 0, 0};

    Vector3D viewport_u {viewport_width, 0, 0};
    Vector3D viewport_v {0, -viewport_height, 0};

    Vector3D pixel_delta_u = viewport_u / image_width;
    Vector3D pixel_delta_v = viewport_v / image_height;

    Point3D viewport_upper_left = camera_center
                                  - Vector3D(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    Point3D pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

private:
    static Camera * ptr_camera_instance;
    static std::mutex m_mutex;

};

Camera* Camera::ptr_camera_instance{nullptr};
std::mutex Camera::m_mutex;

#endif //CAMERA_HPP
