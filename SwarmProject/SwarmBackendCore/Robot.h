#pragma once
#include "pch.h"
#include <vector>
//#include "Map.h"


class Robot
{
private:

    int radius;
    int x_pos, y_pos;
    double maxSpeed;
    double mass;

public:
    Robot(int x, int y);

    void setPosition(int x, int y);
    //void setVelocity(double vx, double vy);

    //void setForce(double fx, double fy);
    //void addForce(double fx, double fy);
    //void addForce(const Vector2D& newForce);
    //void computeForce(Map mapa); //
    //void clearForce();

    //void update(double dt);

    int getPosX();
    int getPosY();

    // do dopisania
    int computeMoveX(std::vector<std::vector<int>> obj_map);
    int computeMoveY(std::vector<std::vector<int>> obj_map);
    // ^^^^^^^^^^^^

    double getRadius();
    //double getMass() const;
    //double getMaxSpeed() const;
};