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

	switch (mapa->placeRobot(x, y))
	{
	case -2:
		cout << endl << "W tym miejscu jest robot";
		break;
	case -1:
		cout << endl << "W tym miejscu jest przeszkoda";
		break;
	case 0:
		system("CLS");
		cout << endl << "Wstawiono robota!" << endl;
		doDecrement = 0;
		break;
	case 1:
		cout << endl << "X musi być w zakresie mapy: 0 - " << mapa->get_size_x();
		break;
	case 2:
		cout << endl << "Y musi być w zakresie mapy: 0 - " << mapa->get_size_y();
		break;
	case 3:
		cout << endl << "Wspolrzedne musza byc dodatnie";
		break;
	}

	return doDecrement;
}

int WrapperMap::placeObstacle(int x, int y)
{
	int doDecrement = 1;

	switch (mapa->placeObstacle(x, y))
	{
	case -2:
		cout << endl << "W tym miejscu jest robot";
		break;
	case -1:
		cout << endl << "W tym miejscu jest przeszkoda";
		break;
	case 0:
		system("CLS");
		cout << endl << "Wstawiono przeszkode!" << endl;
		doDecrement = 0;
		break;
	case 1:
		cout << endl << "X musi być w zakresie mapy: 0 - " << mapa->get_size_x();
		break;
	case 2:
		cout << endl << "Y musi być w zakresie mapy: 0 - " << mapa->get_size_y();
		break;
	case 3:
		cout << endl << "Wspolrzedne musza byc dodatnie";
		break;
	}

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