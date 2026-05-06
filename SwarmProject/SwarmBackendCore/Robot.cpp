#include "pch.h"
#include "Robot.h"


Robot::Robot(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

void Robot::setPosition(int x, int y)
{
    x_pos += x;
    y_pos += y;
}

//void Robot::setVelocity(double vx, double vy)
//{
//    velocity = Vector2D(vx, vy);
//}

//void Robot::setForce(double fx, double fy)
//{
//    force = Vector2D(fx, fy);
//}
//
//void Robot::addForce(double fx, double fy)
//{
//    force += Vector2D(fx, fy);
//}

//void Robot::addForce(const Vector2D& newForce)
//{
//    force += newForce;
//}
//void Robot::clearForce()
//{
//    force = Vector2D(0.0, 0.0);
//}

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

//void Robot::update(double dt)
//{
//    if (dt <= 0.0)
//    {
//        return;
//    }
//
//    Vector2D acceleration = force;
//
//    velocity += acceleration * dt;
//
//    if (velocity.length() > maxSpeed)
//    {
//        velocity = velocity.normalized() * maxSpeed;
//    }
//
//    position += velocity * dt;
//}
//
int Robot::getPosX()
{
    return x_pos;
}

int Robot::getPosY()
{
    return y_pos;
}

//Vector2D Robot::getVelocity() const
//{
//    return velocity;
//}
//
//Vector2D Robot::getForce() const
//{
//    return force;
//}
//
double Robot::getRadius()
{
    return radius;
}

int Robot::computeMoveX(std::vector<std::vector<int>> obj_map)
{
    return 0;
};

int Robot::computeMoveY(std::vector<std::vector<int>> obj_map)
{
    return 0;
};
//
//
//double Robot::getMaxSpeed() const
//{
//    return maxSpeed;
//}
