#pragma once
#include "Map.h"

class WrapperMap
{
	Map* mapa = new Map(20,20);

public:
	~WrapperMap();
	WrapperMap(int x_len, int y_len);
	void show();
	int placeRobot(int x, int y);
	int placeObstacle(int x, int y);
	void update();
	void showRobotPos();

	std::vector<std::vector<int>> getMap();
	int getSizeX();
	int getSizeY();

	int getRobotNum();
	int getObstacleNum();

	// do liczenia ruchow robota
	int getRobotMoveCount(int id);

	std::vector<int> getRobotPos(int id);

	int getRobotLastMoveX(int id);
	int getRobotLastMoveY(int id);

private:

};
