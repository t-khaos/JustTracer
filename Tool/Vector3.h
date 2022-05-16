#pragma once

#include <cmath>

struct Vector3 {
    union {
        struct {
            double x, y, z;
        };
        struct {
            double r, g, b;
        };
        double data[3];
    };

    //矢量构造函数
    Vector3() : data{0, 0, 0} {}

    Vector3(double _value) : data{_value, _value, _value} {}

    Vector3(double _x, double _y, double _z) : data{_x, _y, _z} {}

    //矢量取反
    Vector3 operator-() const { return {-x, -y, -z}; }

    //矢量索引
    double operator[](int i) const { return data[i]; }

    double &operator[](int i) { return data[i]; }

    //矢量赋值
    Vector3 &operator+=(const Vector3 &v) {
        *this = (*this) + v;
        return *this;
    }

    Vector3 &operator*=(const double &t) {
        *this = (*this) * t;
        return *this;
    }

    Vector3 &operator/=(const double &t) {
        return *this *= 1 / t;
    }

    //矢量四则运算
    Vector3 operator+(const Vector3 &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3 &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator*(const Vector3 &v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    //矢量数乘
    Vector3 operator*(const double &t) const {
        return {t * x, t * y, t * z};
    }

    friend Vector3 operator*(const double &t, const Vector3 &v) {
        return {t * v.x, t * v.y, t * v.z};
    }

    Vector3 operator/(const double &t) const {
        return (*this) * (1 / t);
    }

    //矢量取模
    double Norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    //矢量归一化
    Vector3 Normalize() const {
        double k = 1 / std::sqrt(x * x + y * y + z * z);
        return {x * k, y * k, z * k};
    }

    //矢量点乘
    double Dot(const Vector3 &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    //矢量叉乘
    Vector3 Cross(const Vector3 &v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    //反射
    Vector3 Reflect(const Vector3& N)const{
        return *this - 2*(*this).Dot(N)*N;
    }

    //折射


    //转换到世界坐标系
    Vector3 ToWorld(const Vector3& n){
        //施密特标准正交化
        Vector3 N  = n.Normalize();
        Vector3 t = std::fabs(n.x)<std::fabs(n.y) ? Vector3(1.,0.,0.):Vector3(0.,1.,0.);
        Vector3 T = (t-t.Dot(N)*N).Normalize();
        Vector3 B = T.Cross(N);

        return x*B+y*T+z*N;
    }

    //转换到本地坐标系
};

typedef Vector3 Vec3;
typedef Vector3 Point3;
typedef Vector3 Color;
