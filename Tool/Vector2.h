#pragma once

struct Vector2 {
    union {
        struct {
            double x, y;
        };
        struct {
            double u, v;
        };
        struct {
            double s, t;
        };
        double data[2];
    };

    Vector2() : data{0, 0} {}

    Vector2(double _value) : data{_value, _value} {}

    Vector2(double _x, double _y) : data{_x, _y} {}

    //矢量取反
    Vector2 operator-() const { return {-x, -y}; }

    //矢量索引
    double operator[](int i) const { return data[i]; }

    double &operator[](int i) { return data[i]; }

    //矢量四则运算
    Vector2 operator+(const Vector2 &v) const {
        return {x + v.x, y + v.y};
    }

    Vector2 operator-(const Vector2 &v) const {
        return {x - v.x, y - v.y};
    }

    Vector2 operator*(const Vector2 &v) const {
        return {x * v.x, y * v.y};
    }
};

typedef Vector2 Vec2;
typedef Vector2 Point2;