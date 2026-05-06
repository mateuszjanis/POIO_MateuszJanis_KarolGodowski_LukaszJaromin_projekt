#pragma once
#include "pch.h"
#include <vector>
//#include "Robot.h"

class Map
{

	int size_x, size_y;
	//std::vector<Robot> robot_list;
	std::vector<std::vector<int>> obj_map; 

public:
	Map();
	Map(int x_len, int y_len);

	int get_size_x();
	int get_size_y();
	std::vector<std::vector<int>> get_map();

	void resize(int x_len, int y_len);
	int coord2id(int x, int y);
	int placeRobot(int x, int y);
	int placeObstacle(int x, int y);

private:

};

