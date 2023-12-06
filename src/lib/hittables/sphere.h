//
// Created by tmai42 on 12/6/23.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.hpp"
#include "vector3D.hpp"

class sphere {
public:
    sphere(point3D _center, double _radius): center(_center), radius(_radius) {}

    bool hit(const ray& ray_to_check, double min_ray_t, double max_ray_t, hit_record& record) const ;

private:
    double radius;
    point3D center;
};


#endif //SPHERE_H
