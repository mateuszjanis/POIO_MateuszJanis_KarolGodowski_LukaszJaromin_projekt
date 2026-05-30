#pragma once
#include "Map.h"

class WrapperMap
{
	Map* mapa = new Map(20,20);

public:
	~WrapperMap();
	WrapperMap(int x_len, int y_len);
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

	void setInitialForces(); // Wyliczenie sił - powinno być użyte po postawieniu
	// wszystkich przeszkód i robotów
	// jeśli dodajemy roboty podczas symulacji - też wywołać
	// siły są liczone dla kolejnego ruchu wykonanego


	int getRobotLastMoveX(int id);
	int getRobotLastMoveY(int id);

	bool undoLastState();

private:

};
