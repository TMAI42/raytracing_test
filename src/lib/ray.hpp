//
// Created by tmai42 on 12/5/23.
//

#ifndef RAY_HPP
#define RAY_HPP

#include "vector3D.hpp"

class ray {
public:
    ray() = default;

    ray(const point3D &origin, const vector3D &direction) : orig(origin), dir(direction) {}

    [[nodiscard]] point3D origin() const { return orig; }

    [[nodiscard]] vector3D direction() const { return dir; }

    [[nodiscard]] point3D at(double t) const {
        return orig + t * dir;
    }

private:
    point3D orig;
    vector3D dir;
};

#endif //RAY_HPP