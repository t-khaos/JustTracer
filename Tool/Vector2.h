#pragma once

struct Vector2 {
    union {
        struct {
            float x, y;
        };
        struct {
            float u, v;
        };
        struct {
            float s, t;
        };
        float data[2];
    };

    Vector2() : data{0, 0} {}

    Vector2(float _value) : data{_value, _value} {}

    Vector2(float _x, float _y) : data{_x, _y} {}

    //矢量取反
    Vector2 operator-() const { return {-x, -y}; }

    //矢量索引
    float operator[](int i) const { return data[i]; }

    float &operator[](int i) { return data[i]; }

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