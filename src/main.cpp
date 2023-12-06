
#include "lib/ray.hpp"
#include "lib/color.hpp"
#include "lib/hittables/sphere.h"


color ray_color(const ray& r, const sphere& sp) {

    hit_record record;
    if (sp.hit(r, 0.0, 10.0, record)) {
        vector3D N = unit_vector(r.at(record.t) - sp.get_center());
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    //TODO: add gradient as brush
    const vector3D unit_direction = unit_vector(r.direction());
    const double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

//TODO: split into Image, Camera and Render as separate components
int main() {

    // Image

    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr u_int32_t image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    constexpr u_int32_t image_height = []() constexpr {
        constexpr auto image_height = static_cast<u_int32_t>(image_width / aspect_ratio);
        return (image_height < 1) ? 1 : image_height;
    }();

    // Camera

    // Viewport widths less than one are ok since they are real valued.
    constexpr double viewport_height = 2.0;
    constexpr double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    constexpr double focal_length = 1.0;
    const point3D camera_center {0, 0, 0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const vector3D viewport_u {viewport_width, 0, 0};
    const vector3D viewport_v {0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const vector3D pixel_delta_u = viewport_u / image_width;
    const vector3D pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    const point3D viewport_upper_left = camera_center
                               - vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    const point3D pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Scene

    sphere sp{{0,0,-1}, 0.5};

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            point3D pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vector3D ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, sp);
            write_color(std::cout, pixel_color);

            std::cout << '\t';
        }
        std::cout << '\n';
    }
    std::clog << "\rDone.                 \n";
}
