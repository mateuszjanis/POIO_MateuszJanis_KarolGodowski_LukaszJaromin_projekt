#include "pch.h"
#include "Robot.h"

using namespace std;

Robot::Robot(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

Robot::Robot(int x, int y, int moveCount) : Robot(x, y)
{
    this->moveCount = moveCount;
}

void Robot::setPosition(int newX, int newY, std::vector<std::vector<int>> obj_map)
{
    x_pos = newX;
    y_pos = newY;
    
    computeForce(obj_map);
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

int Robot::getLastMoveX()
{
    return lastMoveX;
}

int Robot::getLastMoveY()
{
    return lastMoveY;
}

void Robot::setMoveCount(int value)
{
    moveCount = value;
}

double Robot::computeForceComponent(int dist)
{
    double ForceComponent = - k * 1 / (dist * dist);

    return ForceComponent;
}

void Robot::computeForce(std::vector<std::vector<int>> obj_map)
{
    double ForceX = 0;
    double ForceY = 0;

    int cols = obj_map.size();
    int rows = obj_map[0].size();

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

    int component = 1;

    for (auto dir : directions) {

        if (abs(dir.first) == 1 && abs(dir.second) == 1) //po skosie należy "zmniejszyć" badaną odległość
        {
            component = 1 / sqrt(2);
        }
        else
        {
            component = 1;
        }

        for (int step = 1; step * component <= radius; step++) {

            int dx = dir.first * step;
            int dy = dir.second * step;
            int current_x = x_pos + dx;
            int current_y = y_pos + dy;

            if (current_x < 0 || current_x >= cols || current_y < 0 || current_y >= rows) {
                break; // poza mapą
            }

            int cell_value = obj_map[current_x][current_y];

            double dist = sqrt(dx * dx + dy * dy);
            double Force = computeForceComponent(dist); // całkowita siła 

            if (cell_value != 0) {
                ForceX += Force * dx / dist; // rzutowanie 
                ForceY += Force * dy / dist; // na osie
                break;
            }
        }
    }

    Force[0] = ForceX;
    Force[1] = ForceY;

}

vector<int> Robot::computeMove()
{
    double ForceX = Force[0];
    double ForceY = Force[1];
    vector<int> move(2);

    double tangens = ForceY / ForceX;
    int my, mx;

    // treshold dla zbyt małych sił
    if (sqrt(ForceX * ForceX + ForceY * ForceY) < ForceTreshold)
    {
        move[0] = 0;
        move[1] = 0;
    }
    else
    {
        if (ForceY >= 0) { my = 1; }
        else { my = -1; }

        if (ForceX >= 0) { mx = 1; }
        else { mx = -1; }

        if (abs(tangens) < sqrt(3) / 3) // tan(30st)
        {
            move[0] = mx;
            move[1] = 0;
        }
        else if (abs(tangens) < sqrt(3)) // tan(60st)
        {
            move[0] = mx;
            move[1] = my;
        }
        else
        {
            move[0] = 0;
            move[1] = my;
        }
    }

    lastMoveX = move[0];
    lastMoveY = move[1];

    return move;
};