//
// Created by tmai42 on 12/5/23.
//

#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3D.hpp"

class Ray {
public:
    Ray() = default;

    Ray(const Point3D &origin, const Vector3D &direction) : m_origin(origin), m_direction(direction) {}

    [[nodiscard]] Point3D GetOrigin() const { return m_origin; }

    [[nodiscard]] Vector3D GetDirection() const { return m_direction; }

    [[nodiscard]] Point3D at(double t) const {
        return m_origin + t * m_direction;
    }

private:
    Point3D m_origin;
    Vector3D m_direction;
};

#endif //RAY_HPP