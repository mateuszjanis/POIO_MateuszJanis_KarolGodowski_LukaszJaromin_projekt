#include "pch.h"
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

Map::Map()
{
    int init_x = 20;
    int init_y = 20;
    this->resize(init_x, init_y);
}

Map::Map(int x_len, int y_len)
{
    this->resize(x_len, y_len);
}

Map::~Map()
{
    deleteRobots();
}

void Map::deleteRobots()
{
    for (auto& robot : robot_list)
    {
        delete robot;
    }

    robot_list.clear();
}

void Map::resize(int x_len, int y_len)
{
    deleteRobots();
    history.clear();

    size_x = x_len;
    size_y = y_len;

    obj_map.assign(x_len, vector<int>(y_len, 0));

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
        {
            if (i == 0 || i == x_len - 1 || j == 0 || j == y_len - 1)
                obj_map[i][j] = 1;
            else
                obj_map[i][j] = 0;
        }
    }
}

int Map::get_size_x()
{
    return size_x;
}

int Map::get_size_y()
{
    return size_y;
}

int Map::get_robot_num()
{
    return static_cast<int>(robot_list.size());
}

int Map::get_robot_move_count(int id)
{
    return robot_list[id]->getMoveCount();
}

vector<int> Map::get_robot_pos(int id)
{
    vector<int> position(2);

    position[0] = robot_list[id]->getPosX();
    position[1] = robot_list[id]->getPosY();

    return position;
}

vector<double> Map::get_robot_Force(int id)
{
    vector<double> force(2);

    force[0] = robot_list[id]->getForceX();
    force[1] = robot_list[id]->getForceY();

    return force;
}

vector<vector<int>> Map::get_map()
{
    return obj_map;
}

int Map::placeRobot(int x, int y)
{
    int com;

    if (x > 0 && y > 0)
    {
        if (x < size_x)
        {
            if (y < size_y)
            {
                switch (obj_map[x][y])
                {
                case 0:
                    saveState();
                    obj_map[x][y] = 2;
                    robot_list.push_back(new Robot(x, y));
                    com = 0;
                    break;

                case 1:
                    com = -1;
                    break;

                case 2:
                    com = -2;
                    break;

                default:
                    com = -3;
                    break;
                }
            }
            else
            {
                com = 1;
            }
        }
        else
        {
            com = 2;
        }
    }
    else
    {
        com = 3;
    }

    return com;
}

int Map::placeObstacle(int x, int y)
{
    int com;

    if (x > 0 && y > 0)
    {
        if (x < size_x)
        {
            if (y < size_y)
            {
                switch (obj_map[x][y])
                {
                case 0:
                    saveState();
                    obj_map[x][y] = 1;
                    com = 0;
                    break;

                case 1:
                    com = -1;
                    break;

                case 2:
                    com = -2;
                    break;

                default:
                    com = -3;
                    break;
                }
            }
            else
            {
                com = 1;
            }
        }
        else
        {
            com = 2;
        }
    }
    else
    {
        com = 3;
    }

    return com;
}

void Map::clearRobot(int id)
{
    int x = robot_list[id]->getPosX();
    int y = robot_list[id]->getPosY();

    obj_map[x][y] = 0;
}

void Map::moveRobot(int id, vector<int> move)
{
    int xtemp = robot_list[id]->getPosX() + move[0];
    int ytemp = robot_list[id]->getPosY() + move[1];

    bool checkObstacle = true;

    while (checkObstacle)
    {
        if (xtemp < 0 || xtemp >= size_x || ytemp < 0 || ytemp >= size_y)
        {
            xtemp = robot_list[id]->getPosX();
            ytemp = robot_list[id]->getPosY();
            break;
        }

        if (obj_map[xtemp][ytemp] != 0)
        {
            if (move[0] < 0)
                xtemp = xtemp + 1;
            else if (move[0] > 0)
                xtemp = xtemp - 1;

            if (move[1] < 0)
                ytemp = ytemp + 1;
            else if (move[1] > 0)
                ytemp = ytemp - 1;
        }
        else
        {
            checkObstacle = false;
        }
    }

    if (robot_list[id]->getPosX() != xtemp || robot_list[id]->getPosY() != ytemp)
    {
        robot_list[id]->increaseMoveCount();
    }

    robot_list[id]->setPosition(xtemp, ytemp, obj_map);
    obj_map[xtemp][ytemp] = 2;
}

void Map::update()
{
    if (robot_list.empty())
        return;

    saveState();

    int id = 0;
    vector<int> curr_move = { 0, 0 };
    vector<vector<int>> move_list;

    for (auto& robot : robot_list)
    {
        robot->computeForce(obj_map);
    }

    for (auto& robot : robot_list)
    {
        curr_move = robot->computeMove();
        move_list.push_back(curr_move);
    }

    curr_move = { 0, 0 };

    for (auto& robot : robot_list)
    {
        curr_move = move_list[id];
        clearRobot(id);
        moveRobot(id, curr_move);
        id++;
    }
}

int Map::get_obstacle_num()
{
    int count = 0;

    for (int x = 1; x < size_x - 1; x++)
    {
        for (int y = 1; y < size_y - 1; y++)
        {
            if (obj_map[x][y] == 1)
                count++;
        }
    }

    return count;
}

int Map::get_robot_last_move_x(int id)
{
    return robot_list[id]->getLastMoveX();
}

int Map::get_robot_last_move_y(int id)
{
    return robot_list[id]->getLastMoveY();
}

void Map::setInitialForces()
{
    for (auto& robot : robot_list)
    {
        robot->computeForce(obj_map);
    }
}

bool Map::saveToFile(const string& fileName)
{
    ofstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }

    file << "SWARM_SAVE_V1" << endl;
    file << size_x << " " << size_y << endl;

    int obstacleCount = 0;

    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            if (obj_map[x][y] == 1 && !(x == 0 || x == size_x - 1 || y == 0 || y == size_y - 1))
            {
                obstacleCount++;
            }
        }
    }

    file << "OBSTACLES " << obstacleCount << endl;

    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            if (obj_map[x][y] == 1 && !(x == 0 || x == size_x - 1 || y == 0 || y == size_y - 1))
            {
                file << x << " " << y << endl;
            }
        }
    }

    file << "ROBOTS " << robot_list.size() << endl;

    for (int i = 0; i < static_cast<int>(robot_list.size()); i++)
    {
        file << robot_list[i]->getPosX() << " "
            << robot_list[i]->getPosY() << " "
            << robot_list[i]->getMoveCount() << " "
            << robot_list[i]->getLastMoveX() << " "
            << robot_list[i]->getLastMoveY()
            << endl;
    }

    file.close();

    return true;
}

bool Map::loadFromFile(const string& fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }

    string header;
    file >> header;

    if (header != "SWARM_SAVE_V1")
    {
        return false;
    }

    int loadedSizeX, loadedSizeY;
    file >> loadedSizeX >> loadedSizeY;

    if (!file.good() || loadedSizeX < 3 || loadedSizeY < 3)
    {
        return false;
    }

    deleteRobots();
    history.clear();

    size_x = loadedSizeX;
    size_y = loadedSizeY;

    obj_map.assign(size_x, vector<int>(size_y, 0));

    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            if (x == 0 || x == size_x - 1 || y == 0 || y == size_y - 1)
                obj_map[x][y] = 1;
            else
                obj_map[x][y] = 0;
        }
    }

    string sectionName;
    int obstacleCount;

    file >> sectionName >> obstacleCount;

    if (sectionName != "OBSTACLES" || obstacleCount < 0)
    {
        return false;
    }

    for (int i = 0; i < obstacleCount; i++)
    {
        int x, y;
        file >> x >> y;

        if (!file.good())
            return false;

        if (x > 0 && x < size_x - 1 && y > 0 && y < size_y - 1 && obj_map[x][y] == 0)
        {
            obj_map[x][y] = 1;
        }
    }

    int robotCount;

    file >> sectionName >> robotCount;

    if (sectionName != "ROBOTS" || robotCount < 0)
    {
        return false;
    }

    for (int i = 0; i < robotCount; i++)
    {
        int x, y, moveCount, lastMoveX, lastMoveY;

        file >> x >> y >> moveCount >> lastMoveX >> lastMoveY;

        if (!file.good())
            return false;

        if (x > 0 && x < size_x - 1 && y > 0 && y < size_y - 1 && obj_map[x][y] == 0)
        {
            Robot* robot = new Robot(x, y);

            robot->setMoveCount(moveCount);
            robot->setLastMove(lastMoveX, lastMoveY);

            robot_list.push_back(robot);
            obj_map[x][y] = 2;
        }
    }

    setInitialForces();

    file.close();

    return true;
}

void Map::saveState()
{
    MapState state;

    state.size_x = size_x;
    state.size_y = size_y;
    state.obj_map = obj_map;

    for (auto& robot : robot_list)
    {
        RobotState rs;

        rs.x = robot->getPosX();
        rs.y = robot->getPosY();
        rs.moveCount = robot->getMoveCount();
        rs.lastMoveX = robot->getLastMoveX();
        rs.lastMoveY = robot->getLastMoveY();

        state.robots.push_back(rs);
    }

    history.push_back(state);
}

bool Map::undoLastState()
{
    if (history.empty())
        return false;

    MapState previous = history.back();
    history.pop_back();

    int commonCount = std::min(
        static_cast<int>(previous.robots.size()),
        static_cast<int>(robot_list.size())
    );

    vector<int> reverseMoveX(commonCount, 0);
    vector<int> reverseMoveY(commonCount, 0);

    for (int i = 0; i < commonCount; i++)
    {
        reverseMoveX[i] = previous.robots[i].x - robot_list[i]->getPosX();
        reverseMoveY[i] = previous.robots[i].y - robot_list[i]->getPosY();
    }

    deleteRobots();

    size_x = previous.size_x;
    size_y = previous.size_y;
    obj_map = previous.obj_map;

    for (int i = 0; i < static_cast<int>(previous.robots.size()); i++)
    {
        RobotState rs = previous.robots[i];

        Robot* robot = new Robot(rs.x, rs.y);

        robot->setMoveCount(rs.moveCount);
        robot->setLastMove(rs.lastMoveX, rs.lastMoveY);

        if (i < commonCount)
        {
            robot->setLastMove(reverseMoveX[i], reverseMoveY[i]);
        }

        robot_list.push_back(robot);
    }

    setInitialForces();

    return true;
}