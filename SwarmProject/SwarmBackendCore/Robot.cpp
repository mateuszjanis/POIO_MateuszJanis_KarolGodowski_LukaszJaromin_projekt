#include "pch.h"
#include "Robot.h"

using namespace std;

Robot::Robot(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

void Robot::setPosition(int Xshift, int Yshift)
{
    x_pos += Xshift;
    y_pos += Yshift;
}

//void Robot::setVelocity(double vx, double vy)
//{
//    velocity = Vector2D(vx, vy);
//}
//
//void Robot::setForce(double fx, double fy)
//{
//    force = Vector2D(fx, fy);
//}
//
//void Robot::addForce(double fx, double fy)
//{
//    force += Vector2D(fx, fy);
//}
//
//void Robot::addForce(const Vector2D& newForce)
//{
//    force += newForce;
//}
//void Robot::clearForce()
//{
//    force = Vector2D(0.0, 0.0);
//}
//
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
//
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
    double ForceX = 0;
    int moveX;

    int rows = obj_map.size();
    int cols = obj_map[0].size();
    
    int x_min = max(0, x_pos - radius);
    int x_max = min(cols - 1, x_pos + radius);
    int y_min = max(0, y_pos - radius);
    int y_max = min(rows - 1, y_pos + radius);

    for (int i = x_min; i <= x_max; i++) {
        for (int j = y_min; j <= y_max; j++) {

            int dx = i - x_pos;
            int dy = j - y_pos;

            // warunek okręgu
            if (dx * dx + dy * dy <= radius * radius) {
                if (obj_map[i][j] != 0)
                {
                    if (dx > 0)
                    {
                    ForceX += - k * 1 / (dx ^ 2);
                    }
                    else
                    {
                    ForceX += k * 1 / (dx ^ 2);
                    }
                }
                
            }
        }
    }

    moveX = round(ForceX * dt * dt); // policzenie przemieszczenia

    return moveX;

};

int Robot::computeMoveY(std::vector<std::vector<int>> obj_map)
{   
    double ForceY = 0;
    int moveY;

    int rows = obj_map.size();
    int cols = obj_map[0].size();

    int x_min = max(0, x_pos - radius);
    int x_max = min(cols - 1, x_pos + radius);
    int y_min = max(0, y_pos - radius);
    int y_max = min(rows - 1, y_pos + radius);

    

    for (int i = x_min; i <= x_max; i++) {
        for (int j = y_min; j <= y_max; j++) {

            int dx = i - x_pos;
            int dy = j - y_pos;

            // warunek okręgu
            if (dx * dx + dy * dy <= radius * radius) {
                if (obj_map[i][j] != 0)
                {
                    if (dy > 0)
                    {
                        ForceY += -k * 1 / (dy ^ 2);
                    }
                    else
                    {
                        ForceY += k * 1 / (dy ^ 2);
                    }
                }
            }
        }
    }

    moveY = round(ForceY * dt * dt); // policzenie przemieszczenia

    return moveY;

};

//
//
//double Robot::getMaxSpeed() const
//{
//    return maxSpeed;
//}
