#include "WrapperMap.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

WrapperMap::WrapperMap(int x_len, int y_len)
{
    mapa = new Map(x_len, y_len);
}

WrapperMap::~WrapperMap()
{
    delete mapa;
    mapa = nullptr;
}

void WrapperMap::show()
{
    vector<vector<int>> obj_map = mapa->get_map();

    for (int i = 0; i < mapa->get_size_y(); i++)
    {
        for (int j = 0; j < mapa->get_size_x(); j++)
        {
            switch (obj_map[j][i])
            {
            case 0:
                cout << "  ";
                break;
            case 1:
                cout << "x ";
                break;
            case 2:
                cout << "R ";
                break;
            }
        }
        cout << endl;
    }
}

int WrapperMap::placeRobot(int x, int y)
{
    return mapa->placeRobot(x, y);
}

int WrapperMap::placeObstacle(int x, int y)
{
    return mapa->placeObstacle(x, y);
}

void WrapperMap::update()
{
    mapa->update();
}

void WrapperMap::showRobotPos()
{
    int count = mapa->get_robot_num();
    vector<int> tempRobotPos(2);
    vector<double> tempRobotForce(2);

    for (int i = 0; i < count; i++)
    {
        tempRobotPos = mapa->get_robot_pos(i);
        tempRobotForce = mapa->get_robot_Force(i);

        cout << "Robot " << i
            << " x: " << tempRobotPos[0]
            << " y: " << tempRobotPos[1]
            << " ruchy: " << mapa->get_robot_move_count(i)
            << " FX: " << tempRobotForce[0]
            << " FY: " << tempRobotForce[1]
            << " F: " << sqrt(pow(tempRobotForce[0], 2) + pow(tempRobotForce[1], 2))
            << endl;
    }
}

void WrapperMap::setInitialForces()
{
    mapa->setInitialForces();
}

bool WrapperMap::saveToFile(const std::string& fileName)
{
    return mapa->saveToFile(fileName);
}

bool WrapperMap::loadFromFile(const std::string& fileName)
{
    return mapa->loadFromFile(fileName);
}

int WrapperMap::getSizeX()
{
    return mapa->get_size_x();
}

int WrapperMap::getSizeY()
{
    return mapa->get_size_y();
}

int WrapperMap::getRobotNum()
{
    return mapa->get_robot_num();
}

int WrapperMap::getObstacleNum()
{
    return mapa->get_obstacle_num();
}

std::vector<std::vector<int>> WrapperMap::getMap()
{
    return mapa->get_map();
}

std::vector<int> WrapperMap::getRobotPos(int id)
{
    return mapa->get_robot_pos(id);
}

int WrapperMap::getRobotMoveCount(int id)
{
    return mapa->get_robot_move_count(id);
}

int WrapperMap::getRobotLastMoveX(int id)
{
    return mapa->get_robot_last_move_x(id);
}

int WrapperMap::getRobotLastMoveY(int id)
{
    return mapa->get_robot_last_move_y(id);
}

bool WrapperMap::undoLastState()
{
    return mapa->undoLastState();
}