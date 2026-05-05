#pragma once 
#include "pch.h"
class Vector2D
{
public:
    int x;
    int y;

    Vector2D();
    Vector2D(double x, double y);

    double length() const;
    Vector2D normalized() const;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(double scalar) const;

    Vector2D& operator+=(const Vector2D& other);
};

