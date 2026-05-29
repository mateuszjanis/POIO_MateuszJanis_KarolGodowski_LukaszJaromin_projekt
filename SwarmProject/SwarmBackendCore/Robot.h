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
    int moveCount = 0;

public:
    Robot(int x, int y);

    void setPosition(int x, int y);
    int getPosX();
    int getPosY();
    double getRadius();
    std::vector<int> computeMove(std::vector<std::vector<int>> obj_map);

    // do liczenia przemieszczen robotow
    int getMoveCount(); 
    void increaseMoveCount(); 
    //

private:
    double computeForceComponent(int dist);

};