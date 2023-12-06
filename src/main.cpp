
#include "lib/ray.hpp"
#include "lib/color.hpp"


double hit_sphere(const point3D & sphere_center, double sphere_radius, const ray& ray_to_check) {
    // Calculate the vector from the ray's origin to the center of the sphere
    const vector3D origin_to_center = ray_to_check.origin() - sphere_center;

    // The coefficients a, b, and c are derived from the equation of a sphere
    // and the ray in vector form. The equation for a sphere centered at the
    // origin with radius r is x^2 + y^2 + z^2 = r^2. For a ray, the equation is
    // P(t) = A + tb, where P is a point on the ray at time t, A is the origin,
    // and b is the direction.

    // a is the dot product of the direction of the ray with itself,
    // which simplifies to the square of the length of the direction vector.
    const double a = dot(ray_to_check.direction(), ray_to_check.direction());

    // b is derived from rearranging the sphere's equation to form a quadratic equation
    // in terms of t. It involves the dot product of the vector from the ray's origin to
    // the sphere center and the ray's direction, multiplied by 2.
    const double half_b = dot(origin_to_center, ray_to_check.direction());

    // c represents the square of the length of the origin_to_center vector minus
    // the square of the sphere's radius. This comes from the sphere's equation
    // rewritten in terms of the ray's parameters.
    const double c = dot(origin_to_center, origin_to_center) - sphere_radius * sphere_radius;

    // The discriminant determines whether the ray intersects the sphere. It's derived
    // from the quadratic formula. A positive discriminant indicates two points of
    // intersection, zero indicates one point (tangent), and a negative discriminant
    // means no intersection.
    const double discriminant = half_b * half_b - a * c;

    // If the discriminant is greater than or equal to zero, the ray intersects the sphere.
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

color ray_color(const ray& r) {

    //TODO: add scene for objects instead
    const point3D sphere_center{0,0,-1};

    auto t = hit_sphere(sphere_center, 0.5, r);
    if (t > 0.0) {
        vector3D N = unit_vector(r.at(t) - sphere_center);
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

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            point3D pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vector3D ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);

            std::cout << '\t';
        }
        std::cout << '\n';
    }
    std::clog << "\rDone.                 \n";
}
