#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

struct hit_record {
    point3D hit_point;
    vector3D hit_normal;
    double t; // actually this is distance from previous hit, but conventionally it is called t
    bool outside_hit;

    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.
    void set_face_normal(const ray& ray_to_check, const vector3D& outward_normal) {
        outside_hit = dot(ray_to_check.direction(), outward_normal) < 0;
        hit_normal = outside_hit ? outward_normal : -outward_normal;
    }


};

struct hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& ray_to_check, double min_ray_t, double max_ray_t, hit_record& record) const = 0;
};

#endif