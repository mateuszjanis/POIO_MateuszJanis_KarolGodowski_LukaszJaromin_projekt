#include "pch.h"
#include "Map.h"
#include <vector>
#include <fstream>
#include <string>

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

void Map::resize(int x_len, int y_len) {

    size_x = x_len;
    size_y = y_len;
    robot_list.clear();

    obj_map.assign(x_len, vector<int>(y_len, 0));

    for (int i = 0; i < x_len; i++) {
        for (int j = 0; j < y_len; j++) {
            if (i == 0 || i == x_len - 1 || j == 0 || j == y_len - 1)
            {
                obj_map[i][j] = 1;
            }
            else
            {
                obj_map[i][j] = 0;
            }
        }
    }
}

int Map::get_size_x() {
    return size_x;
}

int Map::get_size_y() {
    return size_y;
}

int Map::get_robot_num()
{
    return robot_list.size();
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

std::vector<double> Map::get_robot_Force(int id)
{
	vector<double> force(2);
	force[0] = robot_list[id]->getForceX();
	force[1] = robot_list[id]->getForceY();

	return force;
}

vector<vector<int>> Map::get_map() {
    return obj_map;
}

int Map::placeRobot(int x, int y)
{
	int com;

	if (x > 0 && y > 0) {
		if (x < size_x) {
			if (y < size_y) {
				switch (obj_map[x][y])
				{
				case 0:
					obj_map[x][y] = 2;
					com = 0; // jest ok

					robot_list.push_back(new Robot(x, y, obj_map));
					break;
				case 1:
					com = -1; // przeszkoda
					break;
				case 2:
					com = -2; // robot
					break;
				}
			}
			else {
				com = 1; // y poza granicą
			}
		}
		else {
			com = 2; // x poza granicą
		}
	}
	else {
		com = 3; // współrzędne ujemne
	}

	return com;
}

int Map::placeObstacle(int x, int y)
{
    int com;

    if (x > 0 && y > 0) {
        if (x < size_x) {
            if (y < size_y) {
                switch (obj_map[x][y])
                {
                case 0:
                    obj_map[x][y] = 1;
                    com = 0;
                    break;
                case 1:
                    com = -1;
                    break;
                case 2:
                    com = -2;
                    break;
                }
            }
            else {
                com = 1;
            }
        }
        else {
            com = 2;
        }
    }
    else {
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

	// Natrafienie na obiekt
	bool checkObstacle = 1;

	while (checkObstacle)
	{
		if (obj_map[xtemp][ytemp] != 0)
		{
			if (move[0] < 0)
			{
				//xtemp + 1;
				xtemp = xtemp + 1;
			}
			else if (move[0] > 0)
			{
				//xtemp - 1;
				xtemp = xtemp - 1;
			}

			if (move[1] < 0)
			{
				//ytemp + 1;
				ytemp = ytemp + 1;
			}
			else if (move[1] > 0)
			{
				//ytemp - 1;
				ytemp = ytemp - 1;
			}

		}
		else
		{
			checkObstacle = 0;
		}
	}

	if (robot_list[id]->getPosX() != xtemp ||
		robot_list[id]->getPosY() != ytemp)
	{
		robot_list[id]->increaseMoveCount();
	}

	robot_list[id]->setPosition(xtemp, ytemp, obj_map); // czy działam na kopii czy na obiekcie ?????
	obj_map[xtemp][ytemp] = 2;

}

void Map::update()
{
	int id = 0;

	for (auto& robot : robot_list)
	{
		vector<int> move = robot->computeMove();
	
		this->clearRobot(id);	
		this->moveRobot(id, move);

		id++;
	}
}

int Map::get_obstacle_num()
{
    int count = 0;

    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            if (obj_map[x][y] == 1)
                count++;
        }
    }

    return count;
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
    for (int i = 0; i < robot_list.size(); i++)
    {
        file << robot_list[i]->getPosX() << " "
            << robot_list[i]->getPosY() << " "
            << robot_list[i]->getMoveCount() << endl;
    }

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

    if (loadedSizeX < 3 || loadedSizeY < 3)
    {
        return false;
    }

    resize(loadedSizeX, loadedSizeY);

    string sectionName;
    int obstacleCount;
    file >> sectionName >> obstacleCount;

    if (sectionName != "OBSTACLES")
    {
        return false;
    }

    for (int i = 0; i < obstacleCount; i++)
    {
        int x, y;
        file >> x >> y;

        if (x > 0 && x < size_x - 1 && y > 0 && y < size_y - 1 && obj_map[x][y] == 0)
        {
            obj_map[x][y] = 1;
        }
    }

    int robotCount;
    file >> sectionName >> robotCount;

    if (sectionName != "ROBOTS")
    {
        return false;
    }

    for (int i = 0; i < robotCount; i++)
    {
        int x, y, moveCount;
        file >> x >> y >> moveCount;

        if (x > 0 && x < size_x - 1 && y > 0 && y < size_y - 1 && obj_map[x][y] == 0)
        {
            robot_list.push_back(new Robot(x, y, obj_map, moveCount));
            obj_map[x][y] = 2;
        }
    }

    return true;
}