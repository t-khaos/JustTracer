#pragma once

#include <cmath>

struct Vector3 {
    union {
        struct {
            double x,y,z;
        };
        double data[3];
    };

    //矢量构造函数
    Vector3() : data{0,0,0} {}
    Vector3(double _value): data{_value,_value,_value}{}
    Vector3(double _x, double _y, double _z) : data{_x, _y, _z} {}

    //矢量取反
    Vector3 operator-() const { return {-x, -y, -z}; }

    //矢量索引
    double operator[](int i) const { return data[i]; }
    double& operator[](int i) { return data[i]; }

    //矢量赋值
    Vector3& operator+=(const Vector3 &v) {
        *this = (*this) + v;
        return *this;
    }

    Vector3& operator*=(const double& t) {
        *this = (*this) * t;
        return *this;
    }

    Vector3& operator/=(const double& t) {
        return *this *= 1/t;
    }

    //矢量四则运算
    Vector3 operator+(const Vector3 &v) const{
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3 &v) const{
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator*(const Vector3 &v) const{
        return {x * v.x, y * v.y, z * v.z};
    }

    //矢量数乘
    Vector3 operator*(const double& t) const{
        return {t*x, t*y, t*z};
    }

    friend Vector3 operator*( const double& t, const Vector3 &v) {
        return {t*v.x, t*v.y, t*v.z};
    }

    Vector3 operator/(const double& t) const{
        return (*this)*(1/t);
    }

    //矢量取模
    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    //矢量归一化
    Vector3 normalize() const{
        double k = 1/std::sqrt(x * x + y * y + z * z);
        return {x*k,y*k,z*k};
    }

    //矢量点乘
    double dot(const Vector3 &v) const{
        return x * v.x + y * v.y + z * v.z;
    }

    //矢量叉乘
    Vector3 cross(const Vector3 &v)const {
        return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
        };
    }

    //矢量镜面反射
    Vector3 reflect(const Vector3& normal) const{
        double NoV = (*this).dot(normal);
        return (*this) - 2*NoV*normal;
    }
};

typedef Vector3 Vec3;
typedef Vector3 Point3;
typedef Vector3 Color;
