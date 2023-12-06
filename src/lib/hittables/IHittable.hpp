#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.hpp"
#include "Interval.h"

struct HitResult {
    Point3D hit_point;
    Vector3D hit_normal;
    double t; // actually this is distance from Ray casting point, but conventionally it is called t
    bool outside_hit;

    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit Length.
    void SetFaceNormal(const Ray& ray_to_check, const Vector3D& outward_normal) {
        outside_hit = DotProduct(ray_to_check.GetDirection(), outward_normal) < 0;
        hit_normal = outside_hit ? outward_normal : -outward_normal;
    }

};

class IHittable {
public:
    virtual ~IHittable() = default;

    virtual bool CheckHit(const Ray& ray_to_check, Interval<double> distance_interval, HitResult& record) const = 0;
};

#endif