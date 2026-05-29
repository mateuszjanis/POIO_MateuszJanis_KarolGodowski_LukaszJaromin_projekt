#pragma once
#include "pch.h"
#include <vector>
#include <cmath>

class Robot
{
private:
    double k = 1;
    int radius = 5;
    int x_pos, y_pos;
    int moveCount = 0;
    double ForceTreshold = .3;
    double Force[2] = {0.0, 0.0};

public:
    Robot(int x, int y, std::vector<std::vector<int>> obj_map);

    void setPosition(int x, int y, std::vector<std::vector<int>> obj_map);
    int getPosX();
    int getPosY();
    double getRadius();
    std::vector<int> computeMove();
    double getForceX() { return Force[0]; }
    double getForceY() { return Force[1]; }

    int getMoveCount();
    void increaseMoveCount();
    void setMoveCount(int value);

private:
    double computeForceComponent(int dist);
    void computeForce(std::vector<std::vector<int>> obj_map);
    // wykonywana jest podczas tworzenia obiektu robota
    // oraz po wykonaniu każdego ruchu (computeMove)

};