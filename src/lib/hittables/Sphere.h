//
// Created by tmai42 on 12/6/23.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "IHittable.hpp"
#include "Vector3D.hpp"

class Sphere {
public:
    Sphere(Point3D center, double radius) : m_center(center), m_radius(radius) {}

    bool CheckHit(const Ray &ray_to_check, double min_ray_t, double max_ray_t, HitResult &record) const;

    [[nodiscard]] Point3D GetCenter() const { return m_center; };


private:
    double m_radius;
    Point3D m_center;
};


#endif //SPHERE_H
