#include "pch.h"
#include "Vector2D.h"
#include <cmath>


Vector2D::Vector2D()
    : x(0.0), y(0.0)
{
}

Vector2D::Vector2D(double x, double y)
    : x(x), y(y)
{
}

double Vector2D::length() const
{
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalized() const
{
    double len = length();

    if (len == 0.0)
    {
        return Vector2D(0.0, 0.0);
    }

    return Vector2D(x / len, y / len);
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;

    return *this;
}