//
// Created by tmai42 on 12/6/23.
//

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "IHittable.hpp"
#include "Vector3D.hpp"
#include "Interval.h"

class Sphere {
public:
    Sphere(Point3D center, double radius) : m_center(center), m_radius(radius) {}

    [[nodiscard]] Point3D GetCenter() const { return m_center; };

    bool CheckHit(const Ray &ray_to_check, Interval<double> distance_interval, HitResult &record) const{
        // Calculate the vector from the Ray's GetOrigin to the m_center of the Sphere
        const Vector3D origin_to_center = ray_to_check.GetOrigin() - m_center;

        // The coefficients a, b, and c are derived from the equation of a Sphere
        // and the Ray in vector form. The equation for a Sphere centered at the
        // GetOrigin with m_radius r is X^2 + Y^2 + Z^2 = r^2. For a Ray, the equation is
        // P(t) = A + tb, where P is a point on the Ray at time t, A is the GetOrigin,
        // and b is the GetDirection.

        // a is the DotProduct product of the GetDirection of the Ray with itself,
        // which simplifies to the square of the Length of the GetDirection vector.
        const double a = DotProduct(ray_to_check.GetDirection(), ray_to_check.GetDirection());

        // b is derived from rearranging the Sphere's equation to form a quadratic equation
        // in terms of t. It involves the DotProduct product of the vector from the Ray's GetOrigin to
        // the Sphere m_center and the Ray's GetDirection, multiplied by 2.
        const double half_b = DotProduct(origin_to_center, ray_to_check.GetDirection());

        // c represents the square of the Length of the origin_to_center vector minus
        // the square of the Sphere's m_radius. This comes from the Sphere's equation
        // rewritten in terms of the Ray's parameters.
        const double c = DotProduct(origin_to_center, origin_to_center) - m_radius * m_radius;

        // The discriminant determines whether the Ray intersects the Sphere. It's derived
        // from the quadratic formula. A positive discriminant indicates two points of
        // intersection, zero indicates one point (tangent), and a negative discriminant
        // means no intersection.
        const double discriminant = half_b * half_b - a * c;

        // If the discriminant is greater than or equal to zero, the Ray intersects the Sphere.
        if (discriminant < 0) return false;

        const double discriminant_sqrt = sqrt(discriminant);

        // Now we are looking for minimal intersection distance in range `valid_intersection_distance`
        double valid_intersection_distance = (-half_b - discriminant_sqrt) / a;
        if (!distance_interval.surrounds(valid_intersection_distance)) {
            valid_intersection_distance = (-half_b + discriminant_sqrt) / a;
            if (!distance_interval.surrounds(valid_intersection_distance))
                return false;
        }

        // In case of getting proper collision in range of "t" we modify HitResult
        record.t = valid_intersection_distance;
        record.hit_point = ray_to_check.at(valid_intersection_distance);
        // We want hit_normal point from Sphere m_center
        const Vector3D hit_normal = (record.hit_point - m_center) / m_radius;
        record.SetFaceNormal(ray_to_check, hit_normal);

        return true;
    }

private:
    double m_radius;
    Point3D m_center;
};


#endif //SPHERE_HPP
