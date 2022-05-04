#pragma once

#include <cmath>

struct Vector3 {
    union {
        struct {
            double x,y,z;
        };
        double data[3];
    };

    Vector3() : data{0,0,0} {}
    Vector3(double value): data{value,value,value}{}
    Vector3(double e0, double e1, double e2) : data{e0, e1, e2} {}

    Vector3 operator-() const { return {-x, -y, -z}; }
    double operator[](int i) const { return data[i]; }
    double& operator[](int i) { return data[i]; }

    Vector3& operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vector3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double dot(const Vector3 &v) const{
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3 &v)const {
        return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
        };
    }

    Vector3 normalized() const{
        return {x/norm(),y/norm(),z/norm()};
    }
};

inline Vector3 operator+(const Vector3 &u, const Vector3 &v) {
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

inline Vector3 operator*(double t, const Vector3 &v) {
    return {t*v.x, t*v.y, t*v.z};
}

inline Vector3 operator*(const Vector3 &v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3& v, double t) {
    return (1/t) * v;
}

typedef Vector3 Vec3;
typedef Vector3 Point3;
typedef Vector3 Color;
