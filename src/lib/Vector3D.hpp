//
// Created by tmai42 on 12/5/23.
//

#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include <cmath>
#include <iostream>

struct Vector3D {
    double xyz[3];

    Vector3D() : xyz{0, 0, 0} {}

    Vector3D(double X, double Y, double Z) : xyz{X, Y, Z} {}

    [[nodiscard]] double X() const { return xyz[0]; }

    [[nodiscard]] double Y() const { return xyz[1]; }

    [[nodiscard]] double Z() const { return xyz[2]; }

    Vector3D operator-() const{ return Vector3D{-xyz[0], -xyz[1], -xyz[2]}; }

    double operator[](int i) const { return xyz[i]; }

    double &operator[](int i) { return xyz[i]; }

    Vector3D &operator+=(const Vector3D &v) {
        xyz[0] += v.xyz[0];
        xyz[1] += v.xyz[1];
        xyz[2] += v.xyz[2];
        return *this;
    }

    Vector3D &operator*=(double t) {
        xyz[0] *= t;
        xyz[1] *= t;
        xyz[2] *= t;
        return *this;
    }

    Vector3D &operator/=(double t) {
        return *this *= 1 / t;
    }

    [[nodiscard]] double Length() const {
        return sqrt(SquaredLength());
    }

    [[nodiscard]] double SquaredLength() const {
        return xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2];
    }

};


using Point3D = Vector3D;


inline std::ostream &operator<<(std::ostream &out, const Vector3D &v) {
    return out << v.xyz[0] << ' ' << v.xyz[1] << ' ' << v.xyz[2];
}

inline Vector3D operator+(const Vector3D &u, const Vector3D &v) {
    return {u.xyz[0] + v.xyz[0], u.xyz[1] + v.xyz[1], u.xyz[2] + v.xyz[2]};
}

inline Vector3D operator-(const Vector3D &u, const Vector3D &v) {
    return {u.xyz[0] - v.xyz[0], u.xyz[1] - v.xyz[1], u.xyz[2] - v.xyz[2]};
}

inline Vector3D operator*(const Vector3D &u, const Vector3D &v) {
    return {u.xyz[0] * v.xyz[0], u.xyz[1] * v.xyz[1], u.xyz[2] * v.xyz[2]};
}

inline Vector3D operator*(double t, const Vector3D &v) {
    return {t * v.xyz[0], t * v.xyz[1], t * v.xyz[2]};
}

inline Vector3D operator*(const Vector3D &v, double t) {
    return t * v;
}

inline Vector3D operator/(Vector3D v, double t) {
    return (1 / t) * v;
}

inline double DotProduct(const Vector3D &u, const Vector3D &v) {
    return u.xyz[0] * v.xyz[0] + u.xyz[1] * v.xyz[1] + u.xyz[2] * v.xyz[2];
}

inline Vector3D VectorProduct(const Vector3D &u, const Vector3D &v) {
    return {u.xyz[1] * v.xyz[2] - u.xyz[2] * v.xyz[1], u.xyz[2] * v.xyz[0] - u.xyz[0] * v.xyz[2],
            u.xyz[0] * v.xyz[1] - u.xyz[1] * v.xyz[0]};
}

inline Vector3D unit_vector(Vector3D v) {
    return v / v.Length();
}

#endif //VECTOR_3D_HPP
