//
// Created by tmai42 on 12/5/23.
//

#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include <cmath>
#include <iostream>

struct vector3D {
    double XYZ[3];

    vector3D() : XYZ{0, 0, 0} {}

    vector3D(double X, double Y, double Z) : XYZ{X, Y, Z} {}

    [[nodiscard]] double x() const { return XYZ[0]; }

    [[nodiscard]] double y() const { return XYZ[1]; }

    [[nodiscard]] double z() const { return XYZ[2]; }

    vector3D operator-() const{ return vector3D{-XYZ[0], -XYZ[1], -XYZ[2]}; }

    double operator[](int i) const { return XYZ[i]; }

    double &operator[](int i) { return XYZ[i]; }

    vector3D &operator+=(const vector3D &v) {
        XYZ[0] += v.XYZ[0];
        XYZ[1] += v.XYZ[1];
        XYZ[2] += v.XYZ[2];
        return *this;
    }

    vector3D &operator*=(double t) {
        XYZ[0] *= t;
        XYZ[1] *= t;
        XYZ[2] *= t;
        return *this;
    }

    vector3D &operator/=(double t) {
        return *this *= 1 / t;
    }

    [[nodiscard]] double length() const {
        return sqrt(length_squared());
    }

    [[nodiscard]] double length_squared() const {
        return XYZ[0] * XYZ[0] + XYZ[1] * XYZ[1] + XYZ[2] * XYZ[2];
    }

};


using point3D = vector3D;


inline std::ostream &operator<<(std::ostream &out, const vector3D &v) {
    return out << v.XYZ[0] << ' ' << v.XYZ[1] << ' ' << v.XYZ[2];
}

inline vector3D operator+(const vector3D &u, const vector3D &v) {
    return {u.XYZ[0] + v.XYZ[0], u.XYZ[1] + v.XYZ[1], u.XYZ[2] + v.XYZ[2]};
}

inline vector3D operator-(const vector3D &u, const vector3D &v) {
    return {u.XYZ[0] - v.XYZ[0], u.XYZ[1] - v.XYZ[1], u.XYZ[2] - v.XYZ[2]};
}

inline vector3D operator*(const vector3D &u, const vector3D &v) {
    return {u.XYZ[0] * v.XYZ[0], u.XYZ[1] * v.XYZ[1], u.XYZ[2] * v.XYZ[2]};
}

inline vector3D operator*(double t, const vector3D &v) {
    return {t * v.XYZ[0], t * v.XYZ[1], t * v.XYZ[2]};
}

inline vector3D operator*(const vector3D &v, double t) {
    return t * v;
}

inline vector3D operator/(vector3D v, double t) {
    return (1 / t) * v;
}

inline double dot(const vector3D &u, const vector3D &v) {
    return u.XYZ[0] * v.XYZ[0] + u.XYZ[1] * v.XYZ[1] + u.XYZ[2] * v.XYZ[2];
}

inline vector3D cross(const vector3D &u, const vector3D &v) {
    return {u.XYZ[1] * v.XYZ[2] - u.XYZ[2] * v.XYZ[1], u.XYZ[2] * v.XYZ[0] - u.XYZ[0] * v.XYZ[2],
            u.XYZ[0] * v.XYZ[1] - u.XYZ[1] * v.XYZ[0]};
}

inline vector3D unit_vector(vector3D v) {
    return v / v.length();
}

#endif //VECTOR_3D_HPP
