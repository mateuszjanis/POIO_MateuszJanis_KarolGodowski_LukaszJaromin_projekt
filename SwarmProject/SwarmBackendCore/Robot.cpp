#include "pch.h"
#include "Robot.h"


Robot::Robot(double x, double y)
    : position(x, y),
    velocity(0.0, 0.0),
    force(0.0, 0.0),
    radius(5.0),
    maxSpeed(100.0)
{
}

void Robot::setPosition(double x, double y)
{
    position = Vector2D(x, y);
}

void Robot::setVelocity(double vx, double vy)
{
    velocity = Vector2D(vx, vy);
}

void Robot::setForce(double fx, double fy)
{
    force = Vector2D(fx, fy);
}

void Robot::addForce(double fx, double fy)
{
    force += Vector2D(fx, fy);
}

void Robot::addForce(const Vector2D& newForce)
{
    force += newForce;
}
void Robot::clearForce()
{
    force = Vector2D(0.0, 0.0);
}

//void Robot::computeForce(Map mapa)
//{
//    int rows = matrix.size();
//    int cols = matrix[0].size();
//
//    int x_min = std::max(0, x - range);
//    int x_max = std::min(cols - 1, x + range);
//
//    int y_min = std::max(0, y - range);
//    int y_max = std::min(rows - 1, y + range);
//
//    for (int i = y_min; i <= y_max; i++) {
//        for (int j = x_min; j <= x_max; j++) {
//
//            int dx = j - x;
//            int dy = i - y;
//
//            // warunek okręgu (bez sqrt — szybciej)
//            if (dx * dx + dy * dy <= range * range) {
//                results.emplace_back(j, i); // (x, y)
//            }
//        }
//    }
//}

void Robot::update(double dt)
{
    if (dt <= 0.0)
    {
        return;
    }

    Vector2D acceleration = force;

    velocity += acceleration * dt;

    if (velocity.length() > maxSpeed)
    {
        velocity = velocity.normalized() * maxSpeed;
    }

    position += velocity * dt;
}

Vector2D Robot::getPosition() const
{
    return position;
}

Vector2D Robot::getVelocity() const
{
    return velocity;
}

Vector2D Robot::getForce() const
{
    return force;
}

double Robot::getRadius() const
{
    return radius;
}


double Robot::getMaxSpeed() const
{
    return maxSpeed;
}
