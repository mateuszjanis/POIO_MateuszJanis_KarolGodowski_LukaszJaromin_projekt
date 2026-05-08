#pragma once
#include "pch.h"
#include <vector>
#include <cmath>

class Robot
{
private:
    double k = 1;
    double dt = 1;
    int radius = 10;
    int x_pos, y_pos;

public:
    Robot(int x, int y);

    void setPosition(int x, int y);
    int getPosX();
    int getPosY();
    double getRadius();
    std::vector<int> computeMove(std::vector<std::vector<int>> obj_map);

private:
    double ForceX_component(int dx, int dy, int currObj);
    double ForceY_component(int dx, int dy, int currObj);
};