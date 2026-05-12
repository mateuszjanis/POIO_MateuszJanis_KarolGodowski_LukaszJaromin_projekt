#include "pch.h"
#include "Map.h"
#include <vector>

using namespace std;

Map::Map()
{
	int init_x = 20;
	int init_y = 20;
	
	this->resize(init_x, init_y);
}

Map::Map(int x_len, int y_len)
{
	this -> resize(x_len, y_len);
}

void Map::resize(int x_len, int y_len)
{
	size_x = x_len;
	size_y = y_len;

	obj_map.clear();
	obj_map.resize(size_x);

	for (int i = 0; i < size_x; i++)
	{
		obj_map[i].resize(size_y);
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (i == 0 || i == size_x - 1 || j == 0 || j == size_y - 1)
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

vector<int> Map::get_robot_pos(int id)
{
	vector<int> position(2);
	position[0] = robot_list[id].getPosX();
	position[1] = robot_list[id].getPosY();

	return position;
}

vector<vector<int>> Map::get_map() {

	return obj_map;

}

int Map::placeRobot(int x, int y)
{
	int com;
	Robot new_robot(x, y);

	if (x > 0 && y > 0) {
		if (x < size_x) {
			if (y < size_y) {
				switch (obj_map[x][y])
				{
				case 0:
					obj_map[x][y] = 2;
					com = 0; // jest ok

					robot_list.push_back(new_robot);
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
					com = 0; // jest ok
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

void Map::clearRobot(int id)
{
	int x = robot_list[id].getPosX();
	int y = robot_list[id].getPosY();
	obj_map[x][y] = 0;
}

void Map::moveRobot(int id, vector<int> move)
{
	int oldX = robot_list[id].getPosX();
	int oldY = robot_list[id].getPosY();

	int xtemp = oldX + move[0];
	int ytemp = oldY + move[1];

	// Robot nie powinien wjezdzac w sciane brzegowa.
	if (xtemp <= 0) xtemp = 1;
	else if (xtemp >= size_x - 1) xtemp = size_x - 2;

	if (ytemp <= 0) ytemp = 1;
	else if (ytemp >= size_y - 1) ytemp = size_y - 2;

	// Jezeli pole docelowe jest zajete, robot zostaje w miejscu.
	// To jest bezpieczniejsze niz petla while, ktora mogla sie zawieszac.
	if (obj_map[xtemp][ytemp] != 0)
	{
		xtemp = oldX;
		ytemp = oldY;
	}

	robot_list[id].setPosition(xtemp, ytemp);
	obj_map[xtemp][ytemp] = 2;
}

void Map::update()
{
	int id = 0;

	for (auto& robot : robot_list)
	{
		vector<int> move = robot.computeMove(obj_map);
	
		this->clearRobot(id);	
		this->moveRobot(id, move);

		id++;
	}
}

