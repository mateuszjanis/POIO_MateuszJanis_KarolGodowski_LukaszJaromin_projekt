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

void WrapperMap::show()
{
	vector<vector<int>> obj_map = mapa->get_map();

	for (int i = 0; i < mapa->get_size_x(); i++) {
		for (int j = 0; j < mapa->get_size_x(); j++) {
			switch (obj_map[i][j])
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
};

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
		this->show();
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
		this->show();
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

void WrapperMap::showRobotPos()
{
	int count = mapa->get_robot_num();
	vector<int> tempRobotPos(2);

	for (int i = 0; i < count; i++)
	{
		tempRobotPos = mapa->get_robot_pos(i);
		cout << "Robot "<< i << " x: " << tempRobotPos[0] 
			<<" y: " << tempRobotPos[1] << endl;
	}
}