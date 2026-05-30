#include "pch.h"
#include "WrapperMap.h"
#include <iostream>
#include <vector>
using namespace std;

WrapperMap::~WrapperMap()
{
	delete mapa;
	mapa = nullptr;
}

WrapperMap::WrapperMap(int x_len, int y_len)
{
	mapa->resize(x_len, y_len);
}

int WrapperMap::placeRobot(int x, int y)
{
	int doDecrement = 1;

	if(mapa->placeRobot(x, y) == 0) { doDecrement = 0; }

	return doDecrement;
}

int WrapperMap::placeObstacle(int x, int y)
{
	int doDecrement = 1;

	if (mapa->placeObstacle(x, y) == 0) { doDecrement = 0; }

	return doDecrement;
}

void WrapperMap::update()
{
	mapa->update();
}


std::vector<std::vector<int>> WrapperMap::getMap()
{
	return mapa->get_map();
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

// do liczenia ruchow robota
int WrapperMap::getRobotMoveCount(int id)
{
	return mapa->get_robot_move_count(id);
}

std::vector<int> WrapperMap::getRobotPos(int id)
{
	return mapa->get_robot_pos(id);
}

void WrapperMap::setInitialForces()
{
	mapa->setInitialForces();
}

int WrapperMap::getRobotLastMoveX(int id)
{
	return mapa->get_robot_last_move_x(id);
}

int WrapperMap::getRobotLastMoveY(int id)
{
	return mapa->get_robot_last_move_y(id);
}