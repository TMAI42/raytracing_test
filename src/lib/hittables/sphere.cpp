//
// Created by tmai42 on 12/6/23.
//

#include "sphere.h"

bool sphere::hit(const ray& ray_to_check, double min_ray_t, double max_ray_t, hit_record& record) const {
    // Calculate the vector from the ray's origin to the center of the sphere
    const vector3D origin_to_center = ray_to_check.origin() - center;

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
    const double c = dot(origin_to_center, origin_to_center) - radius * radius;

    // The discriminant determines whether the ray intersects the sphere. It's derived
    // from the quadratic formula. A positive discriminant indicates two points of
    // intersection, zero indicates one point (tangent), and a negative discriminant
    // means no intersection.
    const double discriminant = half_b * half_b - a * c;

    // If the discriminant is greater than or equal to zero, the ray intersects the sphere.
    if (discriminant < 0) return false;

    const double discriminant_sqrt = sqrt(discriminant);

    // Now we are looking for minimal intersection distance in range `valid_intersection_distance`
    double valid_intersection_distance = (-half_b - discriminant_sqrt) / a;
    if (valid_intersection_distance <= min_ray_t || max_ray_t <= valid_intersection_distance) {
        valid_intersection_distance = (-half_b + discriminant_sqrt) / a;
        if (valid_intersection_distance <= min_ray_t || max_ray_t <= valid_intersection_distance)
            return false;
    }

    // In case of getting proper collision in range of "t" we modify hit_record
    record.t = valid_intersection_distance;
    record.hit_point = ray_to_check.at(valid_intersection_distance);
    // We want hit_normal point from sphere center
    const vector3D hit_normal = (record.hit_point - center) / radius;
    record.set_face_normal(ray_to_check, hit_normal);

    return true;

}
