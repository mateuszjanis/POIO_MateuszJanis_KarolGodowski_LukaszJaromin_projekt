#pragma once
#include "pch.h"
#include <vector>
#include <cmath>

#define k 1

class Robot
{
private:

    int radius = 5;
    int x_pos, y_pos;
    int lastMoveX = 0;
    int lastMoveY = 0;
    int moveCount = 0;
    double ForceTreshold = .1;
    double Force[2] = {0.0, 0.0};

public:
    Robot(int x, int y);
    Robot(int x, int y, int moveCount);

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

    int getLastMoveX();
    int getLastMoveY();
    
    void computeForce(std::vector<std::vector<int>> obj_map);
    // wykonywana jest przy wywołaniu setInitialForces()
    // oraz po wykonaniu każdego ruchu (computeMove())

    void setLastMove(int x, int y);
    

private:
    double computeForceComponent(int dist);
    

};