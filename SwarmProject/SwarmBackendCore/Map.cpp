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

	for (auto& robot : robot_list) {
		delete robot;
	}

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
					saveState();
					obj_map[x][y] = 2;
					com = 0; // jest ok

					robot_list.push_back(new Robot(x, y));
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

	if (robot_list.empty())
		return;

	saveState();


	int id = 0;
	vector<int> curr_move = { 0,0 };
	vector<vector<int>> move_list;

	// aktualizacja sił przed obliczeniem ruchu
	for (auto& robot : robot_list)
	{
		robot->computeForce(obj_map);
	}

	// obliczenie ruchów
	for (auto& robot : robot_list)
	{
		curr_move = robot->computeMove();
		move_list.push_back(curr_move);

	}

	curr_move = { 0,0 };
	// właściwy ruch robotów
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

    for (int x = 1; x < size_x-1; x++)
    {
        for (int y = 1; y < size_y-1; y++)
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

void Map::updateForces()
{
	for (auto& robot : robot_list)
	{
		robot->computeForce(obj_map); // aktualna mapa
	}
}

 bool Map::saveToFile(const string& fileName)
 {
	 FILE* file = nullptr;
	 // Bezpieczne otwarcie pliku w trybie zapisu ("w")
	 if (fopen_s(&file, fileName.c_str(), "w") != 0 || file == nullptr)
	 {
		 return false;
	 }

	 // Nagłówek i rozmiar mapy
	 fprintf(file, "SWARM_SAVE_V1\n");
	 fprintf(file, "%d %d\n", size_x, size_y);

	 // Zliczanie wewnętrznych przeszkód
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

	 // Zapis przeszkód
	 fprintf(file, "OBSTACLES %d\n", obstacleCount);
	 for (int x = 0; x < size_x; x++)
	 {
		 for (int y = 0; y < size_y; y++)
		 {
			 if (obj_map[x][y] == 1 && !(x == 0 || x == size_x - 1 || y == 0 || y == size_y - 1))
			 {
				 fprintf(file, "%d %d\n", x, y);
			 }
		 }
	 }

	 // Zapis robotów
	 fprintf(file, "ROBOTS %zu\n", robot_list.size());
	 for (size_t i = 0; i < robot_list.size(); i++)
	 {
		 fprintf(file, "%d %d %d %d %d\n",
			 robot_list[i]->getPosX(),
			 robot_list[i]->getPosY(),
			 robot_list[i]->getMoveCount(),
			 robot_list[i]->getLastMoveX(),
			 robot_list[i]->getLastMoveY());
	 }

	 fclose(file);
	 return true;
 }
 
 bool Map::loadFromFile(const string& fileName)
 {
	 FILE* file = nullptr;
	 if (fopen_s(&file, fileName.c_str(), "r") != 0 || file == nullptr)
	 {
		 return false;
	 }

	 char header[64];
	 if (fscanf_s(file, "%63s", header, (unsigned)_countof(header)) != 1)
	 {
		 fclose(file);
		 return false;
	 }

	 if (strcmp(header, "SWARM_SAVE_V1") != 0)
	 {
		 fclose(file);
		 return false;
	 }

	 int new_size_x, new_size_y;
	 if (fscanf_s(file, "%d %d", &new_size_x, &new_size_y) != 2)
	 {
		 fclose(file);
		 return false;
	 }

	 // Zmiana rozmiaru mapy (zobacz uwagę poniżej dotyczącą tej funkcji!)
	 this->resize(new_size_x, new_size_y);

	 char section[64];
	 int itemsCount;

	 // Odczyt bloków pliku
	 while (fscanf_s(file, "%63s %d", section, (unsigned)_countof(section), &itemsCount) == 2)
	 {
		 if (strcmp(section, "OBSTACLES") == 0)
		 {
			 for (int i = 0; i < itemsCount; i++)
			 {
				 int ox, oy;
				 if (fscanf_s(file, "%d %d", &ox, &oy) == 2)
				 {
					 if (ox > 0 && ox < size_x - 1 && oy > 0 && oy < size_y - 1)
					 {
						 obj_map[ox][oy] = 1;
					 }
				 }
			 }
		 }
		 else if (strcmp(section, "ROBOTS") == 0)
		 {
			 for (int i = 0; i < itemsCount; i++)
			 {
				 int rx, ry, moveCount, lastMoveX, lastMoveY;
				 if (fscanf_s(file, "%d %d %d %d %d", &rx, &ry, &moveCount, &lastMoveX, &lastMoveY) == 5)
				 {
					 if (rx > 0 && rx < size_x - 1 && ry > 0 && ry < size_y - 1)
					 {
						 Robot* robot = new Robot(rx, ry, moveCount);
						 robot->setLastMove(lastMoveX, lastMoveY);

						 robot_list.push_back(robot);
						 obj_map[rx][ry] = 2;
					 }
				 }
			 }
		 }
	 }

	 fclose(file);

	 updateForces();
	 history.clear();

	 return true;
 }

 void Map::saveState()
 {
	 MapState state;

	 state.size_x = size_x;
	 state.size_y = size_y;
	 //state.robot_list = robot_list;
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
	 state.obj_map = obj_map;

	 history.push_back(state);
 }

 bool Map::undoLastState()
 {
	 if (history.empty())
		 return false;

	 MapState previous = history.back();
	 history.pop_back();

	 
	 int commonCount = std::min(
		 (int)previous.robots.size(),
		 (int)robot_list.size()
	 );

	 std::vector<int> reverseMoveX(commonCount, 0);
	 std::vector<int> reverseMoveY(commonCount, 0);

	 for (int i = 0; i < commonCount; i++)
	 {
		 reverseMoveX[i] = previous.robots[i].x - robot_list[i]->getPosX();
		 reverseMoveY[i] = previous.robots[i].y - robot_list[i]->getPosY();
	 }

	 
	 for (auto& robot : robot_list)
	 {
		 delete robot;
	 }
	 robot_list.clear();

	 
	 size_x = previous.size_x;
	 size_y = previous.size_y;
	 obj_map = previous.obj_map;

	 
	 for (int i = 0; i < previous.robots.size(); i++)
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

	 updateForces();

	 return true;
 }