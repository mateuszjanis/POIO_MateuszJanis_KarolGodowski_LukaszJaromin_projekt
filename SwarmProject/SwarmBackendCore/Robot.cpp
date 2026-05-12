#include "pch.h"
#include "Robot.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

Robot::Robot(int x, int y)
{
    x_pos = x;
    y_pos = y;
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

double Robot::ForceX_component(int dx, int dy, int currObj)
{
    double ForceComponent = 0;

    if (dx == 0 || currObj == 0 || dx * dx + dy * dy > radius * radius)
    {
        ForceComponent = 0;
    }
    else if (dx > 0)
    {
        ForceComponent = - k * 1 / pow(dx, 2);
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
        ForceComponent = - k * 1 / pow(dy, 2);
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
    move[0] = static_cast<int>(round(ForceX * dt * dt));
    move[1] = static_cast<int>(round(ForceY * dt * dt));

    // Ruch maksymalnie o jedno pole, zeby robot nie przeskakiwal przez przeszkody.
    if (move[0] > 1) move[0] = 1;
    if (move[0] < -1) move[0] = -1;

    if (move[1] > 1) move[1] = 1;
    if (move[1] < -1) move[1] = -1;

    // Jezeli pole potencjalne sie wyzerowalo, dodajemy losowy ruch eksploracyjny.
    // Bez tego robot czesto zatrzymuje sie po pierwszym kroku.
    if (move[0] == 0 && move[1] == 0)
    {
        int direction = rand() % 4;

        switch (direction)
        {
        case 0:
            move[0] = 1;
            move[1] = 0;
            break;
        case 1:
            move[0] = -1;
            move[1] = 0;
            break;
        case 2:
            move[0] = 0;
            move[1] = 1;
            break;
        case 3:
            move[0] = 0;
            move[1] = -1;
            break;
        }
    }

    return move;


};
