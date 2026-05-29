#include "pch.h"
#include "Robot.h"

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

// do liczenia przemieszczen robotow
int Robot::getMoveCount()
{
    return moveCount;
}

void Robot::increaseMoveCount()
{
    moveCount++;
}

double Robot::computeForceComponent(int dist)
{
    double ForceComponent = 0;

    if (dist > 0)
    {
        ForceComponent = -k * 1 / pow(dist, 2);
    }
    else
    {
        ForceComponent = k * 1 / pow(dist, 2);
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

    //int x_min = max(0, x_pos - radius);
    //int x_max = min(cols - 1, x_pos + radius);
    //int y_min = max(0, y_pos - radius);
    //int y_max = min(rows - 1, y_pos + radius);

    vector<pair<int, int>> directions = {
        {0, -1},  // w górę
        {0, 1},   // w dół
        {-1, 0},  // w lewo
        {1, 0},   // w prawo
        {-1, -1}, // lewy górny skos
        {1, -1},  // prawy górny skos
        {-1, 1},  // lewy dolny skos
        {1, 1}    // prawy dolny skos
    };

    for (auto dir : directions) {

        for (int step = 1; step <= radius; ++step) {
            
            int dx = dir.first * step;
            int dy = dir.second * step;
            int current_x = x_pos + dx;
            int current_y = y_pos + dy;

            if (current_x < 0 || current_x >= cols  || current_y < 0 || current_y >= rows) {
                break; // poza mapą
            }

            int cell_value = obj_map[current_x][current_y];

            if (cell_value == 1 || cell_value == 2) {
                ForceX += computeForceComponent(dx);
                ForceY += computeForceComponent(dy);
                break;
            }
        }
    }

    double tangens = ForceY / ForceX;
    int my, mx;

    if (ForceY >= 0) { my = 1; }
    else { my = -1; }

    if (ForceX >= 0) { mx = 1; }
    else { mx = -1; }

    if (abs(tangens) < sqrt(3)/3) // tan(30st)
    {
        move[0] = mx;
        move[1] = 0;
    }
    else if (abs(tangens) < sqrt(3)) // tan(60)
    {
        move[0] = mx;
        move[1] = my;
    }
    else
    {
        move[0] = 0;
        move[1] = my;
    }


    return move;

};

