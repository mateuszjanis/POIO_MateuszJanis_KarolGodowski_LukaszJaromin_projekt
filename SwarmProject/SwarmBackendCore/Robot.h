
#pragma once
#include "pch.h"
#include "Vector2D.h"


class Robot
{
private:
    Vector2D position;
    Vector2D velocity;
    Vector2D force;

    double radius;
    double maxSpeed;

public:
    Robot(double x, double y);

    void setPosition(double x, double y);
    void setVelocity(double vx, double vy);

    void setForce(double fx, double fy);
    void addForce(double fx, double fy);
    void addForce(const Vector2D& newForce);
    void clearForce();

    void update(double dt);

    Vector2D getPosition() const;
    Vector2D getVelocity() const;
    Vector2D getForce() const;

    double getRadius() const;
    double getMaxSpeed() const;
};