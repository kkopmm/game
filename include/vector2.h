#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <math.h>

class Vector2
{
public:
    float x = 0;
    float y = 0;
    Vector2() = default;
    ~Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    void operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
    }
    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    void operator-=(const Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
    }
    Vector2 operator*(float scalar) const
    {

        return Vector2(x * scalar, y * scalar);
    }
    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }
    float length() const
    {
        return sqrt(x * x + y * y);
    }
    Vector2 normalize() const
    {
        float len = length();
        if (len == 0)
            return Vector2(0, 0);
        return Vector2(x / len, y / len);
    }
};

#endif // _VECTOR2_H
