#include "pch.h"
#include "Robot.h"

using namespace std;

Robot::Robot(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

Robot::Robot(int x, int y, int moveCount)
{
    x_pos = x;
    y_pos = y;
    this->moveCount = moveCount;
}

void Robot::setPosition(int newX, int newY)
{
    x_pos = newX;
    y_pos = newY;
}

int Robot::getPosX()
{
    return x_pos;
}

int Robot::getPosY()
{
    return y_pos;
}

double Robot::getRadius()
{
    return radius;
}

int Robot::getMoveCount()
{
    return moveCount;
}

void Robot::increaseMoveCount()
{
    moveCount++;
}

void Robot::setMoveCount(int value)
{
    moveCount = value;
}

double Robot::ForceX_component(int dx, int dy, int currObj)
{
    double ForceComponent = 0;

    if (dx == 0 || currObj == 0 || dx * dx + dy * dy > radius * radius)
    {
        ForceComponent = 0;
    }
    else if (dx > 0)
    {
        ForceComponent = -k * 1 / pow(dx, 2);
    }
    else
    {
        ForceComponent = k * 1 / pow(dx, 2);
    }

    return ForceComponent;
}

double Robot::ForceY_component(int dx, int dy, int currObj)
{
    double ForceComponent = 0;

    if (dy == 0 || currObj == 0 || dx * dx + dy * dy > radius * radius)
    {
        ForceComponent = 0;
    }
    else if (dy > 0)
    {
        ForceComponent = -k * 1 / pow(dy, 2);
    }
    else
    {
        ForceComponent = k * 1 / pow(dy, 2);
    }

    return ForceComponent;
}

vector<int> Robot::computeMove(std::vector<std::vector<int>> obj_map)
{
    double ForceX = 0;
    double ForceY = 0;
    vector<int> move(2);

    int cols = obj_map.size();
    int rows = obj_map[0].size();

    int x_min = max(0, x_pos - radius);
    int x_max = min(cols - 1, x_pos + radius);
    int y_min = max(0, y_pos - radius);
    int y_max = min(rows - 1, y_pos + radius);

    for (int i = x_min; i <= x_max; i++) {
        for (int j = y_min; j <= y_max; j++) {

            int dx = i - x_pos;
            int dy = j - y_pos;

            ForceX += ForceX_component(dx, dy, obj_map[i][j]);
            ForceY += ForceY_component(dx, dy, obj_map[i][j]);
        }
    }

    move[0] = round(ForceX * dt * dt);
    move[1] = round(ForceY * dt * dt);

    return move;
};